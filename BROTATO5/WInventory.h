#pragma once
#include "Weapon.h"
#include "Button.h"

class WInventory
{
private:
	vector<Button*> vWButton;
	int x, y;
	//string key[6];

public:
	HRESULT init(int x, int y);
	void equipWeapon(int iNum, int sNum, int grade);
	void update(POINT mPt);
	void render(HDC hdc);
	void release();

	WInventory() {}
	~WInventory() {}
};

