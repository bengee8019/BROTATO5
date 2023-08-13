#pragma once
//#include <tchar.h>
#include "button.h"
#include "Stats.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

class statCard
{
private:
	HFONT statFont;
	HFONT oldFont;
	COLORREF tColor;
	Button* statButton;
	RECT bRect;
	Image* image;
	ULONG_PTR gdiplusToken;
	int _cardNum;		//1,2,3,4
	int _renderX, _renderY;	
	int _statType;		//1~16
	int _grade;			//0,1,2,3
	int _statUp;
	wstring _sName;
	wstring _sType;
	string _key;
	wstring _dir;
	wchar_t tempStr[50];
	wchar_t tempSType[50];
	wchar_t cDir[200];
	bool statSelect;
public:
	statCard() {}
	~statCard() {}
	void init(int x, int y, int cNum, int grade, int statNum, HFONT font);
	void addImage(wchar_t* fileName);
	void update(POINT mPt);
	void render(HDC hdc);
	void release();
	bool getStatSelect() { return statSelect; }
	int getStatType() { return _statType; }
	int getCardNum() { return _cardNum; }
	int getStatUp() { return _statUp; }
	void setStatUp(int sUp) { _statUp = sUp; }
	void setSName(wstring sname) { _sName = sname; }
	void setSType(wstring stype) { _sType = stype; }
	void setStatType(int stattype) { _statType = stattype; }
	RECT getBRect() { return bRect; }
};

