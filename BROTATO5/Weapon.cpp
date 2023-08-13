#include "Stdafx.h"
#include "Weapon.h"

//void Weapon::setItem(int iNum)
//{
//	//itemNum에 따른 아이템 값 초기화
//}

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

HRESULT Weapon::init(int sNum, int pX, int pY, int grade)
{
	Items::init(itemNum);
	rRenderer = new rotateRender;
	lRenderer = new rotateRender;

	rRenderer->init();
	lRenderer->init();
	rRenderer->addImage(_fileNameR);
	lRenderer->addImage(_fileNameL);

	slotNum = sNum;
	this->grade = grade;

	coolDownCount = 0;
	isIdle = true;
	dIsLeft = false;
	dAngle = 0.0f;
	isLeft = dIsLeft;
	_angle = dAngle;
	isFire = false;
	//isLeft = dIsLeft;
	//_angle = 0;
	
	switch (sNum)
	{
	case 1:
	{
		x = pX + 50 * sinf(300.0f * M_PI / 180);
		y = pY + 50 * cosf(300.0f * M_PI / 180);
		break;
	}
	case 2:
	{
		x = pX + 50 * sinf(240.0f * M_PI / 180);
		y = pY + 50 * cosf(240.0f * M_PI / 180);
		break;
	}
	case 3:
	{
		x = pX + 50 * sinf(0.0f * M_PI / 180);
		y = pY + 50 * cosf(0.0f * M_PI / 180);
		break;
	}
	case 4:
	{	
		x = pX + 50 * sinf(180.0f * M_PI / 180);
		y = pY + 50 * cosf(180.0f * M_PI / 180);
		break;
	}
	case 5:
	{
		x = pX + 50 * sinf(60.0f * M_PI / 180);
		y = pY + 50 * cosf(60.0f * M_PI / 180);
		break;
	}
	case 6:
	{
		x = pX + 50 * sinf(120.0f * M_PI / 180);
		y = pY + 50 * cosf(120.0f * M_PI / 180);
		break;
	}

	}

	return S_OK;
}

void Weapon::setItem()
{
}

void Weapon::update(int pX, int pY, bool pLeft)
{
	//if (KEYMANAGER->isToggleKey(VK_SPACE))
	//{
	//	isIdle = !isIdle;
	//}
	switch (slotNum)
	{
	case 1:
	{
		dx = 25 + 60 * cosf(300.0f * M_PI / 180);
		dy = 25 + 60 * sinf(260.0f * M_PI / 180);
		break;
	}
	case 2:
	{
		dx = 25 + 60 * cosf(240.0f * M_PI / 180);
		dy = 25 + 60 * sinf(240.0f * M_PI / 180);
		break;
	}
	case 3:
	{
		dx = 25 + 60 * cosf(0.0f * M_PI / 180);
		dy = 25 + 60 * sinf(0.0f * M_PI / 180);
		break;
	}
	case 4:
	{
		dx = 25 + 60 * cosf(180.0f * M_PI / 180);
		dy = 25 + 60 * sinf(180.0f * M_PI / 180);
		break;
	}
	case 5:
	{
		dx = 25 + 60 * cosf(60.0f * M_PI / 180);
		dy = 25 + 60 * sinf(60.0f * M_PI / 180);
		break;
	}
	case 6:
	{
		dx = 25 + 60 * cosf(120.0f * M_PI / 180);
		dy = 25 + 60 * sinf(120.0f * M_PI / 180);
		break;
	}
	}
	x = pX + dx;
	y = pY + dy;
	
	//_angle += 1.0f;

	
	coolDownCount++;

	if (isIdle)
	{
		if (pLeft)
		{
			_angle = 180.0f;
		}
		else
		{
			_angle = 0.0f;
		}
	}
	else
	{
		if (coolDownCount >= attackDelay)
		{
			coolDownCount = 0;
			attack();			
		}
	}

	if (_angle > 360.0f)
	{
		_angle -= 360.0f;
	}
	if (_angle < 0.0f)
	{
		_angle += 360.0f;
	}
	if (_angle >= 270.0f || _angle < 90.0f)
	{
		isLeft = false;
	}
	else
	{
		isLeft = true;
	}
}

void Weapon::render(HDC hdc)
{
}

void Weapon::attack()
{
}

void Weapon::release()
{
	rRenderer->release();
	lRenderer->release();
}
