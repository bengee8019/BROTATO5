#pragma once
#include "Items.h"
#include "rotateRender.h"
struct tagWeapon
{
	int iNum;
	wchar_t* fileNameL;
	wchar_t* fileNameR;
};

class Weapon : public Items
{
protected:
	tagWeapon _tagWeapon;
	rotateRender* rRenderer;
	rotateRender* lRenderer;
	wchar_t* _fileNameL;
	wchar_t* _fileNameR;

	int x, y;
	int playerX, playerY;
	int playerRX, playerRY;
	int dx, dy;
	int itemNum;
	int slotNum;

	float _angle;
	float dAngle;
	bool isLeft;
	bool dIsLeft;

	int _range;
	int attackDelay;
	int coolDownCount;
	int damage;
	int extraDamage;

	bool isIdle;
	bool isFire;
public:
	Weapon();
	~Weapon();
	virtual HRESULT init(int sNum, int pX, int pY, int grade);
	virtual void setItem();
	virtual void update(int pX, int pY, bool pLeft);
	virtual void render(HDC hdc);
	virtual void attack();
	virtual void release();

	void setWX(int wx) { x = wx; }
	int getWX() { return x; }
	void setWY(int wy) { y = wy; }
	int getWY() { return y; }
	void setPlayerX(int rx) { playerX = rx; }
	void setPlayerY(int ry) { playerY = ry; }
	void setPlayerRX(int prx) { playerRX = prx; }
	void setPlayerRY(int pry) { playerRY = pry; }

	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }
	int getRange() { return _range; }
	void setRange(int range) { _range = range; }
	int getSNum() { return slotNum; }
	void setSNum(int sNum) { slotNum = sNum; }
	void setIdle(bool idle) { isIdle = idle; }
	bool getIsFire() { return isFire; }
	void setIsFire(bool isfire) { isFire = isfire; }

};

