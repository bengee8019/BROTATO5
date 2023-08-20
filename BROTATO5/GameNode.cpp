#include "Stdafx.h"
#include "GameNode.h"

//설계에 기반한 효율적인 방법론과 관리

HRESULT GameNode::init()
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//로케일 설정
		//프로그램의 언어가 여러 언어로 주어져 있는 경우 어떤 언어의 것을 출력할 것인지에 대한 설정
		setlocale(LC_ALL, "korean");

		SetTimer(_hWnd, 1, 10, NULL);
		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SOUNDMANAGER->init();

		return S_OK;
	}
	return S_FALSE;
}

//void GameNode::setBackBuffer(void)
//{
//	_backBuffer = new GImage;
//	_backBuffer->init(WINSIZE_X,WINSIZE_Y);
//}

void GameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render()
{
	
}

void GameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		FONTMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

GameNode::GameNode()
{
}

GameNode::~GameNode()
{
}

LRESULT GameNode::MainProc(HWND hwnd, UINT iMessage, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lparam);
		_ptMouse.y = HIWORD(lparam);
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case VK_ESCAPE:
			PostMessage(hwnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		this->render();
		EndPaint(hwnd, &ps);
		break;
	}
	return DefWindowProc(hwnd, iMessage, wparam, lparam);
}
