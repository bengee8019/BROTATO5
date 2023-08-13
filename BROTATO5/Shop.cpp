#include "Stdafx.h"
#include "Shop.h"

HRESULT Shop::init(int nowround, int luck, HFONT font)
{
	//
	testbool = true;

	shopFont = font;
	_select = 20;
	//RND->getInt();
	for (int i = 1; i < 5; i++)
	{
		Button tmpButton;
		tmpButton.setButton(-240 + 360 * i, 650, 161, 66, "buy1", "buy2", "Resources/button/buy1.bmp", "Resources/button/buy2.bmp", i);
		vBuyButton.push_back(tmpButton);
	}
	_nowRound = nowround;
	_playerGold = 0;
	_reRollCount = 0;
	_pLuck = luck;
	loadItemTable();
	reRoll();
	return S_OK;
}

void Shop::loadItemTable()
{
	for (int i = 1; i < 2; i++)
	{
		//일단 1등급별로 무기 5개까지
		for (int j = 1; j < 6; j++)
		{
			string tmpstr = "Resources/weapon/";
			string tmpKey = to_string(i);
			tmpKey = tmpKey + "_" + to_string(j);
			tmpstr = tmpstr + tmpKey + "info.bmp";
			char tmpdir[100];
			strcpy_s(tmpdir, 100, tmpstr.c_str());
			IMAGEMANAGER->addImage(tmpKey, tmpdir, 351, 478, true, RGB(255, 0, 255));
			tagITable tmpitem = { j, i, 15 * i, tmpKey};

			//등급별 아이템 테이블 맵에 <iNum, tagITable> 페어 등록
			switch (i)
			{
			case 1:
			{
				normalItems.insert(make_pair(j, tmpitem));
				break;
			}
			case 2:
			{
				uncommonItems.insert(make_pair(j, tmpitem));
				break;
			}
			case 3:
			{
				rareItems.insert(make_pair(j, tmpitem));
				break;
			}
			case 4:
			{
				uniqueItems.insert(make_pair(j, tmpitem));
				break;
			}
			}
			if (testbool)
			{
				cout << tmpdir << endl;
			}
		}
		testbool = false;
	}
}

void Shop::update()
{
	for (int i = 0; i < 4; i++)
	{
		if (!(vICard[i]->getSoldOut()))
		{
			vICard[i]->update();
			vICard[i]->setItemPrice(vICard[i]->getItemPrice() + _nowRound);
			vBuyButton[i].update(_ptMouse);
			priceStr[i] = to_string(vICard[i]->getItemPrice());
		}
	}
	_pGold = to_string(_playerGold);
	//for (auto it = vICard.begin(); it != vICard.end();it++)
	//{
	//	if (!(*it)->getSoldOut())
	//	{
	//		(*it)->update();
	//	}
	//}
}


//여기 수정하기#########@@@@@@@@@@@@@####################### 할일
int Shop::buyItem()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&vBuyButton[i].getArea(), _ptMouse)&&_pWIndex<=6)
		{
			if (_playerGold >= vICard[i]->getItemPrice())
			{
				//1,2,3,4
				_select = vBuyButton[i].getSNum();
				vICard[_select - 1]->setSoldOut(true);
				_playerGold -= vICard[_select - 1]->getItemPrice();
				return { _select };
			}
		}
	}
	return 0;
}

//struct tagITable
//{
//	int iNum;
//	int iGrade;
//	int iPrice;
//	string iKey;
//};
void Shop::render(HDC hdc)
{
	for (int i = 0; i < 4; i++)
	{
		if (!(vICard[i]->getSoldOut()))
		{
			vICard[i]->render(hdc);
			vBuyButton[i].render(hdc);
			if (!vBuyButton[i].getOnMouse())
			{
				SetTextColor(hdc, RGB(255, 255, 255));
			}
			else
			{
				SetTextColor(hdc, RGB(0, 0, 0));
			}
			TextOut(hdc, 160+360*i,660,priceStr[i].c_str(),strlen(priceStr[i].c_str()));
		}
	}

	SetTextColor(hdc, RGB(255, 255, 255));
	oldFont = (HFONT)SelectObject(hdc, shopFont);
	DrawText(hdc, _pGold.c_str(), strlen(_pGold.c_str()), &(RectMake(1200, 50, 200, 50)), DT_RIGHT);
	SelectObject(hdc, oldFont);
	//TextOut(hdc, 1300, 50, _pGold.c_str(), strlen(_pGold.c_str()));
}

void Shop::reRoll()
{
	vICard.clear();
	for (int i = 1; i < 5; i++)
	{
		int tmpDice = RND->getInt(100) + 1;
		int tmpDice2 = RND->getInt(5) + 1;
		itemCard* tmpICard = new itemCard;
		tagITable tmpITable;
		//if (tmpDice < 1 + _nowRound / 2 + (_pLuck) / 10)
		//{
		//}
		//else if (tmpDice < 5 + _nowRound / 2 + (_pLuck) / 8)
		//{
		//}
		//else if (tmpDice < 20 + _nowRound / 2 + (_pLuck) / 5)
		//{
		//}
		//else
		//{
			tmpITable = normalItems.find(tmpDice2)->second;
		//}
		tmpICard->init(tmpITable.iNum, tmpITable.iGrade, _nowRound, tmpITable.iKey, i);

		vICard.push_back(tmpICard);
	}
	_reRollCount++;
}

void Shop::release()
{
}

tagITable Shop::getItemInfo(int sNum)
{
	return { vICard[sNum]->getINum(),vICard[sNum]->getIGrade(),vICard[sNum]->getItemPrice(),vICard[sNum]->getIKey()};
}
//int iNum;
//int iGrade;
//int iPrice;
//string iKey;