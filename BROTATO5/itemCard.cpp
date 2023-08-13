#include "Stdafx.h"
#include "itemCard.h"

void itemCard::init(int iNum, int iGrade, int nowround, string ikey,int sNum)
{
	_itemNum = iNum;
	_itemGrade = iGrade;
	_itemPrice = 15 * iGrade + nowround;
	_price = _itemPrice;
	_iKey = ikey;
	_isSoldOut = false;
	_slotNum = sNum;
}

void itemCard::update()
{
	if (!_isSoldOut)
	{

	}
}

void itemCard::render(HDC hdc)
{
	if (!_isSoldOut)
	{
		
		IMAGEMANAGER->render(_iKey, hdc, -340 + _slotNum * 360, 250);
	}
}

void itemCard::release()
{
}
