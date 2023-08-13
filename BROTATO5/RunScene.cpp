#include "Stdafx.h"
#include "RunScene.h"

//class Player;

HRESULT RunScene::init()
{
	_bgmCount = 0;
	//loopBGM();
	//외곽선 기능??
	TimerFont = setFont(80, 600, "Noto Sans KR Medium");

	LargeFont = setFont(60, 600, "Noto Sans KR Medium");
	//TimerOutFont = setFont(80, 800, "Noto Sans KR Medium");
	mediumFont = setFont(40, 600, "Noto Sans KR Medium");
	//mediumOutFont = setFont(40, 800, "Noto Sans KR Medium");
	smallFont = setFont(20, 600, "Noto Sans KR Medium");

	statDataLoad();
	imageLoad();
	sReRollButton.setButton(630,700,276,63,"스탯리롤1","스탯리롤2","Resources/button/reroll1.bmp", "Resources/button/reroll2.bmp", 5);
	vShopButton.resize(1);
	vShopButton[0].setButton(WINSIZE_X - 450, WINSIZE_Y - 140, 411, 65, "웨이브시작1", "웨이브시작2", "Resources/button/wavestart1.bmp", "Resources/button/wavestart2.bmp", 0);
	selectNum = 20;

	pMaxWeapon = 6;
	pWeaponIndex = 1;

	player = new Player;
	player->init(playerRole);
	WInven = new WInventory;
	WInven->init(1150,820);
	dpStat = new statUI;
	dpStat->init(TimerFont, mediumFont, statArr);

	_shop.init(_stageRound, player->getPStats().luck, LargeFont);
	vSCardReRoll();
	////1 샷건 테스트 
	//equipWeapon(1, 1, 1);
	////2 레이저건 테스트
	//equipWeapon(2, 2, 1);
	////3 메디컬건 테스트
	//equipWeapon(3, 3, 1);
	////4 SMG 테스트
	//equipWeapon(4, 4, 1);
	////5 pistol 테스트
	//equipWeapon(5, 5, 1);
	//equipWeapon(5, 6, 1);
	equipWeapon(4, 1);

	renderPt = { player->getX(), player->getY()};
	renderArea = RectMakeCenter(renderPt.x, renderPt.y, WINSIZE_X, WINSIZE_Y);
	_stageRound = 1;
	_initRTime = 600;
	_rTimeCount = _initRTime;
	_breakTime = 150;
	_bTimeCount = _breakTime;
	_rTimer = 0.0f;
	_hitTimer = 0;
	_onRun = true;
	_openShop = false;
	_ready = false;
	_isClear = false;
	_levelUp = false;
	lvRerollFee = 2;
	_iEnemyNum = 5;
	_iIndex = _iEnemyNum;
	_MaxEnemyNum = 15;
	statRerollCount = 0;
	wcscpy_s(levelUpText, 20, L"레벨 업!");

	barWidth = 304;
	barHeight = 34;

	nullPen = CreatePen(PS_NULL, 1, NULL);
	redBrush = CreateSolidBrush(RGB(184, 0, 0));
	greenBrush = CreateSolidBrush(RGB(64, 217, 64));


	for (int i = 0; i < _iIndex; i++)
	{
		Enemy* tmpEnemy = new Enemy;
		tmpEnemy->setENum(i);
		vEnemy.push_back(tmpEnemy);
	}

	for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
	{
		(*iter)->init(_stageRound);
	}

	_testMode = false;

    return S_OK;
}

