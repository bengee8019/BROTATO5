#pragma once
#include "SingletonBase.h"
//#include "Items.h"
//#include "Weapon.h"
#include "Guns.h"

struct tagItemData
{
	int itemNum;
	int grade;
	bool isWeapon;
	int price;
	string itemName;

	tagStats iStats;
};

class ItemManager : public SingletonBase<ItemManager>
{
private:
	typedef map<int, Items*> ItemList;
	typedef map<int, Items*>::iterator ItemListIter;
	ItemList _ItemList;
public:
	ItemManager();
	~ItemManager();

	HRESULT init(tagItemData* itemData);
	Items* ItemManager::addItem(int intKey, int grade,
		bool isWeapon,
		int price,
		string itemName,
		tagStats iStats);
	Items* findItem(int key);

	bool deleteAll();

	void release();


};

