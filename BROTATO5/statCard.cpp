#include "Stdafx.h"
#include "statCard.h"


//statup ��ġ ǥ���ϱ� ���� ������ ����

void statCard::init(int x, int y, int cNum, int grade, int statNum ,HFONT font)
{

	statFont = font;
	_sName += L" ";
	_sName += to_wstring(grade);

	switch (grade)
	{
	case 1:
	{
		_key = "����1";
		tColor = RGB(255, 255, 255);
		break;
	}
	case 2:
	{
		_key = "����2";
		tColor = RGB(90, 190, 255);
		break;
	}

	case 3:
	{
		_key = "����3";
		tColor = RGB(173, 90, 255);
		break;
	}

	case 4:
	{
		_key = "����4";
		tColor = RGB(255, 0, 0);
		break;
	}
	}
	_sType = L"+" + to_wstring(_statUp) + _sType;

	_dir = L"Resources/stats/";
	_dir += to_wstring(statNum);
	_dir += L".png";
	
	wcscpy_s(cDir, 200, _dir.c_str());
	wcscpy_s(tempStr, 50, _sName.c_str());
	wcscpy_s(tempSType, 50, _sType.c_str());
	_cardNum = cNum;
	_grade = grade;
	_statType = statNum;
	_renderX = x + (_cardNum-1) * 370;
	_renderY = y;
	statSelect = false;
	// ���� ��ư ����
	statButton = new Button;
	statButton->setButton(_renderX+22, _renderY+200, 321, 45, "����1", "����2", "Resources/button/select1.bmp", "Resources/button/select2.bmp", _cardNum);
	bRect = statButton->getArea();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	gdiplusToken = 0;
	addImage(cDir);
}

void statCard::addImage(wchar_t* fileName)
{
	image = Image::FromFile(fileName);
}

void statCard::update(POINT mPt)
{
	statButton->update(mPt);
}

void statCard::render(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	IMAGEMANAGER->render(_key, hdc, _renderX, _renderY);
	SetTextColor(hdc, tColor);
	oldFont = (HFONT)SelectObject(hdc, statFont);
	TextOutW(hdc, _renderX + 130, _renderY + 10, tempStr, wcslen(tempStr));
	SetTextColor(hdc, RGB(255,255,255));
	TextOutW(hdc, _renderX + 20, _renderY + 150, tempSType, wcslen(tempSType));
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.DrawImage(image, _renderX +20, _renderY + 20 );
	statButton->render(hdc);
}

void statCard::release()
{
	SAFE_DELETE(image);
	if (gdiplusToken)
	{
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
}
