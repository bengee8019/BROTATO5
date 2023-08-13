#pragma once
#include "Player.h"
#include "Button.h"

class AInventory : public Player
{
private:
	vector<Button*> vAButton;
	int x, y;
public:
	HRESULT init(int iNum, int x, int y);
	void equipAcc(int iNum);
	void update(POINT mPt);
	void render(HDC hdc);
	void release();

};

