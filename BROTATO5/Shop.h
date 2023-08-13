#pragma once
#include "Items.h"
#include "Button.h"
#include "itemCard.h"

struct tagITable
{
	int iNum;
	int iGrade;
	int iPrice;
	string iKey;
};

class Shop
{
private:
	bool testbool;

	map<int,tagITable> normalItems;
	map<int,tagITable> uncommonItems;
	map<int,tagITable> rareItems;
	map<int,tagITable> uniqueItems;
	vector<itemCard*> vICard;
	//vector<Items*> vItems;
	vector<Button> vBuyButton;
	char rerollPrice[10];
	string priceStr[5];
	char price1[10];
	char price2[10];
	char price3[10];
	char price4[10];

	int _playerGold;
	int _nowRound;
	int _reRollCount;
	int _pLuck;
	int _select;
	int _pWIndex;
	string _pGold;

	HFONT oldFont;
	HFONT shopFont;


public:
	HRESULT init(int nowround, int luck, HFONT font);
	void loadItemTable();
	void update();
	int buyItem();
	void render(HDC hdc);
	void reRoll();
	void setPLuck(int pluck) { _pLuck = pluck; }
	void release();
	void setPGold(int pgold) { _playerGold = pgold; }
	int getPGold() { return _playerGold; }
	tagITable getItemInfo(int sNum);
	void setPWIndex(int windex) { _pWIndex = windex; }


};

