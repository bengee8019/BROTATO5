#include "Stdafx.h"
#include "GameManager.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };


//콜백
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

GameManager* _gm;
int centerX;
int centerY;

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	LPSTR _lpszCmdParam,
	int nCmdShow)
{
	_gm = new GameManager();
	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);
	//메모리 단계 show 하기전에 셋팅
	// 클라이언트 영역의 사이즈를 정확히 잡아주기 위해 
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_gm->init()))
	{
		return 0;
	}
	//UpdateWindow(_hWnd);

	MSG message;
	//ZeroMemory(&message, sizeof(message));

	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	_gm->release();
	UnregisterClass(WINNAME, hInstance);
	return message.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wparam, LPARAM lparam)
{
	return _gm->MainProc(hwnd, iMessage, wparam, lparam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0,0,width,height };
	//실제 윈도우 크기 조정
	//AdjustWindowRect(): RECT 구조체, 윈도우 스타일, 메뉴여부?
	AdjustWindowRect(&rc, WINSTYLE, false);

	//얻어온 렉트의 정보로 윈도우 사이즈 세팅
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
	//기본적으로 렌더링 옵션 ZORDER = 투영 
}