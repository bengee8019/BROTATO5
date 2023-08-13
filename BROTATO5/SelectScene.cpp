#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	selectNum = 0;
	sceneChange = false;

	IMAGEMANAGER->addImage("캐릭터선택화면", "Resources/bg/selectbg.bmp", 1920, 1080, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("다재다능info", "Resources/select/wellroundinfo.bmp", 361, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("레인저info", "Resources/select/rangerinfo.bmp", 361, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔지니어info", "Resources/select/engineerinfo.bmp", 361, 504, true, RGB(255, 0, 255));

	_sNum = 0;
	vButton.resize(4);
	vButton[0].setButton(170, 718, 97, 96, "랜덤1", "랜덤2", "Resources/select/random1.bmp", "Resources/select/random2.bmp", 1);
	vButton[1].setButton(276, 718, 97, 96, "다재다능1", "다재다능2", "Resources/select/wellroundicon1.bmp", "Resources/select/wellroundicon2.bmp", 2);
	vButton[2].setButton(382, 718, 97, 96, "레인저1", "레인저2", "Resources/select/rangericon1.bmp", "Resources/select/rangericon2.bmp", 3);
	vButton[3].setButton(488, 718, 97, 96, "엔지니어1", "엔지니어2", "Resources/select/engineericon1.bmp", "Resources/select/engineericon2.bmp", 4);

	return S_OK;
}

void SelectScene::update()
{
	//마우스 이동 시
	for (auto it = vButton.begin(); it != vButton.end(); ++it)
	{
		if (PtInRect(&(it->getArea()), _ptMouse))
		{
			it->setOnMouse(true);
			_sNum = it->getSNum();
		}
		else
		{
			it->setOnMouse(false);
		}
		//it->update(_ptMouse);
	}
	//클릭 시
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (auto it = vButton.begin(); it != vButton.end(); ++it)
		{
			if (PtInRect(&(it->getArea()), _ptMouse))
			{
				selectNum = it->getSNum();
				sceneChange = true;
			}
		}
	}
}

void SelectScene::render()
{
	IMAGEMANAGER->render("캐릭터선택화면", getMemDC(), 0, 0);
	for (auto it = vButton.begin(); it != vButton.end(); ++it)
	{
		it->render(getMemDC());
	}
	switch (_sNum)
	{
	case 2:
	{
		IMAGEMANAGER->render("다재다능info", getMemDC(), 780, 200);
		break;
	}
	case 3:
	{
		IMAGEMANAGER->render("레인저info", getMemDC(), 780, 200);
		break;
	}
	case 4:
	{
		IMAGEMANAGER->render("엔지니어info", getMemDC(), 780, 200);
		break;
	}
	}
}

void SelectScene::release()
{
	IMAGEMANAGER->deleteImage("캐릭터선택화면");
	IMAGEMANAGER->deleteImage("다재다능info");
	IMAGEMANAGER->deleteImage("레인저info");
	IMAGEMANAGER->deleteImage("엔지니어info");
}
