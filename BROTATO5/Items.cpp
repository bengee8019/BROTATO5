#include "Stdafx.h"
#include "Items.h"

HRESULT Items::init(int iNum)
{
	itemNum = iNum;
	if (iNum <= 20)
	{
		isWeapon = true;
	}
	else
	{
		isWeapon = false;
	}

	return S_OK;
}

void Items::render()
{
	//¾ÆÀÌÄÜ ·»´õ
}

void Items::setItem()
{
}

void Items::release()
{
}
