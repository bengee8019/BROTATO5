#pragma once
#include "Stats.h"

//#include "Guns.h"
class Items
{
protected:
	int itemNum;
	int grade;
	bool isWeapon;
	int price;
	string itemName;
	tagStats iStats;
	//Guns* _shot
public:
	virtual HRESULT init(int iNum);
	virtual void render();
	virtual void setItem();
	virtual void release();

	int getINum() { return itemNum; }
	tagStats getStats() { return iStats; }
};

