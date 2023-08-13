#include "Stdafx.h"
#include "Bullet.h"


void Bullet::init(int bX, int bY, int spd, int dmg, float angle, bool allies, int bNum, int penet)
{
	x = bX;
	y = bY;
	onFire = true;
	switch (bNum)
	{
	case 1:
	{
		bStrKey = "¿œπ›√—æÀ";
		width = 50;
		height = 50;
		break;
	}
	case 2:
	{
		bStrKey = "∑π¿Ã¿˙√—æÀ";
		width = 50;
		height = 50;
		break;
	}
	case 3:
	{
		bStrKey = "¿«∑·√—æÀ";
		width = 50;
		height = 50;
		break;
	}
	}
	bRect = RectMakeCenter(x, y, width+50, height+50);
	_dmg = dmg;
	bSpd = spd;
	bAngle = angle;
	_penet = penet;
	alley = allies;

}

void Bullet::update()
{	
	if (onFire)
	{
		x += bSpd * cosf(bAngle * M_PI / 180);
		y += bSpd * sinf(bAngle * M_PI / 180);
		bRect = RectMakeCenter(x, y, width + 50, height + 50);
	}

	if (x < 0 || x >= WINSIZE_X || y < 0 || y >= WINSIZE_Y)
	{
		onFire = false;
	}

}

void Bullet::render(HDC hdc)
{
	if (onFire)
	{
		IMAGEMANAGER->render(bStrKey, hdc, bRect.left, bRect.top, width, height, 0, 0, width, height);
	}
	//DrawRectMake(hdc, bRect);
}
