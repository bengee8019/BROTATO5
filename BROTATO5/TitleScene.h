#pragma once
#include "Scene.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

class TitleScene :public Scene
{
private:
	vector<Button> vButton;

	ULONG_PTR gdiplusToken;

	//Image* bgImage1;
	Image* bgImage2;
	//Image* bgImage3;
	Image* bgImage4;
	Image* bgImage5;
	//wchar_t bgDir1[200];
	wchar_t bgDir2[200];
	//wchar_t bgDir3[200];
	wchar_t bgDir4[200];
	wchar_t bgDir5[200];
	//wstring _wsbgDir1;
	wstring _wsbgDir2;
	//wstring _wsbgDir3;
	wstring _wsbgDir4;
	wstring _wsbgDir5;

	int animTimer;
	int bgAnimIndex1;
	int chAnimIndex;
	//int bgAnimIndex3;
	bool animSwitch;
	int animLR;
	int animCount;
	int num1;



public:
	void loadSound();
	HRESULT init();
	void update();
	void animUpdate();
	void render();
	void release();
};

