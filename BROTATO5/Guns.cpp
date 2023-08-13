#include "Stdafx.h"
#include "Guns.h"

HRESULT Guns::init(int sNum, int pX, int pY, int grade)
{
	Weapon::init(sNum, pX, pY, grade);
	return S_OK;
}

void Guns::setItem()
{
	Weapon::setItem();
}

void Guns::render(HDC hdc)
{
	Weapon::render(hdc);
}

void Guns::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
	attack();
}

void Guns::attack()
{
	Weapon::attack();
}

void Guns::release()
{
	Weapon::release();
}

void Guns::bUpdate()
{
	for (int i = 0; i < pVBullets.size();)
	{
		if (pVBullets.at(i).getOnFire() == false)
		{
			pVBullets.erase(pVBullets.begin() + i);
		}
		else
		{
			pVBullets.at(i).update();
			i++;
		}
	}
}

int Guns::hitCheck(HDC hdc, int ex, int ey)
{
	int totalDmg = 0;
	int tmpDmg = 0;
	for (int i = 0; i < pVBullets.size(); i++)
	{
		if (PtInRect(&(pVBullets.at(i).getBRect()), POINT{ ex,ey }))
		{
			if (pVBullets.at(i).getBPenet() <= 0)
			{
				pVBullets.at(i).setOnFire(false);
			}
			else
			{
				pVBullets.at(i).setBPenet(pVBullets.at(i).getBPenet() - 1);
				tmpDmg = pVBullets.at(i).getBDmg();
				totalDmg += tmpDmg;
			}
		}
	}
	if (totalDmg != 0)
	{
		SOUNDMANAGER->playSound("Impact", 0.8);
	}
	return totalDmg;
}


HRESULT ShotGun::init(int sNum, int pX, int pY, int grade)
{
	_tagWeapon = { 1,L"Resources/weapon/Gun/double_barrel_shotgunL.png",L"Resources/weapon/Gun/double_barrel_shotgunR.png" };
	itemNum = _tagWeapon.iNum;
	_fileNameL = _tagWeapon.fileNameL;
	_fileNameR = _tagWeapon.fileNameR;
	Guns::init(sNum, pX, pY, grade);


	setItem();
	return S_OK;
}

void ShotGun::setItem()
{
	
	bulletSpd = 50;
	switch (grade)
	{
	case 1:
	{
		maxBullet = 4;
		damage = 3;
		attackDelay = 137;
		_range = 350;
		_penet = 2;
		break;
	}

	case 2:
	{
		maxBullet = 4;
		damage = 6;
		attackDelay = 128;
		_range = 350;
		_penet = 2;
		break;
	}
	case 3:
	{
		maxBullet = 4;
		damage = 9;
		attackDelay = 120;
		_range = 350;
		_penet = 2;
		break;
	}
	case 4:
	{
		maxBullet = 6;
		damage = 12;
		attackDelay = 112;
		_range = 350;
		_penet = 3;
		break;
	}
	}
}

void ShotGun::render(HDC hdc)
{
	Guns::render(hdc);
	if (isLeft)
	{
		lRenderer->Render(hdc, x, y, _angle+180.0f);
	}
	else
	{
		rRenderer->Render(hdc, x, y, _angle);
	}
}

void ShotGun::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
}

void ShotGun::attack()
{
	Guns::attack();
	SOUNDMANAGER->playSound("Resources/weapon/Gun/double_barrel_shotgun.wav", 1.0);
	for (int i = 0; i < maxBullet; i++)
	{
		Bullet tmpBullet;
		tmpBullet.init(playerRX + dx, playerRY + dy, bulletSpd, damage, 45 / (maxBullet - 1) * (i-maxBullet/2) + _angle, true, 1, _penet);
		pVBullets.push_back(tmpBullet);		
	}
}

void ShotGun::release()
{
	Weapon::release();
}


HRESULT LaserGun::init(int sNum, int pX, int pY, int grade)
{
	_tagWeapon = { 2,L"Resources/weapon/Gun/laser_gunL.png",L"Resources/weapon/Gun/laser_gunR.png" };
	itemNum = _tagWeapon.iNum;
	_fileNameL = _tagWeapon.fileNameL;
	_fileNameR = _tagWeapon.fileNameR;
	Guns::init(sNum, pX, pY, grade);


	setItem();
	return S_OK;
}

void LaserGun::setItem()
{
	bulletSpd = 70;
	switch (grade)
	{
	case 1:
	{
		damage = 30;
		attackDelay = 223;
		_range = 500;
		_penet = 1;
		break;
	}

	case 2:
	{
		damage = 45;
		attackDelay = 215;
		_range = 500;
		_penet = 1;
		break;
	}
	case 3:
	{
		damage = 60;
		attackDelay = 207;
		_range = 500;
		_penet = 1;
		break;
	}
	case 4:
	{
		damage = 90;
		attackDelay = 190;
		_range = 500;
		_penet = 1;
		break;
	}
	}

}

void LaserGun::render(HDC hdc)
{
	Guns::render(hdc);
	if (isLeft)
	{
		lRenderer->Render(hdc, x, y, _angle + 180.0f);
	}
	else
	{
		rRenderer->Render(hdc, x, y, _angle);
	}
}

void LaserGun::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
}

void LaserGun::attack()
{
	Guns::attack();
	SOUNDMANAGER->playSound("LaserGun", 0.8);
	Bullet tmpBullet;
	tmpBullet.init(playerRX + dx, playerRY + dy, bulletSpd, damage, _angle, true, 2, _penet);
	pVBullets.push_back(tmpBullet);
}

void LaserGun::release()
{
	Guns::release();
}


