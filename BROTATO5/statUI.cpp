#include "Stdafx.h"
#include "statUI.h"

void statUI::init(HFONT font1, HFONT font2, tagUpStat* tagupstat)
{
	titleFont = font1;
	statFont = font2;
	for (int i = 0; i < 16; i++)
	{
		_upStats[i] = tagupstat[i]._sType;
	}
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	gdiplusToken = 0;
	IMAGEMANAGER->addImage("½ºÅÈbg","Resources/stats/stats.bmp", 411, 740, true, RGB(255, 0, 255));
	primary = true;
	wSTitle = L"´É·ÂÄ¡";
	wcscpy_s(titleStr, 200, wSTitle.c_str());
	for (int i = 0; i < 16; i++)
	{
		//_dir.clear();
		_dir = L"Resources/stats/_" + to_wstring(i + 1)+ L".png";
		//fill_n(sDir, 200, 0);
		wcscpy_s(sDir, 200, _dir.c_str());
		Image* tmpImage = Image::FromFile(sDir);
		vImage.push_back(tmpImage);
	}
	_stats = { 0, };
}

void statUI::update(tagStats pStats)
{
	for (int i = 0; i < 36; i++)
	{
		_stats[i] = pStats[i];
	}
}

void statUI::render(HDC hdc, int x, int y)
{
	Gdiplus::Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	IMAGEMANAGER->alphaRender("½ºÅÈbg", hdc, x, y, 220);
	oldFont = (HFONT)SelectObject(hdc, titleFont);
	for (int i = 0; i < 20; i++)
	{
		statRect[i] = RectMake(x + 80, y + 120 + i * 36, 300, 36);
	}

	SetTextColor(hdc, RGB(255, 255, 255));
	TextOutW(hdc, x + 130, y + 10, titleStr, wcslen(titleStr));
	SelectObject(hdc, statFont);
	if (primary)
	{
		for (int i = 0; i < 16; i++)
		{
			fill_n(statStr,30,NULL);
			wcscpy_s(statStr, 30, to_wstring(_stats[i]).c_str());
			graphics.DrawImage(vImage[i], x + 30, y + 125 + i * 36,36,36);
			setColor(hdc, _stats[i]);
			DrawTextW(hdc, _upStats[i].c_str(), wcslen(_upStats[i].c_str()),&statRect[i],DT_LEFT);
			DrawTextW(hdc, statStr, wcslen(statStr), &statRect[i], DT_RIGHT);
			//TextOutW(hdc, x + 80, y + 160 + i * 40, _upStats[i].c_str(), wcslen(_upStats[i].c_str()));
		}
	}
	else
	{

	}
	SetTextColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
}

void statUI::setColor(HDC hdc, int stat)
{
	if (stat == 0)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
	}
	else if (stat < 0)
	{
		SetTextColor(hdc, RGB(0, 240, 120));
	}
	else
	{
		SetTextColor(hdc, RGB(80, 221, 94));
	}
}

void statUI::release()
{
	for (auto it = vImage.begin(); it != vImage.end();)
	{
		SAFE_DELETE((*it));
		it=vImage.erase(it);
	}
	if (gdiplusToken)
	{
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

}