void RunScene::update()
{
	SOUNDMANAGER->update();
	//테스트 모드 space 키
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_testMode = !_testMode;
	}
	//_unHitableTime--;
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	SOUNDMANAGER->playEffectSoundWave(TEXT("Resources/music/effectSound/button/onButton.wav"));
	//}
	//_hitTimer++;
	_bgmCount--;
	//loopBGM();
	_rTimer = _rTimeCount / 100;
	player->levelUpCheck();
	if (_rTimeCount < 100)
	{
		//dp스텟 업데이트
		dpStat->update(player->getPStats());
		if (!player->getStop() && _onRun)
		{
			//tempEnemy->roundEnd();
			player->setRange(5000);
			//windex : 무기갯수
			for (int i = 0; i < player->getWIndex(); i++)
			{
				player->setWIdle(i, true);
			}
			player->setStop(true);
			//적 벡터 비우기
			/*for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
			{
				(*iter)->death();
			}*/
			vEnemy.clear();
			_onRun = false;
			_ready = false;
		}

		//재료 흡수, 3초 뒤 레벨업 체크, 아이템 체크 후
		_bTimeCount--;
		if (_bTimeCount <= 0)
		{
			//런 클리어 확인
			if (_stageRound == 20)
			{
				_isClear = true;
			}
			//획득한 아이템 체크
			//레벨업 시 스탯 선택 후
			if (player->getLvUpCount() > 0)
			{
				_levelUp = true;			
			}
			else
			{
				//레벨업 리롤 카운트 초기화
				statRerollCount = 0;
				_levelUp = false;
				// 상점 오픈
				_openShop = true;
			}

			if (_levelUp)
			{
				//레벨업 처리
				int lvUpSelectNum = 0;
				if (player->getGold() > lvRerollFee)
				{
					sReRollButton.update(_ptMouse);
				}
				for (auto vCIt = vSCard.begin(); vCIt != vSCard.end(); vCIt++)
				{
					(*vCIt)->update(_ptMouse);
				}
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (PtInRect(&(sReRollButton.getArea()), _ptMouse))
					{
						lvUpSelectNum = sReRollButton.getSNum();
					}
					for (auto vCIt = vSCard.begin(); vCIt != vSCard.end(); vCIt++)
					{
						if (PtInRect(&((*vCIt)->getBRect()), _ptMouse))
						{
							player->decreaseLvUpCount();
							lvUpSelectNum = (*vCIt)->getCardNum();
						}
					}
				}

				switch (lvUpSelectNum)
				{
				case 1:
				case 2:
				case 3:
				case 4:
				{
					//cout<< vSCard[lvUpSelectNum - 1]->getStatType() <<endl;
					//cout << vSCard[lvUpSelectNum - 1]->getStatUp() << endl;
					player->setPStats(vSCard[lvUpSelectNum-1]->getStatType()-1, vSCard[lvUpSelectNum - 1]->getStatUp());
					player->applyStat();
					lvUpSelectNum = 0;
					vSCardReRoll();
					break;
				}			
				case 5:
				{
					player->setGold(player->getGold() - lvRerollFee);
					vSCardReRoll();
					statRerollCount++;
					lvUpSelectNum = 0;
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		if (_openShop)
		{
			_shop.setPGold(player->getGold());
			_shop.setPWIndex(pWeaponIndex);
			_shop.update();
			
			WInven->update(_ptMouse);
			for (auto it = vShopButton.begin(); it != vShopButton.end(); ++it)
			{
				it->update(_ptMouse);
				//클릭 시
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					int tmpSNum = _shop.buyItem();
					if (tmpSNum != 20 && tmpSNum != 0)
					{
						if (pWeaponIndex <= pMaxWeapon)
						{
						player->setGold(_shop.getPGold());
						tagITable tmpItemInfo = _shop.getItemInfo(tmpSNum-1);
						//
							equipWeapon(tmpItemInfo.iNum, tmpItemInfo.iGrade);
						}
					}
					if (PtInRect(&(it->getArea()), _ptMouse))
					{
						selectNum = it->getSNum();
					}
				}
			}
			//shop 버튼 선택 분기
			switch (selectNum)
			{
			case 0:
			{
				_ready = true;
				_openShop = false;

				break;
			}
			case 1:
			{

				selectNum = 20;
				break;
			}			
			}
		}

		if (_ready)
		{
			setNewRound();
		}
	}

	if (player->getHp() <= 0)
	{
		playerDie();
	}
	player->update();

	//테스트
	if (_testMode)
	{
		dpStat->update(player->getPStats());

		sReRollButton.update(_ptMouse);
		for (auto vCIt = vSCard.begin(); vCIt != vSCard.end(); vCIt++)
		{
			(*vCIt)->update(_ptMouse);
		}
	}

	//라운드 진행 중
	if (_onRun)
	{
		_rTimeCount--;
		_hitTimer++;
		if (_rTimeCount % 200 == 0 && _MaxEnemyNum > _iIndex)
		{
			Enemy* tmpEnemy = new Enemy;
			tmpEnemy->setENum(_iIndex);
			tmpEnemy->init(_stageRound);
			vEnemy.push_back(tmpEnemy);
			_iIndex++;
		}
		aimTarget(findEnemy());

		//카메라 위치 갱신
		cameraUpdate();

		//적 움직임
		//cout << vEnemy.size() << endl;
		for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
		{
			//타격 횟수에따라 총알 제거, 데미지 계산
			if ((*iter)->getAlive())
			{
				int tmpDmg = (*iter)->getEHp();
				(*iter)->setEHp((*iter)->getEHp() - tmpGun->hitCheck(getMemDC(), (*iter)->getREX(), (*iter)->getREY()));
				tmpDmg -= (*iter)->getEHp();
				//데미지 렌더러 생성
				if (tmpDmg > 0)
				{
					(*iter)->setKnockBack(3);
					makeDRender(tmpDmg, (*iter)->getX(), (*iter)->getY());
					SOUNDMANAGER->playSound("Impact",0.5);
				}
			}
			(*iter)->setAngle(findTarget((*iter)->getX(), (*iter)->getY(), player->getX(), player->getY(), 10000));
			(*iter)->update();
			(*iter)->setREX((*iter)->getX() - renderPt.x + WINSIZE_X / 2);
			(*iter)->setREY((*iter)->getY() - renderPt.y + WINSIZE_Y / 2);
			//int count;
			//피격시 20 frame간 무적 
			if ((*iter)->getAlive() && _hitTimer >= 20)
			{
				if (PtInRect(&((*iter)->getERect()), POINT{ player->getX(),player->getY() }))
				{
					SOUNDMANAGER->playSound("Impact",0.5);
					player->setHp(player->getHp() - (*iter)->getEDmg());
					makeDRender((*iter)->getEDmg(), player->getX(), player->getY());
					_hitTimer = 0;
				}
			}
		}
	}
	tempEnemy->dropSet(player->getX(), player->getY(), renderPt.x, renderPt.y, player->getRange());
	tagDrop _drops = { 0,0 };
	_drops = tempEnemy->dropCheck(player->getGold(), player->getExp());
	player->setGold(_drops.gold);
	player->setExp(_drops.exp);

	//데미지 렌더러 없애기
	for (auto dRIt = vDRender.begin(); dRIt != vDRender.end();)
	{
		if (dRIt->getTimeOut())
		{
			dRIt = vDRender.erase(dRIt);
		}
		else
		{
			dRIt->update(renderPt.x, renderPt.y);
			dRIt++;
		}
	}

	//총알 위치 업데이트
	tmpGun->bUpdate();
}

//새 라운드 시작 세팅
void RunScene::setNewRound()
{
	//loopBGM();
	selectNum = 20;
	_stageRound++;
	_rTimeCount = _initRTime + (_stageRound - 1) * 200;
	//시작 몹 증가
	_iEnemyNum++;
	_MaxEnemyNum++;
	_iIndex = _iEnemyNum;
	//플레이어 위치 초기화
	player->setNewRound();
	//player->setHp(player->getPStats().maxHp);
	//player->setX(1400);
	//player->setY(800);
	//player->setStop(false);


	lvRerollFee = 2; //+ player->getLv();
	_bTimeCount = _breakTime;
	_shop.reRoll();
	_onRun = true;
	_ready = false;


	//시작 몹 생성 및 초기화
	for (int i = 0; i < _iIndex; i++)
	{
		Enemy* tmpEnemy = new Enemy;
		tmpEnemy->setENum(i);
		vEnemy.push_back(tmpEnemy);
	}
	for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
	{
		(*iter)->init(_stageRound);
	}
}

//void RunScene::loopBGM()
//{
//	if (_bgmCount <= 0)
//	{
//		SOUNDMANAGER->stopMp3WithKey("Ingame_converted");
//		SOUNDMANAGER->playSoundWithKey("title_converted");
//		_bgmCount = 13000;
//	}
//}

void RunScene::vSCardReRoll()
{
	vSCard.clear();
	int tmpIndex = 0;
	for (int i = 1; i < 5; i++)
	{
		statCard* tempSCard = new statCard;
		int gradeIndex = RND->getInt(100) + 1;
		int tmpGrade = 0;
		checkLabel:
		int tmpSNum = RND->getInt(16) + 1;
		if (vSCard.size() != 0)
		{
			for (int j = 0; j < tmpIndex; j++)
			{
				if (vSCard[j]->getStatType() == tmpSNum)
				{
					goto checkLabel;
				}
			}
		}
		tempSCard->setSName(statArr[tmpSNum - 1]._sName);
		tempSCard->setSType(statArr[tmpSNum - 1]._sType);
		tempSCard->setStatType(tmpSNum);
		//switch (tmpGrade)
		//{
		//case 1:
		//{
		//	tempSCard->setStatUp(statArr[tmpSNum - 1].t1);
		//	break;
		//}
		//case 2:
		//{
		//	tempSCard->setStatUp(statArr[tmpSNum - 1].t2);
		//	break;
		//}
		//case 3:
		//{
		//	tempSCard->setStatUp(statArr[tmpSNum - 1].t3);
		//	break;
		//}
		//case 4:
		//{
		//	tempSCard->setStatUp(statArr[tmpSNum - 1].t4);
		//	break;
		//}
		//}
		if(gradeIndex < 1 + _stageRound / 2 + (player->getPStats().luck) / 10)
		{
			tempSCard->setStatUp(statArr[tmpSNum - 1].t4);
			tmpGrade = 4;
		}
		else if(gradeIndex < 5 + _stageRound / 2 + (player->getPStats().luck) / 8)
		{
			tempSCard->setStatUp(statArr[tmpSNum - 1].t3);
			tmpGrade = 3;
		}
		else if(gradeIndex < 20 + _stageRound / 2 + (player->getPStats().luck) / 5)
		{
			tempSCard->setStatUp(statArr[tmpSNum - 1].t2);
			tmpGrade = 2;
		}
		else
		{
			tempSCard->setStatUp(statArr[tmpSNum - 1].t1);
			tmpGrade = 1;
		}

		tempSCard->init(20, 300, i, tmpGrade, tmpSNum, mediumFont);
		vSCard.push_back(tempSCard);
		tmpIndex++;
	}
}

void RunScene::statDataLoad()
{
	tagUpStat tempStatArr[16] =
	{
		{3,6,9,12,L"심장",L" 최대 HP"},
		{2,3,4,5,L"폐",L" HP 재생"},
		{1,2,3,4,L"이",L" 생명 훔침"},
		{5,8,12,16,L"삼두근",L"% 데미지"},
		{2,4,6,8,L"팔뚝",L" 근거리 데미지"},
		{1,2,3,4,L"어깨",L" 원거리 데미지"},
		{1,2,3,4,L"뇌",L" 원소 데미지"},
		{5,10,15,20,L"반사신경",L"% 공격 속도"},
		{3,5,7,9,L"손가락",L"% 치명타율"},
		{2,3,4,5,L"두개골",L" 엔지니어링"},
		{15,30,45,60,L"눈",L" 범위"},
		{1,2,3,4,L"가슴",L" 방어력"},
		{3,6,9,12,L"척추",L"% 회피"},
		{3,6,9,12,L"다리",L"% 속도"},
		{5,10,15,20,L"코",L" 행운"},
		{5,8,10,12,L"손",L" 수확"}
	};

	for (int i = 0; i < 16; i++)
	{
		statArr[i] = tempStatArr[i];
	}
}

void RunScene::imageLoad()
{
	IMAGEMANAGER->addImage("맵1", "Resources/maps/Map1.bmp", 2800, 1600);
	IMAGEMANAGER->addImage("상점배경", "Resources/bg/shop_background.bmp", 1920, 1080);
	IMAGEMANAGER->addImage("마커", "Resources/marker/spawn_34_3.bmp", 102, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy1", "Resources/enemy/Baby_Alien.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI", "Resources/bg/UI.bmp", 316, 157, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드롭스0", "Resources/material/material_0000.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드롭스1", "Resources/material/material_0001.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드롭스2", "Resources/material/material_0002.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스탯1", "Resources/stats/stat_grade1.bmp", 363, 267, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스탯2", "Resources/stats/stat_grade2.bmp", 363, 267, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스탯3", "Resources/stats/stat_grade3.bmp", 363, 267, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스탯4", "Resources/stats/stat_grade4.bmp", 363, 267, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("히트", "Resources/hitEffect/hitFrame.bmp", 570, 219, 3, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스3", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스4", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스5", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스6", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스7", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스8", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("드롭스9", "Resources/bg/UI.bmp", 40, 40, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("웨이브시작1", "Resources/button/wavestart1.bmp", 411, 65, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("웨이브시작2", "Resources/button/wavestart2.bmp", 411, 65, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("일반총알", "Resources/bullet/bullet1.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("레이저총알", "Resources/bullet/bullet_laser.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("의료총알", "Resources/bullet/bullet_medical.bmp", 50, 50, true, RGB(255, 0, 255));


}

void RunScene::equipWeapon(int iNum, int grade)
{
	if (pWeaponIndex <= pMaxWeapon)
	{
		player->equipWeapon(iNum, pWeaponIndex, grade);
		WInven->equipWeapon(iNum, pWeaponIndex, grade);
		pWeaponIndex++;
	}
}

void RunScene::makeDRender(int dmg, int x, int y)
{
	DamageRenderer tmpDRender;
	tmpDRender.init(dmg, x, y);
	vDRender.push_back(tmpDRender);
}

void RunScene::cameraUpdate()
{
	renderPt = { player->getX() + 30, player->getY() + 30 };

	//가장자리 카메라 처리
	if (player->getX() + 30 < WINSIZE_X / 2)
	{
		renderPt.x = WINSIZE_X / 2;
		player->setOnMoveX(false);
	}
	if (player->getX() + 30 > 2800 - WINSIZE_X / 2)
	{
		renderPt.x = 2800 - WINSIZE_X / 2;
		player->setOnMoveX(false);
	}
	if (player->getY() + 30 < WINSIZE_Y / 2)
	{
		renderPt.y = WINSIZE_Y / 2;
		player->setOnMoveY(false);
	}
	if (player->getY() + 30 > 1600 - WINSIZE_Y / 2)
	{
		renderPt.y = 1600 - WINSIZE_Y / 2;
		player->setOnMoveY(false);
	}

	if (player->getX() + 30 > WINSIZE_X / 2 && player->getX() + 30 < 2800 - WINSIZE_X / 2)
	{
		player->setOnMoveX(true);
	}
	if (player->getY() + 30 > WINSIZE_Y / 2 && player->getY() + 30 < 1600 - WINSIZE_Y / 2)
	{
		player->setOnMoveY(true);
	}
	renderArea = RectMakeCenter(renderPt.x, renderPt.y, WINSIZE_X, WINSIZE_Y);
}

void RunScene::render()
{
	//cout << tmpGun->getPVBullets().size() << endl;
	SetBkMode(getMemDC(), TRANSPARENT);
	if (_openShop)
	{
		dpShopInterface();
		_shop.render(getMemDC());
		dpStat->render(getMemDC(), 1500, 30);
	}
	else
	{
		IMAGEMANAGER->render("맵1", getMemDC(), 0, 0, renderArea.left, renderArea.top, renderArea.right, renderArea.bottom);
		for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
		{
			(*iter)->render(getMemDC());
		}
		//
		//cout << tempEnemy->getDropsVector().size() << endl;
		for (int i = 0; i < vDrops.size();++i)
		{
			vDrops.at(i).render(getMemDC());
		}
		//for (auto vIt = tmpGun->getPVBullets().begin(); vIt != tmpGun->getPVBullets().end(); vIt++)
		//{
		//	vIt->render(getMemDC());
		//}
		for (int i = 0; i < pVBullets.size(); ++i)
		{
			pVBullets.at(i).render(getMemDC());
		}
		player->render();

		//데미지 표시
		dpDamage(getMemDC(), RGB(255,255,0), mediumFont);

		//테스트
		//DrawRectMake(getMemDC(),RectMakeCenter(player->getX()-renderPt.x+WINSIZE_X/2,player->getY()-renderPt.y+WINSIZE_Y/2, 60, 60));

		dpTime(getMemDC());
		dpInterface(getMemDC(), 34, 34);

		//테스트
		if (_testMode)
		{
			//DrawRectMake(getMemDC(), RectMake(player->getRX(), player->getRY(), 60, 60));
			//DrawRectMake(getMemDC(), RectMake(player->getX() - renderPt.x + WINSIZE_X / 2, player->getY() - renderPt.y + WINSIZE_Y / 2, 60, 60));
			//WInven->render(getMemDC());
		}
	}
	//테스트
	if (_testMode)
	{
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SelectObject(getMemDC(), TimerFont);

		TextOutW(getMemDC(), WINSIZE_X / 2 - 110, 200, levelUpText, wcslen(levelUpText));

		sReRollButton.render(getMemDC());
		for (auto vCIt = vSCard.begin(); vCIt != vSCard.end(); vCIt++)
		{
			(*vCIt)->render(getMemDC());
		}
		dpStat->render(getMemDC(), 1500, 150);

	}

	if (_levelUp)
	{
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SelectObject(getMemDC(), TimerFont);
		TextOutW(getMemDC(), WINSIZE_X / 2 - 110, 200, levelUpText, wcslen(levelUpText));
		sReRollButton.render(getMemDC());

		dpStat->render(getMemDC(), 1500, 150);

		for (auto vCIt = vSCard.begin(); vCIt != vSCard.end(); vCIt++)
		{
			(*vCIt)->render(getMemDC());
		}
	}
}

void RunScene::release()
{
	tempEnemy->release();
	tmpGun->release();
	for (auto it = vSCard.begin(); it != vSCard.end();)
	{
		(*it)->release();
		it = vSCard.erase(it);
	}
	dpStat->release();
	WInven->release();
	for (auto it = vEnemy.begin(); it != vEnemy.end();)
	{
		(*it)->release();
		it = vEnemy.erase(it);
	}
	player->release();
}

void RunScene::playerDie()
{
	player->setDeath(true);
	//플레이어 사망 처리
	vEnemy.clear();
	_onRun = false;
	_bTimeCount--;
	if (_bTimeCount <= 0)
	{
		//인벤토리, 달리기 결과 표시, 타이틀 돌아가기 버튼
	}
}

float RunScene::findTarget(int x, int y, int tX, int tY, int range)
{
	if ((sqrtf(pow(x - tX, 2) + pow(y - tY, 2)) <= range))
	{
		return atan2f(tY-y,  tX-x);
	}
	else
	{
		return NULL;
	}
}

int RunScene::findEnemy()
{
	float MinDist = 10000.0f;
	float tmpDist = 0.0f;
	int minENum = -1;
	for (auto iter = vEnemy.begin(); iter != vEnemy.end(); ++iter)
	{
		if (!(*iter)->getAlive())
		{
			continue;
		}
			tmpDist = sqrtf(pow(player->getX() - (*iter)->getX(), 2) + pow(player->getY() - (*iter)->getY(), 2));
			if (tmpDist < MinDist)
			{
				MinDist = tmpDist;
				minENum = (*iter)->getENum();
			}		
	}
	return minENum;
}

void RunScene::aimTarget(int ENum)
{
	/*for (int i = 1; i < 7; i++)
	{
		if (player->getSNum(i) == 0) continue;
		if (minD < player->getWRange(i))
		{
			player->setAngle(i, findTarget(player->getWX(i), player->getWY(i), eX, eY, minD));
		}
		else
		{
			player->setWIdle(i, true);
		}
	}*/

	for (int i = 0; i < player->getWIndex(); i++)
	{
		//적이없으면 나가기
		if (ENum < 0)
		{
			break;
		}
		//슬롯에 아이템 sNum=0이면
		if (player->getSNum(i) == 0)
		{
			continue;
		}
		int wX = player->getWX(i) - player->getRX() + player->getX();
		int wY = player->getWY(i) - player->getRY() + player->getY();
		float tmpDist = sqrtf(pow(wX - vEnemy.at(ENum)->getX(), 2) + pow(wY - vEnemy.at(ENum)->getY(), 2));
		
		if ((tmpDist <= player->getWRange(i)))
		{
			player->setWIdle(i, false);
			player->setAngle(i, 180 / M_PI * atan2f(vEnemy.at(ENum)->getY() - wY, vEnemy.at(ENum)->getX() - wX));
		}
		else
		{
			player->setWIdle(i, true);
		}
	}
}

void RunScene::dpTime(HDC hdc)
{
	string dpTime;
	string dpRound = "웨이브 ";
	char tempStr1[20];
	char tempStr2[20];
	dpTime = to_string(_rTimer);
	dpRound += to_string(_stageRound);
	strcpy_s(tempStr1, 20, dpTime.c_str());
	strcpy_s(tempStr2, 20, dpRound.c_str());

	SetTextColor(hdc, RGB(255, 255, 255));
	dpText(hdc, WINSIZE_X / 2 - 40, 70, tempStr1, TimerFont);
	dpText(hdc, WINSIZE_X / 2 - 112, 0, tempStr2, TimerFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, smallFont);
}

void RunScene::dpInterface(HDC hdc, int destX, int destY)
{
	char tempStr1[20];
	char tempStr2[20];
	char tempStr3[20];
	string dpNowHp = to_string(player->getHp());
	string dpMaxHp = to_string(player->getPStats().maxHp);
	string dpNowLv = to_string(player->getLv());
	string dpLv = "LV. ";
	string dpGold = to_string(player->getGold());

	dpNowHp += (string)" / ";
	dpNowHp += dpMaxHp;
	dpLv += dpNowLv;

	strcpy_s(tempStr1, 20, dpNowHp.c_str());
	strcpy_s(tempStr2, 20, dpLv.c_str());
	strcpy_s(tempStr3, 20, dpGold.c_str());

	float hpRatio = (float)player->getHp() / player->getPStats().maxHp;
	float expRatio = (float)player->getExp() / player->getMaxExp();
	IMAGEMANAGER->render("UI", hdc, destX, destY);
	oldPen = (HPEN)SelectObject(hdc, nullPen);
	oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
	if (hpRatio >= 0 && hpRatio <= 1)
	{
		RectangleMake(hdc, 6 + destX, 7 + destY, (int)(hpRatio * barWidth), barHeight);
	}
	if (expRatio >= 0 && hpRatio <= 1)
	{
		SelectObject(hdc, greenBrush);
		RectangleMake(hdc, 6 + destX, 59 + destY, (int)(expRatio * barWidth), barHeight);
	}
	// hp 표시
	//SetTextColor(hdc, RGB(0, 0, 0));
	//dpText(hdc, 155, 36, tempStr1, mediumOutFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	dpText(hdc, 153, 34, tempStr1, mediumFont);
	// 레벨 표시
	//SetTextColor(hdc, RGB(0, 0, 0));
	//dpText(hdc, 260, 88, tempStr2, mediumOutFont);

	dpText(hdc, 266, 88, tempStr2, mediumFont);
	dpText(hdc, 100, 126, tempStr3, TimerFont);

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, smallFont);
}

void RunScene::dpShopInterface()
{
	IMAGEMANAGER->render("상점배경", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, 0, 0, 1920, 1080);
	for (auto it = vShopButton.begin(); it != vShopButton.end(); ++it)
	{
		it->render(getMemDC());
	}
	WInven->render(getMemDC());
}

HFONT RunScene::setFont(int fSize, int fWeight, char* fontName)
{
	return CreateFont(fSize, 0, 0, 0, fWeight, 0, 0, 0, 0, OUT_OUTLINE_PRECIS, 0, DEFAULT_QUALITY, 0, fontName);
}

void RunScene::dpText(HDC hdc, int destX, int destY, char* str, HFONT font)
{
	//char* tempStr = str;
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, font);
	TextOut(hdc, destX, destY, str, strlen(str));
}

void RunScene::dpDamage(HDC hdc, COLORREF rgb, HFONT font)
{
	//데미지 표시하기
	//cout << vDRender.size() << endl;
	SetTextColor(hdc, rgb);
	SelectObject(hdc, font);
	for (auto dRIt = vDRender.begin(); dRIt != vDRender.end(); dRIt++)
	{
		dRIt->render(getMemDC());
	}
	SetTextColor(hdc, (255, 255, 255));
}