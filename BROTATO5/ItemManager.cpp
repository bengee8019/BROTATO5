#include "Stdafx.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init(tagItemData* itemData)
{
	//addItem(1, 1, true, 20, "샷건", {0,});
	return S_OK;
}

Items* ItemManager::addItem(int intKey, int grade,
bool isWeapon,
int price,
string itemName,
tagStats iStats)
{
	Items* item = findItem(intKey);
	if (item)
	{
		return item;
	}

	item = new Items;
	//item
	if (FAILED(item->init(intKey)))
	{
		SAFE_DELETE(item);
		return NULL;
	}
	_ItemList.insert(pair<int, Items*>(intKey, item));

	return item;
}

//key에 해당하는 item 주소 반환
Items* ItemManager::findItem(int intKey)
{
	auto key = _ItemList.find(intKey);

	if (key != _ItemList.end())
	{
		return key->second;
	}
	return nullptr;
}

bool ItemManager::deleteAll()
{
	auto iter = _ItemList.begin();
	for (; iter != _ItemList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _ItemList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_ItemList.clear();
	return true;
}

void ItemManager::release()
{
	this->deleteAll();
}
