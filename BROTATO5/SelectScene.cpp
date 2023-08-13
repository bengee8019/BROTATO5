#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	selectNum = 0;
	sceneChange = false;

	IMAGEMANAGER->addImage("ĳ���ͼ���ȭ��", "Resources/bg/selectbg.bmp", 1920, 1080, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("����ٴ�info", "Resources/select/wellroundinfo.bmp", 361, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������info", "Resources/select/rangerinfo.bmp", 361, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����Ͼ�info", "Resources/select/engineerinfo.bmp", 361, 504, true, RGB(255, 0, 255));

	_sNum = 0;
	vButton.resize(4);
	vButton[0].setButton(170, 718, 97, 96, "����1", "����2", "Resources/select/random1.bmp", "Resources/select/random2.bmp", 1);
	vButton[1].setButton(276, 718, 97, 96, "����ٴ�1", "����ٴ�2", "Resources/select/wellroundicon1.bmp", "Resources/select/wellroundicon2.bmp", 2);
	vButton[2].setButton(382, 718, 97, 96, "������1", "������2", "Resources/select/rangericon1.bmp", "Resources/select/rangericon2.bmp", 3);
	vButton[3].setButton(488, 718, 97, 96, "�����Ͼ�1", "�����Ͼ�2", "Resources/select/engineericon1.bmp", "Resources/select/engineericon2.bmp", 4);

	return S_OK;
}

void SelectScene::update()
{
	//���콺 �̵� ��
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
	//Ŭ�� ��
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
	IMAGEMANAGER->render("ĳ���ͼ���ȭ��", getMemDC(), 0, 0);
	for (auto it = vButton.begin(); it != vButton.end(); ++it)
	{
		it->render(getMemDC());
	}
	switch (_sNum)
	{
	case 2:
	{
		IMAGEMANAGER->render("����ٴ�info", getMemDC(), 780, 200);
		break;
	}
	case 3:
	{
		IMAGEMANAGER->render("������info", getMemDC(), 780, 200);
		break;
	}
	case 4:
	{
		IMAGEMANAGER->render("�����Ͼ�info", getMemDC(), 780, 200);
		break;
	}
	}
}

void SelectScene::release()
{
	IMAGEMANAGER->deleteImage("ĳ���ͼ���ȭ��");
	IMAGEMANAGER->deleteImage("����ٴ�info");
	IMAGEMANAGER->deleteImage("������info");
	IMAGEMANAGER->deleteImage("�����Ͼ�info");
}
