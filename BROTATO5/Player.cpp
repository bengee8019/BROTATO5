#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(int prole)
{
	//EWeapon.resize(6);

	//플레이어 스탯 초기화
	pStats = { 0, };
	//기본 체력 10, 스피드 6
	pStats.maxHp = 10;
	_spd = 6;

	count = 0;
	levelUpCount = 0;
	_hp = pStats.maxHp;
	_exp = 0;
	pLevel = 1;
	maxExp = 10;
	_gold = 0;
	x = 1400;
	y = 800;
	_death = false;
	isLeft = false;
	_baseRange = 10;
	_range = _baseRange * (100 + pStats.gainRange) / 100;

	//임시
	renderX = WINSIZE_X / 2;
	renderY = WINSIZE_Y / 2;

	weaponIndex = 0;
	pHeight = 0;
	animHeight = 0;
	bAnim = true;
	onMoveX = true;
	onMoveY = true;


	switch (prole)
	{
	case 2:
	{
		IMAGEMANAGER->addImage("플레이어", "Resources/player/60px-Well_Rounded.bmp", 120, 60, true, RGB(255, 0, 255));
	}
	case 3:
	{
		IMAGEMANAGER->addImage("플레이어", "Resources/player/60px-Ranger.bmp", 120, 60, true, RGB(255, 0, 255));
	}
	case 4:
	{
		IMAGEMANAGER->addImage("플레이어", "Resources/player/60px-Engineer.bmp", 120, 60, true, RGB(255, 0, 255));
	}
	}
	//iNum 0: 미장착 //1 샷건 //2 레이저건
	//1 샷건 테스트 
	//equipWeapon(1, 1, 1);
	////2 레이저건 테스트
	//equipWeapon(2, 2, 1);
	////3 메디컬건 테스트
	//equipWeapon(3, 3, 1);
	////4 SMG 테스트
	//equipWeapon(4, 4, 1);
	////5 pistol 테스트
	//equipWeapon(5, 5, 1);
	//equipWeapon(5, 6, 1);



	return S_OK;
}

