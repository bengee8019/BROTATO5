#include "Stdafx.h"
#include "WInventory.h"
#pragma warning(disable : 4996)

HRESULT WInventory::init(int posx, int posy)
{
	//vWButton.resize(6);
	x = posx;
	y = posy;
	return S_OK;
}

void WInventory::equipWeapon(int iNum, int sNum, int grade)//sNum 0,1,2,3,4,5까지
{
	Button* wButton = new Button;

	string tmpStr1 = "";
	string tmpStr2 = "";

	string tmpStr = "wIcon";

	char tmpDir1[100] = "Resources/weapon/Icons/";
	char tmpDir2[100] = "Resources/weapon/Icons/";

	tmpStr += to_string(iNum);
	tmpStr += "_";
	tmpStr2 = tmpStr + (string)"on.bmp";
	tmpStr += to_string(grade);

	tmpStr1 = tmpStr + (string)"off.bmp";
	strncat(tmpDir1, tmpStr1.c_str(), strlen(tmpStr1.c_str()));
	strncat(tmpDir2, tmpStr2.c_str(), strlen(tmpStr2.c_str()));
	//테스트
	string key1 = tmpStr + (string)"off";
	string key2 = tmpStr + (string)"on";
	wButton->setButton(x + ((sNum-1) % 3) * (100), y + ((sNum-1) / 3) * 100, 96, 96, key1, key2, tmpDir1, tmpDir2, (sNum - 1));
	//wButton.setButton(x + ((sNum - 1) % 3) * (100), y + ((sNum - 1) / 3) * 100, 411, 65, "웨이브시작1", "웨이브시작2", "Resources/button/wavestart1.bmp", "Resources/button/wavestart2.bmp", 0);
	vWButton.push_back(wButton);
	//key[(sNum - 1)] = tmpStr;

}

void WInventory::update(POINT mPt)
{
	for (auto wBIt = vWButton.begin(); wBIt != vWButton.end(); ++wBIt)
	{
		(*wBIt)->update(mPt);
	}
}

void WInventory::render(HDC hdc)
{
	for (auto wBIt = vWButton.begin(); wBIt != vWButton.end(); ++wBIt)
	{
		(*wBIt)->render(hdc);
	}
}

void WInventory::release()
{
}


