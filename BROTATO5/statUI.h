#pragma once
#include "Player.h"
#include "Button.h"
#include "Stats.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;


class statUI
{
private:
	tagStats _stats;
	wstring _upStats[16];
	vector<Image*> vImage;
	ULONG_PTR gdiplusToken;
	wstring wSTitle;
	wchar_t titleStr[200];
	wchar_t statStr[30];
	wstring _dir;
	wchar_t sDir[200];
	bool primary;
	HFONT titleFont;
	HFONT statFont;
	HFONT oldFont;
	RECT statRect[20];

public:
	void init(HFONT font1, HFONT font2, tagUpStat* tagupstat);
	void update(tagStats pStats);
	void render(HDC hdc, int x, int y);
	void setColor(HDC hdc, int stat);
	void release();
};