void Player::update()
{
	pRect = RectMakeCenter(x, y, 60, 60);

	if (!_stop&&!_death)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (x > 70)
			{
				x -= _spd;
				isLeft = true;
				if (!onMoveX)
				{
					renderX -= _spd;
				}
			}
			else
			{
				x = 70;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (x < 2670)
			{
				x += _spd;
				isLeft = false;
				if (!onMoveX)
				{
					renderX += _spd;
				}
			} 
			else
			{
				x = 2670;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (y > 70)
			{
				y -= _spd;
				if (!onMoveY)
				{
					renderY -= _spd;
				}
			}
			else
			{
				y = 70;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (y < 1470)
			{
				y += _spd;
				if (!onMoveY)
				{
					renderY += _spd;
				}
			}
			else
			{
				y = 1470;
			}
		}
	if (onMoveX)
	{
		renderX = WINSIZE_X / 2-30;
	}
	if (onMoveY)
	{
		renderY = WINSIZE_Y / 2-30;
	}
	count++;
	if (count % 3 == 0)
	{
		if (pHeight > 0 || pHeight < -10)
		{
			bAnim = !bAnim;
		}
		if (bAnim)
		{
			pHeight--; 
		}
		else
		{
			pHeight++;
		}
	}
	animHeight = renderY + pHeight;

	for (auto it = EWeapon.begin(); it != EWeapon.end(); ++it)
	{
		if ((*it)== NULL)
		{
			continue;
		}
		(*it)->setPlayerX(x);
		(*it)->setPlayerY(y);
		(*it)->update(renderX, renderY, isLeft );
		(*it)->setPlayerRX(renderX);
		(*it)->setPlayerRY(renderY);
	}
	}
}

void Player::render()
{
	if (!_death)
	{
		if (!isLeft)
		{
			IMAGEMANAGER->render("플레이어", getMemDC(), renderX, animHeight, 60, 60 - pHeight, 0, 0, 60, 60);
		}
		else
		{
			IMAGEMANAGER->render("플레이어", getMemDC(), renderX, animHeight, 60, 60 - pHeight, 60, 0, 60, 60);
		}
		for (auto it = EWeapon.begin(); it != EWeapon.end(); ++it)
		{
			if ((*it) == NULL)
			{
				continue;
			}
			(*it)->render(getMemDC());
		}
	}
	else
	{

	}
}

void Player::release()
{
}

void Player::setNewRound()
{
	count = 0;
	levelUpCount = 0;
	_hp = pStats.maxHp;

	x = 1400;
	y = 800;


	_death = false;
	isLeft = false;
	_stop = false;
	renderX = WINSIZE_X / 2;
	renderY = WINSIZE_Y / 2;
	onMoveX = true;
	onMoveY = true;

	_range = _baseRange * (100 + pStats.gainRange) / 100;

	//wx 초기화
	//for (int i = 0; i < weaponIndex; i++)
	//{
	//	EWeapon.at(i)->setWX(x);
	//	EWeapon.at(i)->setWY(y);
	//}

}

void Player::equipWeapon(int iNum, int sNum, int grade)
{
	if (weaponIndex >= 6)
	{
		return;
	}
	weaponIndex++;
	Weapon* _weapon;

	switch (iNum)
	{
	case 1:
	{
		_weapon = new ShotGun;
		_weapon->init(sNum, renderX, renderY, grade);
		EWeapon.push_back(_weapon);
		break;
	}
	case 2:
	{
		_weapon = new LaserGun;
		_weapon->init(sNum, renderX, renderY, grade);
		EWeapon.push_back(_weapon);
		break;
	}
	case 3:
	{
		_weapon = new MedicalGuns;
		_weapon->init(sNum, renderX, renderY, grade);
		EWeapon.push_back(_weapon);
		break;
	}
	case 4:
	{
		_weapon = new SubMachineGun;
		_weapon->init(sNum, renderX, renderY, grade);
		EWeapon.push_back(_weapon);
		break;
	}
	case 5:
	{
		_weapon = new PistolGuns;
		_weapon->init(sNum, renderX, renderY, grade);
		EWeapon.push_back(_weapon);
		break;
	}
	}
}

void Player::levelUpCheck()
{
	if (_exp >= maxExp)
	{
		_exp -= maxExp;
		maxExp += 30;
		pLevel++;
		pStats.maxHp++;
		_hp++;
		levelUpCount++;
	}
}

void Player::lvStatUp(int statNum, int statUp)
{
	switch (statNum)
	{
	case 1:
	{
		pStats.maxHp += statUp;
		break;
	}
	case 2:
	{
		pStats.hpRegen += statUp;
		break;
	}
	case 3:
	{
		pStats.lifeSteal += statUp;
		break;
	}
	case 4:
	{
		pStats.dmg += statUp;
		break;
	}
	case 5:
	{
		pStats.meleeDmg += statUp;
		break;
	}
	case 6:
	{
		pStats.rangeDmg += statUp;
		break;
	}
	case 7:
	{
		pStats.elementDmg += statUp;
		break;
	}
	case 8:
	{
		pStats.atkSpd += statUp;
		break;
	}
	case 9:
	{
		pStats.critRate += statUp;
		break;
	}
	case 10:
	{
		pStats.engineering += statUp;
		break;
	}
	case 11:
	{
		pStats.range += statUp;
		break;
	}
	case 12:
	{
		pStats.def += statUp;
		break;
	}
	case 13:
	{
		pStats.evade += statUp;
		break;
	}
	case 14:
	{
		pStats.spd += statUp;
		break;
	}
	case 15:
	{
		pStats.luck += statUp;
		break;
	}
	case 16:
	{
		pStats.harvest += statUp;
		break;
	}
	}
}

void Player::applyStat()
{
	_spd = 6 + (6 * pStats.spd / 100);
}

//void Player::aiming(int sNum, float angle)
//{
//	EWeapon[sNum]->setAngle(angle);
//}
