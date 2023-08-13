#pragma once
class Bullet
{
private:
	char* bStrKey;
	int x, y;
	RECT bRect;
	float bAngle;
	int width, height;
	bool onFire;
	int bSpd;
	int _dmg;
	int _penet;
	bool alley;

public:
	void init(int bX, int bY, int spd, int dmg, float angle, bool allies, int bNum, int penet);
	void update();
	void render(HDC hdc);

	bool getOnFire() { return onFire; }
	void setOnFire(bool onfire) { onFire = onfire; }

	RECT getBRect() { return bRect; }
	int getBDmg() { return _dmg; }
	int getBPenet() { return _penet; }
	void setBPenet(int penet) { _penet = penet; }



};

