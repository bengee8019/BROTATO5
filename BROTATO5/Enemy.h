#pragma once
#include "Drops.h"

class Enemy
{
protected:
	//vector<Drops> vDrops;

	int _enemyNum;
	int _roundNum;
	int _eType;
	int _Count;
	int eX, eY;
	int renderEX, renderEY;
	RECT eRect;
	int animRender;
	float _angle;
	bool onMoveX;
	bool onMoveY;
	bool onRender;
	int eWidth, eHeight;
	int _hp;
	int _eDmg;
	int _eSpd;
	int rInt;
	int _dropIng;
	int _dropGold;
	int _dropExp;

	bool isSpawning;
	bool isAlive;
	int knockBack;

public:
	HRESULT init(int roundnum);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	void spawn();
	void death();
	void drop();

	int getEHp() { return _hp; }
	void setEHp(int ehp) { _hp = ehp; }

	void setENum(int eNum) { _enemyNum = eNum; }
	int getENum() { return _enemyNum; }

	int getX() { return eX; }
	void setX(int x) { eX = x; }
	int getY() { return eY; }
	void setY(int y) { eY = y; }

	int getREX() { return renderEX; }
	void setREX(int rex) { renderEX = rex; }
	int getREY() { return renderEY; }
	void setREY(int rey) { renderEY = rey; }

	bool getAlive() { return isAlive; }
	void setOnRender(bool onOff) { onRender = onOff; }

	void setOnMoveX(bool onmovex) { onMoveX = onmovex; }
	bool getOnMoveX() { return onMoveX; }
	void setOnMoveY(bool onmovey) { onMoveY = onmovey; }
	bool getOnMoveY() { return onMoveY; }

	void setAngle(float angle) { _angle = angle; }
	int getEDmg() { return _eDmg; }

	void setKnockBack(int knockback) { knockBack = knockback; }

	RECT getERect() { return eRect; }
	//vector<Drops> getDropsVector() { return vDrops; }
	tagDrop dropCheck(int pgold, int pexp);
	void dropSet(int px, int py, int cx, int cy, int range);
	//void roundEnd();
	//void dUpdate();
};

