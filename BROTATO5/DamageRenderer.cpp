#include "Stdafx.h"
#include "DamageRenderer.h"

void DamageRenderer::init(int dmg, int x, int y)
{
	_dmg = dmg;
	tmpStr = to_string(_dmg);
	strcpy_s(cstr, 10, tmpStr.c_str());
	_x = x;
	_y = y;
	CameraX = 0;
	CameraY = 0;
	_renderX = 0;
	_renderY = 0;
	_tickCount = 10;
	hitFrame = 0;
	_timeOut = false;
}

void DamageRenderer::update(int cX, int cY)
{
	_tickCount--;
	_renderX = _x - cX + WINSIZE_X / 2;
	_renderY = _y - cY + WINSIZE_Y / 2;
	if (_tickCount < 8)
	{
		hitFrame = 1;
	}
	else if(_tickCount < 6)
	{
		hitFrame = 2;
	}
	if (_tickCount < 0)
	{
		_timeOut = true;
	}
}

void DamageRenderer::render(HDC hdc)
{
	if (!_timeOut)
	{
		if (_tickCount > 4)
		{
			IMAGEMANAGER->frameRender("È÷Æ®", hdc, _renderX - 80, _renderY - 80, hitFrame, 0);
		}
		TextOut(hdc, _renderX, _renderY, cstr, strlen(cstr));
	}
}

DamageRenderer::DamageRenderer()
{
}

DamageRenderer::~DamageRenderer()
{
}
