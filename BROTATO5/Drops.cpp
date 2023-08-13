#include "Stdafx.h"
#include "Drops.h"

void Drops::init(bool isitem, int x, int y, int gold, int exp)
{
	_key = "µå·Ó½º";
	int tmpInt = RND->getInt(3);
	_key += to_string(tmpInt);
	_onRender = true;
	_isItem = isitem;
	_x = x;
	_y = y;
	_cX = 0;
	_cY = 0;
	width = 40;
	height = 40;
	_px = 0;
	_py = 0;
	_gold = gold;
	_exp = exp;
	_range = 0;
}

//void Drops::setPInfo(int px, int py, int range)
//{
//	_px = px;
//	_py = py;
//	_range = range*10;
//}

void Drops::render(HDC hdc)
{
	if (_onRender)
	{
		IMAGEMANAGER->render(_key, hdc, _x - _cX - width / 2 + WINSIZE_X / 2, _y - _cY - height / 2 + WINSIZE_Y / 2, 0, 0, width, height);
	}
}

void Drops::update()
{
	int tmpDist = sqrtf(pow(_px - _x, 2) + pow(_py - _y, 2));
	if(tmpDist <=_range)
	{

		float angle = atan2f((_py - _y), (_px - _x));
		_x += 20 * cosf(angle);
		_y += 20 * sinf(angle);
	}
	if (tmpDist <= 30)
	{
		_onRender = false;
	}
	//cout << tmpDist << endl;
}


void Drops::release()
{
}