HRESULT MedicalGuns::init(int sNum, int pX, int pY, int grade)
{
	_tagWeapon = { 3,L"Resources/weapon/Gun/medical_gunL.png",L"Resources/weapon/Gun/medical_gunR.png" };
	itemNum = _tagWeapon.iNum;
	_fileNameL = _tagWeapon.fileNameL;
	_fileNameR = _tagWeapon.fileNameR;
	Guns::init(sNum, pX, pY, grade);

	setItem();
	return S_OK;
}

void MedicalGuns::setItem()
{
	bulletSpd = 60;
	switch (grade)
	{
	case 1:
	{
		damage = 10;
		attackDelay = 95;
		_range = 400;
		healRate = 40;
		_penet = 1;
		break;
	}

	case 2:
	{
		damage = 15;
		attackDelay = 87;
		_range = 400;
		healRate = 45;
		_penet = 1;
		break;
	}
	case 3:
	{
		damage = 20;
		attackDelay = 78;
		_range = 400;
		healRate = 50;
		_penet = 1;
		break;
	}
	case 4:
	{
		damage = 30;
		attackDelay = 62;
		_range = 400;
		healRate = 60;
		_penet = 1;
		break;
	}
	}
}

void MedicalGuns::render(HDC hdc)
{
	Guns::render(hdc);
	if (isLeft)
	{
		lRenderer->Render(hdc, x, y, _angle + 180.0f);
	}
	else
	{
		rRenderer->Render(hdc, x, y, _angle);
	}
}

void MedicalGuns::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
}

void MedicalGuns::attack()
{
	Guns::attack();
	SOUNDMANAGER->playSound("MedicalGun", 0.8);
	Bullet tmpBullet;
	tmpBullet.init(playerRX + dx, playerRY + dy, bulletSpd, damage, _angle, true, 3, _penet);
	pVBullets.push_back(tmpBullet);
}

void MedicalGuns::release()
{
	Guns::release();
}

HRESULT SubMachineGun::init(int sNum, int pX, int pY, int grade)
{
	_tagWeapon = { 4,L"Resources/weapon/Gun/smgL.png",L"Resources/weapon/Gun/smgR.png" };
	itemNum = _tagWeapon.iNum;
	_fileNameL = _tagWeapon.fileNameL;
	_fileNameR = _tagWeapon.fileNameR;
	Guns::init(sNum, pX, pY, grade);
	setItem();
	return S_OK;
}

void SubMachineGun::setItem()
{
	bulletSpd = 50;
	switch (grade)
	{
	case 1:
	{
		damage = 3;
		attackDelay = 17;
		_range = 400;
		_penet = 1;
		break;
	}

	case 2:
	{
		damage = 4;
		attackDelay = 17;
		_range = 400;
		_penet = 1;
		break;
	}
	case 3:
	{
		damage = 5;
		attackDelay = 17;
		_range = 400;
		_penet = 1;
		break;
	}
	case 4:
	{
		damage = 8;
		attackDelay = 15;
		_range = 400;
		_penet = 1;
		break;
	}
	}
}


void SubMachineGun::render(HDC hdc)
{
	Guns::render(hdc);
	if (isLeft)
	{
		lRenderer->Render(hdc, x, y, _angle + 180.0f);
	}
	else
	{
		rRenderer->Render(hdc, x, y, _angle);
	}
}

void SubMachineGun::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
}

void SubMachineGun::attack()
{
	Guns::attack();
	SOUNDMANAGER->playSound("SMG", 0.8);
	Bullet tmpBullet;
	tmpBullet.init(playerRX + dx, playerRY + dy, bulletSpd, damage, _angle, true, 1, _penet);
	pVBullets.push_back(tmpBullet);
}

void SubMachineGun::release()
{
	Weapon::release();
}


HRESULT PistolGuns::init(int sNum, int pX, int pY, int grade)
{
	_tagWeapon = { 5,L"Resources/weapon/Gun/pistolL.png",L"Resources/weapon/Gun/pistolR.png" };
	itemNum = _tagWeapon.iNum;
	_fileNameL = _tagWeapon.fileNameL;
	_fileNameR = _tagWeapon.fileNameR;
	Guns::init(sNum, pX, pY, grade);
	setItem();
	return S_OK;
}

void PistolGuns::setItem()
{
	bulletSpd = 50;
	switch (grade)
	{
	case 1:
	{
		damage = 12;
		attackDelay = 120;
		_range = 400;
		_penet = 1;
		break;
	}

	case 2:
	{
		damage = 24;
		attackDelay = 112;
		_range = 400;
		_penet = 1;
		break;
	}
	case 3:
	{
		damage = 36;
		attackDelay = 103;
		_range = 400;
		_penet = 1;
		break;
	}
	case 4:
	{
		damage = 55;
		attackDelay = 87;
		_range = 400;
		_penet = 1;
		break;
	}
	}

}

void PistolGuns::render(HDC hdc)
{
	Guns::render(hdc);
	if (isLeft)
	{
		lRenderer->Render(hdc, x, y, _angle + 180.0f);
	}
	else
	{
		rRenderer->Render(hdc, x, y, _angle);
	}
}

void PistolGuns::update(int pX, int pY, bool pLeft)
{
	Weapon::update(pX, pY, pLeft);
}

void PistolGuns::attack()
{
	Guns::attack();
	SOUNDMANAGER->playSound("Pistol", 0.8);
	Bullet tmpBullet;
	tmpBullet.init(playerRX + dx, playerRY + dy, bulletSpd, damage, _angle, true, 1, _penet);
	pVBullets.push_back(tmpBullet);
}

void PistolGuns::release()
{
	Weapon::release();
}
