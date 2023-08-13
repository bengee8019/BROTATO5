#pragma once
#include "GameNode.h"
#include "Stats.h"
#include "Weapon.h"
#include "Guns.h"
#include "Bullet.h"
#include "Acc.h"
//#include "WInventory.h"
//#include "AInventory.h"

class Player : public GameNode
{
protected:

	vector<Weapon*> EWeapon;
	vector<Bullet*> vBullets;
	//WInventory WInven;

	int count;
	bool bAnim;
	int animHeight;
	int pHeight;
	bool isLeft;
	int x, y;
	int weaponIndex;
	int cameraX, cameraY;
	bool onMoveX, onMoveY;
	int renderX, renderY;

	bool _stop;
	bool _death;

	//인벤토리 작업 후
	//WInventory* wInven;
	//AInventory* aInven;

	int _hp;
	float _spd;
	int pLevel;
	int _exp;
	int maxExp;
	int levelUpCount;
	int _gold;
	int _baseRange;
	int _range;


	tagStats pStats;

	//테스트
	RECT pRect;
public:
	HRESULT init(int prole);
	void update();
	void render();
	void release();

	void setNewRound();

	void equipWeapon(int iNum, int sNum, int grade);

	void levelUpCheck();

	void lvStatUp(int statNum, int statUp);
	//void aiming(int sNum, float angle);

	//get, set

	//플레이어의 모든 총알이 담긴 벡터 반환
	vector<Bullet*> getVBullets() { return vBullets; }

	void setOnMoveX(bool onmovex) { onMoveX = onmovex; }
	bool getOnMoveX() { return onMoveX; }
	void setOnMoveY(bool onmovey) { onMoveY = onmovey; }
	bool getOnMoveY() { return onMoveY; }

	void setX(int xPos) { x = xPos; }
	void setY(int yPos) { y = yPos; }
	int getX() { return x; }
	int getY() { return y; }
	void applyStat();

	int getRX() { return renderX; }
	int getRY() { return renderY; }

	void setRX(int rx) { renderX = rx; }
	void setRY(int ry) { renderY = ry; }


	int getSNum(int sNum) { return EWeapon[sNum]->getSNum(); }
	int getWRange(int sNum) { return EWeapon[sNum]->getRange(); }
	int getWX(int sNum) { return EWeapon[sNum]->getWX(); }
	int getWY(int sNum) { return EWeapon[sNum]->getWY(); }
	void setWIdle(int sNum, bool idle) { EWeapon[sNum]->setIdle(idle); }
	void setAngle(int sNum, float angle) { EWeapon[sNum]->setAngle(angle); }

	void setlevel(int num) { pLevel = num; }
	void setmaxExp(int num) { maxExp = num; }
	//first stats
	void setmaxHp(int num) { pStats.maxHp = num; }
	void sethpRegen(int num) { pStats.hpRegen = num; }
	void setlifeSteal(int num) { pStats.lifeSteal = num; }
	void setdmg(int num) { pStats.dmg = num; }
	void setmeleeDmg(int num) { pStats.meleeDmg = num; }
	void setrangeDmg(int num) { pStats.rangeDmg = num; }
	void setelementDmg(int num) { pStats.elementDmg = num; }
	void setatkSpd(int num) { pStats.atkSpd = num; }
	void setcritRate(int num) { pStats.critRate = num; }
	void setengineering(int num) { pStats.engineering = num; }
	void setrange(int num) { pStats.range = num; }
	void setdef(int num) { pStats.def = num; }
	void setevade(int num) { pStats.evade = num; }
	void setspd(int num) { pStats.spd = num; }
	void setluck(int num) { pStats.luck = num; }
	void setharvest(int num) { pStats.harvest = num; }
	//second stats

	void setitemHeal(int num) { pStats.itemHeal = num; }
	void setingHeal(int num) { pStats.ingHeal = num; }
	void setexpGain(int num) { pStats.expGain = num; }
	void setgainRange(int num) { pStats.gainRange = num; }
	void setdiscount(int num) { pStats.discount = num; }
	void setexplodeDmg(int num) { pStats.explodeDmg = num; }
	void setexplodeRange(int num) { pStats.explodeRange = num; }
	void setbound(int num) { pStats.bound = num; }
	void setpenetrate(int num) { pStats.penetrate = num; }
	void setpenetrateDmg(int num) { pStats.penetrateDmg = num; }
	void setbossDmg(int num) { pStats.bossDmg = num; }
	void setburnSpd1(int num) { pStats.burnSpd1 = num; }
	void setburnSpd2(int num) { pStats.burnSpd2 = num; }
	void setknockBack(int num) { pStats.knockBack = num; }
	void setdoubleChance(int num) { pStats.doubleChance = num; }
	void setingInBox(int num) { pStats.ingInBox = num; }
	void setfreeReroll(int num) { pStats.freeReroll = num; }
	void settrees(int num) { pStats.trees = num; }
	void setenemyAmount(int num) { pStats.enemyAmount = num; }
	void setenemySpeed(int num) { pStats.enemySpeed = num; }

	//get할때는 통째로 가져오자.
	void setPStats(int sIndex, int sUp) { pStats[sIndex] += sUp; }
	tagStats getPStats() { return pStats; }

	void setHp(int hp) { _hp = hp; }
	int getHp() { return _hp; }
	int getLv() { return pLevel; }
	int getExp() { return _exp; }
	void setExp(int exp) { _exp = exp; }
	int getMaxExp() { return maxExp; }
	int getWIndex() { return weaponIndex; }
	bool getStop() { return _stop; }
	void setStop(bool stop) { _stop = stop; }
	int getGold() { return _gold; }
	void setGold(int gold) { _gold = gold; }
	int getRange() { return _range; }
	void setRange(int range) { _range = range; }

	void setDeath(bool death) { _death = death; }
	RECT getPRect() { return pRect; }
	int getLvUpCount() { return levelUpCount; }
	void decreaseLvUpCount() { levelUpCount--; }
};

