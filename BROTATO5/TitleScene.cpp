#include "Stdafx.h"
#include "TitleScene.h"

void TitleScene::loadSound()
{

	SOUNDMANAGER->addSound("onButton", "Resources/music/effectSound/button/onButton.wav", false);
	SOUNDMANAGER->addSound("getDrops", "Resources/music/effectSound/harvest/cartoon_boing_jump_01.wav",false);
	SOUNDMANAGER->addSound("Impact", "Resources/music/effectSound/bullet_impact_body_flesh_05.wav", false);
	SOUNDMANAGER->addSound("LaserGun","Resources/weapon/Gun/laser_gun.wav",false);
	SOUNDMANAGER->addSound("MedicalGun","Resources/weapon/Gun/medical_gun.wav",false);
	SOUNDMANAGER->addSound("SMG","Resources/weapon/Gun/SMG.wav", false);
	SOUNDMANAGER->addSound("Pistol", "Resources/weapon/Gun/pistol.wav", false);
	SOUNDMANAGER->addSound("ShotGun", "Resources/weapon/Gun/double_barrel_shotgun.wav", false);
}

HRESULT TitleScene::init()
{
	loadSound();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	gdiplusToken = 0;

	//_wsbgDir1 = L"Resources/title/titlebg1.png";
	_wsbgDir2 = L"Resources/title/titlebg2.png";
	//_wsbgDir3 = L"Resources/title/titlebg3.png";
	_wsbgDir4 = L"Resources/title/titlebg4.png";
	_wsbgDir5 = L"Resources/title/titlebg5.png";

	//wcscpy_s(bgDir1, 200, _wsbgDir1.c_str());
	wcscpy_s(bgDir2, 200, _wsbgDir2.c_str());
	//wcscpy_s(bgDir3, 200, _wsbgDir3.c_str());
	wcscpy_s(bgDir4, 200, _wsbgDir4.c_str());
	wcscpy_s(bgDir5, 200, _wsbgDir5.c_str());


	//bgImage1 = Image::FromFile(bgDir1);
	bgImage2 = Image::FromFile(bgDir2);
	//bgImage3 = Image::FromFile(bgDir3);
	bgImage4 = Image::FromFile(bgDir4);
	bgImage5 = Image::FromFile(bgDir5);

	IMAGEMANAGER->addImage("메인캐릭터", "Resources/title/splash_art_brotato.bmp", 602, 404, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인로고", "Resources/title/titlelogo.bmp", 1122, 330, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인배경1", "Resources/title/titlebg1.bmp", 1920, 1080, false);
	IMAGEMANAGER->addImage("메인배경3", "Resources/title/titlebg3.bmp", 2070, 1080, true, RGB(255, 0, 255));


	//IMAGEMANAGER->addImage("메인화면", "Resources/bg/TITLE.bmp", 1920, 1080, false, RGB(0, 0, 0));

	//SOUNDMANAGER->addWaveFileWithKey("onButton", "Resources/music/effectSound/button/onButton.wav");
	
	SOUNDMANAGER->addSound("Ingame_converted", "Resources/music/bg/Ingame_converted.mp3",true);
	SOUNDMANAGER->playSound("Ingame_converted", 0.4);
	//SOUNDMANAGER->addMp3FileWithKey("Ingame_converted", "Resources/music/bg/Ingame_converted.mp3");
	//SOUNDMANAGER->playSoundWithKey("Ingame_converted");


	FONTMANAGER->setFont(80,"Noto Sans KR Medium");

	selectNum = 0;
	sceneChange = false;
	vButton.resize(2);
	vButton[0].setButton(100, 800, 104, 65, "시작버튼1", "시작버튼2", "Resources/button/start1.bmp", "Resources/button/start2.bmp", 2);
	vButton[1].setButton(100, 900, 104, 65, "종료버튼1", "종료버튼2", "Resources/button/exit1.bmp", "Resources/button/exit2.bmp", 10);

	animTimer = 0;
	bgAnimIndex1 = 0;
	chAnimIndex = 0;
	//bgAnimIndex3 = 0;
	animSwitch = true;
	animLR = 1;
	animCount = 0;

	return S_OK;
}

