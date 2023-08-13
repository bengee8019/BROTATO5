#pragma once

struct tagUpStat
{
	int t1;
	int t2;
	int t3;
	int t4;
	wstring _sName;
	wstring _sType;
};

struct tagStats
{
	//first Stats
	int maxHp;
	int hpRegen;
	int lifeSteal;
	int dmg;
	int meleeDmg;
	int rangeDmg;
	int elementDmg;
	int atkSpd;
	int critRate;
	int engineering;
	int range;
	int def;
	int evade;
	int spd;
	int luck;
	int harvest;

	//second Stats
	int itemHeal;
	int ingHeal;
	int expGain;
	int gainRange;
	int discount;
	int explodeDmg;
	int explodeRange;
	int bound;
	int penetrate;
	int penetrateDmg;
	int bossDmg;
	int burnSpd1;
	int burnSpd2;
	int knockBack;
	int doubleChance;
	int ingInBox;
	int freeReroll;
	int trees;
	int enemyAmount;
	int enemySpeed;

	//구조체 index로 접근하기 위해 주소 반환
	int& operator[] (int index) { return *(&maxHp + index); }
};