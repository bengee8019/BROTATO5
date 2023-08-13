#include "Stdafx.h"
#include "FontManager.h"

//void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
//{
//	//배경 투명
//	SetBkMode(hdc, TRANSPARENT);
//
//	HFONT font;
//	HFONT oldFont;
//
//	SetTextColor(hdc, color);
//	const int stringLength = strlen(printString);
//	wchar_t charBuffer[256];
//
//	/*문자크기, 문자폭, 기울기(전체), 문자 방향, 문자 굵기,
//		기울기(t / f), 밑줄(t / f), 취소선,
//		문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질,
//		자간, 폰트*/
//
//	font = CreateFont(fontSize, 0, 0, 0, fontWeight, 0, 0, 0, HANGEUL_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, fontName);
//	oldFont = (HFONT)SelectObject(hdc, font);
//	
//	ZeroMemory(charBuffer, sizeof(charBuffer)/sizeof(wchar_t));
//	mbstowcs(charBuffer, printString, stringLength);
//	TextOutW(hdc, destX, destY, charBuffer, wcslen(charBuffer));
//
//	SelectObject(hdc, oldFont);
//	DeleteObject(font);
//}

//void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
//{
//}
//
//void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printStringArr, int length, COLORREF color)
//{
//	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
//
//	int lineCount = 0;
//
//	for (int i = 0; i < arraySize; i++)
//	{
//		if (i==0)
//		{
//			if ()
//			{
//				SetBkMode(hdc, TRANSPARENT);
//
//				auto font = (HFONT)SelectObject(hdc, font);
//				auto oldFont = ;
//
//				SetTextColor(hdc, color);
//
//			}
//			else
//			{
//				break;
//			}
//		}
//		else
//		{
//
//		}
//	}
//}

void FontManager::setFont(int fSize, char* fontName)
{
	font = CreateFont(fSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, fontName);
}

void FontManager::dpText(HDC hdc, int destX, int destY, char* str)
{
	//char* tempStr = str;
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, font);
	TextOut(hdc, destX, destY, str, strlen(str));
}