void TitleScene::update()
{
	SOUNDMANAGER->update();
	//마우스 이동 시
	animUpdate();
	for (auto it = vButton.begin(); it != vButton.end(); ++it)
	{
		//if (PtInRect(&(it->getArea()), _ptMouse))
		//{
		//	it->setOnMouse(true);
		//}
		//else
		//{
		//	it->setOnMouse(false);
		//}
	it->update(_ptMouse);
	}
	//클릭 시
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (auto it = vButton.begin(); it != vButton.end(); ++it)
		{
			if (PtInRect(&(it->getArea()), _ptMouse))
			{
				selectNum = it->getSNum();
			}
		}
	}
	switch (selectNum)
	{
	case 10:
	{
		sceneChange = true;
		break;
	}
	case 2:
	{
		sceneChange = true;
		break;
	}
	}
}

void TitleScene::animUpdate()
{
	animTimer++;
	if (animTimer <= 15)
	{
		chAnimIndex++;
	}
	else
	{
		chAnimIndex--;
	}
	if (animSwitch)
	{
		if (animTimer <= 20)
		{
			bgAnimIndex1+=3;
		}
		//60
		else if (animTimer <= 25)
		{
			bgAnimIndex1 += 2;
		}
		//10
		else
		{
			bgAnimIndex1++;
		}
		//4
	}
	else
	{
		if (animTimer <= 6)
		{
			bgAnimIndex1--;
		}

		else if (animTimer < 10)
		{
			bgAnimIndex1-=2;
		}

		else
		{
			bgAnimIndex1-=3;
		}

	}
	if (animTimer == 30)
	{
		animTimer = 0;
		animSwitch = !animSwitch;
		animCount++;
		if(animCount % 2 == 0)
		{
			animLR = -animLR;
		}
	}
	//cout << bgAnimIndex1 << endl;
}

void TitleScene::render()
{
	//IMAGEMANAGER->render("메인화면", getMemDC(), 0, 0);
	Gdiplus::Graphics graphics(getMemDC());

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	//graphics.DrawImage(bgImage1, -75, 0);
	IMAGEMANAGER->render("메인배경1", getMemDC(), 0, 0);
	//오른쪽
	graphics.DrawImage(bgImage2, -75 + animLR * bgAnimIndex1, 0);
	//graphics.DrawImage(bgImage3, -75, 0);
	IMAGEMANAGER->render("메인배경3", getMemDC(), -75, 0);

	//캐릭터 애니메이션
	IMAGEMANAGER->render("메인캐릭터", getMemDC(), 650 + chAnimIndex, 500 - chAnimIndex, 602-2*chAnimIndex,404+ chAnimIndex,0,0,602,404);
	graphics.DrawImage(bgImage4, -75 - animLR * bgAnimIndex1, 0);
	graphics.DrawImage(bgImage5, -75, 0);
	//로고
	IMAGEMANAGER->render("메인로고", getMemDC(), 380, 50);



	for (auto it = vButton.begin(); it != vButton.end(); ++it)
	{
		it->render(getMemDC());
	}
}

void TitleScene::release()
{
	IMAGEMANAGER->deleteImage("메인화면");
	IMAGEMANAGER->deleteImage("메인로고");
	IMAGEMANAGER->deleteImage("메인배경1");
	IMAGEMANAGER->deleteImage("메인배경3");
	//SAFE_DELETE(bgImage1);
	SAFE_DELETE(bgImage2);
	//SAFE_DELETE(bgImage3);
	SAFE_DELETE(bgImage4);
	SAFE_DELETE(bgImage5);

	if (gdiplusToken)
	{
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

}

