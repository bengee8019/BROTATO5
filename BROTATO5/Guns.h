#pragma once
#include "Weapon.h"
#include "Bullet.h"

class Guns : public Weapon
{
protected:
	//vector<Bullet> pVBullets;
	//vector<Bullet*> wVBullets;
	int bulletSpd;
	int _penet;

public:
	virtual HRESULT init(int sNum, int pX, int pY, int grade);  //무기 슬롯 번호, 플레이어 위치 x,y
	virtual void setItem();	//
	virtual void render(HDC hdc);
	virtual void update(int pX, int pY, bool pLeft);
	virtual void attack();
	virtual void release();
	//vector<Bullet> getPVBullets() { return pVBullets; }
	void bUpdate();
	int hitCheck(HDC hdc, int ex, int ey);
	//void bRender();
};

class ShotGun : public Guns
{
private:
	int maxBullet;

public:
	HRESULT init(int sNum, int pX, int pY, int grade);  //무기 슬롯 번호, 플레이어 위치 x,y
	void setItem();	
	void render(HDC hdc);
	void update(int pX, int pY, bool pLeft);
	void attack();
	void release();
};

class LaserGun : public Guns
{
private:

public:
	HRESULT init(int sNum, int pX, int pY, int grade);  //무기 슬롯 번호, 플레이어 위치 x,y
	void setItem();
	void render(HDC hdc);
	void update(int pX, int pY, bool pLeft);
	void attack();
	void release();
};

class MedicalGuns : public Guns
{
private:
	int healRate;
public:
	HRESULT init(int sNum, int pX, int pY, int grade);
	void setItem();
	void render(HDC hdc);
	void update(int pX, int pY, bool pLeft);
	void attack();
	void release();
};
//
//

//};
//class ShredderGuns : public Weapon
//{
//private:
//	int bulletSpd;
//public:
//	HRESULT init(int sNum, int pX, int pY);
//	void setItem(int iNum, string strKey);
//	void render(HDC hdc);
//	void attack();
//	void release();
//
//};
class SubMachineGun : public Guns
{
private:

public:
	HRESULT init(int sNum, int pX, int pY, int grade);  //무기 슬롯 번호, 플레이어 위치 x,y
	void setItem();
	void render(HDC hdc);
	void update(int pX, int pY, bool pLeft);
	void attack();
	void release();
};

class PistolGuns : public Guns
{
private:

public:
	HRESULT init(int sNum, int pX, int pY, int grade);
	void setItem();
	void render(HDC hdc);
	void update(int pX, int pY, bool pLeft);
	void attack();
	void release();
};
