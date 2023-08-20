#pragma once
// 경고 무시
#pragma warning(disable : 4005) // 
// 4005: DXGI 등 그래픽 인터페이스에서 매크로 관련하여 출력되는 경고 //c++ > 고급 > 특정경고 사용안함
/*
▶ Stdafx

- MS의 비주얼 스튜디오를 이용하여 프로젝트를 만들면 생성되는 클래스
 ㄴ 이 친구가 의미하는 바는 표준 어플리케이션 프레임워크의 틀

- MS에서 개발자들의 능률 향상을 위해 만들어둔 PCH 파일
 ㄴ 자주 쓰이는 여러가지 헤더들은 미리 컴파일 해두어 이후 다시 컴파일하지 않고 사용

 - 개발에 초기 구축 단계에서는 별 필요성을 못 느끼지만 헤더파일의 크기가 커지거나 양이
   많아질수록 활용도 및 효율이 급상승한다. ↑
*/

//SDKDDKVER.h 는 프로그램에서 지원할 os에 따라 
//or 라이브러리에 따라 Windows 헤더에서 코드에 포함될 함수/ 상수 등을 제어하는데 사용
#include <SDKDDKVER.h>

// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// ㄴ GDI+ 를 사용하려면 헤더파일에서 꺼내와야 한다.
//#include <ole2.h> //회전가능한 헤더 까먹지 마셈
#define WIN32_LEAN_AND_MEAN             

// 디버깅 콘솔창
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")


//! 라이브러리 추가
#pragma comment (lib, "msimg32.lib")

//! Windows 헤더 파일
#include <windows.h>


//! C 런타임 헤더 파일입니다.
// stdlib: C언어의 표준 라이브러리 함수의 헤더 파일
#include <stdlib.h>
// C언어 메모리 할당에 사용
#include <malloc.h>

// 메모리 관련 헤더 파일
// ㄴ memset/ memcopy를 사용하는 헤더파일
#include <memory.h>

/*
▶ 문자열 셋
- 윈도우에서 사용할 문자열 출력 파일(문자) 셋(TextOut, DrawText, wsprintf 등등)
ㄴ 기본적으로 유니코드

 MBCS (멀티바이트 캐릭터 셋)
- 기존에 사용하던 멀티바이트 형태의 문자열을 뜻한다.
- 멀티바이트 코드는 영어 같은 아스키 코드에 포함되는 문자는 1바이트로 표현하고
  포함되지 않는 문자는 2바이트로 처리한다.

 WBCS (와이드바이트 캐릭터 셋)
- 모든 문자를 2바이트로 처리하며 유니코드 기반이다.

- VS에서는 개발시 멀티/ 유니코드를 쓸지 기본적으로 지정을 해줘야 한다
 유니코드인 경우에는 문자열을 따옴표로 감싸고 그 앞에 L을 붙여서 (L"")이라고 표기하고
 멀티바이트 같은 경우에는 그냥 "" 만 사용하면 된다
 유니코드로 개발된 프로그램을 멀티바이트로 이식하려면 이들 문자열의 표현 방식을
 다시 고쳐줘야 하기 때문에 매우 불편하다
 그래서 _T매크로를 사용해야 한다
 문자열을 따옴표로 감싸고 유니코드에서 사용한 "L"대신 "_T"를 사용하면 매크로가 알아서 
 개발환경에 맞게 치환해준다.
*/
#include <tchar.h>
// stdio: 표준 입출력 헤더 파일
#include <stdio.h>
//! C++ 런타임 헤더 파일
#include <time.h>
#include <iostream>
/*
- c++11에서 추가된 시간 관련 라이브러리 (STL)
ㄴ 기본 C 런타임에서 제공하는 time 함수보다 다양한/ 확장된 기능을 지원
ㄴ 장점: 정밀도가 높다. (나노 밀리 초 단위)
	ㄴ time 함수는 초 단위의 값만 측정이 가능하기 때문에 정밀도가 떨어질 수 없다.
ㄴ OS와 독립적으로 동작을 한다.
*/
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <string>
//unordered_map: Hash 자료구조
// ㄴ 일반적 상황에서 map 보다 검색속도가 더 빠르다
// ㄴ 단, 유사 데이터가 많을시(key), 해시 충돌이 발생할 여지가 생기기 때문에 성능 저하가 발생
#include <unordered_map>
// cassert: C++ 프로그래머의 희망 -> 잘 쓰면.. killing process 
#include <cassert> //컴파일 예 아니요 /남발x
//bitset: 비트 연산을 좀 더 쉽게 관리해 주는 함수를 지원하는 STL
//reset,set,flip,all,any,size 등등..
#include <bitset> 
#include <windef.h>

#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

//GDI+
#include <ole2.h>

// !D2D/D3D 헤더파일
//#include <d2d1.h>
//#include<d2d1helper.h>
//#include <d3dx9.h>
//#include <D3DX11.h>
//#include <d3d11shader.h>
//#include <dinput.h>
//
//#pragma comment(lib, "d3d1.lib")
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dx11.lib")
//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
//
//ID2D1Factory*			_ID2DFactory=nullptr;
//ID2D1HwndRenderTarget*	_ID2DRenderTarget=nullptr;
//

//# 사용자 정의 헤더 파일 #

#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "SoundManager.h"
//#include "ItemManager.h"

//# 싱글톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
//#define SOUNDMANAGER TempSoundManager::getSingleton()
//#define ITEMMANAGER ItemManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()

//타이틀
#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

// !전체화면
#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN) //GetSystemMetrics()인자로 전달되는 시스템 설정 정보를 반환
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN) //SM_CXSCREEN ,SM_CYSCREEN 현제 화면 해상도 반환(x,y축) 
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	1280
#define WINSIZE_Y	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif

//# 매크로 # (윈도우창 초기화)

//#define WINNAME  (LPTSTR)(TEXT("WindowsAPI"))
//#define WINSTART_X 0
//#define WINSTART_Y 0
//#define WINSIZE_X  1280
//#define WINSIZE_Y  800
//WS_CAPTION : 타이틀바를 가지기 위한 옵션
//WS_SYSMENU : 제목 표기줄에 컨트롤 메뉴 상자 창
#define WINSTYLE   WS_CAPTION | WS_SYSMENU

//# 매크로 함수 #	(클래스에서 동적할당된 부분 해제)
#define SAFE_DELETE(p)  {if(p){delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if(p){(p)->release();(p)=nullptr;}} 

// # 전역 변수 #  // 플레이어 클래스의 인벤토리 추천
extern HINSTANCE _hInstance;
extern HWND _hWnd;
// X 좌표와 Y 좌표를 평면의 좌표에 정의할때 사용한다.
extern POINT _ptMouse;

#include "Bullet.h"
#include "Drops.h"
//class Bullet;
//class Drops;
EXTERN_C{
extern vector<Bullet> pVBullets;
extern vector<Drops> vDrops;
}

