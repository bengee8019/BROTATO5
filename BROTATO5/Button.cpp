#include "Stdafx.h"
#include "Button.h"


void Button::setButton(int x, int y, int width, int height, string key1, string key2, char* dir1, char* dir2, int sNum)
{
	IMAGEMANAGER->addImage(key1, dir1, width, height, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(key2, dir2, width, height, true, RGB(255, 0, 255));
	_bArea = RectMake(x,y,width,height);
	_key1 = key1;
	_key2 = key2;
	_sNum = sNum;
	_bOnMouse = false;
	_bSelect = false;
	_onSound = false;
	_active = true;
}

void Button::render(HDC hdc)
{
	if (_active)
	{
		if (_bOnMouse)
		{
			IMAGEMANAGER->render(_key2, hdc, _bArea.left, _bArea.top);
		}
		else
		{
			IMAGEMANAGER->render(_key1, hdc, _bArea.left, _bArea.top);
		}
	}
	else
	{
		IMAGEMANAGER->render(_key1, hdc, _bArea.left, _bArea.top);
	}
}

void Button::update(POINT mPt)
{
	if (_active)
	{
		if (PtInRect(&_bArea, mPt))
		{
			if (!_onSound)
			{
				SOUNDMANAGER->playSound("onButton", 0.8);
				_onSound = true;
			}
			_bOnMouse = true;
		}
		else
		{
			_onSound = false;
			_bOnMouse = false;
		}
	}
}

Button::Button()
{
}

Button::~Button()
{
	IMAGEMANAGER->deleteImage(_key1);
	IMAGEMANAGER->deleteImage(_key2);
}
