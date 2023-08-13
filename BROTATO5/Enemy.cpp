#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int roundnum)
{
    _eType = 1;
    _Count = 0;
    eX = eY = 0;
    eWidth = 100;
    eHeight = 100;
	_roundNum = roundnum;
    //###적 애니메이션 처리하기
    animRender = 0;
    _angle = 0.0f;
    _hp = 8+ _roundNum;
	_eDmg = 3 + _roundNum / 3;
	_eSpd = 5 + _roundNum / 5;
    rInt = RND->getInt(3);
	_dropIng = 1 + _roundNum / 5;
	_dropGold = 1 + _roundNum / 5;
	_dropExp = 1 + _roundNum / 5;
    isSpawning = false;
    isAlive = false;
	knockBack = 0;

    spawn();
    return S_OK;
}


void Enemy::update()
{
    if (_hp <= 0)
    {
		death();
    }

    if (isSpawning)
    {
        _Count++;
        if (_Count >= 100)
        {
            isSpawning = false;
            isAlive = true;
            _Count = 0;
        }
    }
    else if (isAlive)
    {
		if (knockBack > 0)
		{
			eX -= _eSpd * cosf(_angle);
			eY -= _eSpd * sinf(_angle);
			knockBack--;
		}
		else
		{
			eX += _eSpd * cosf(_angle);
			eY += _eSpd * sinf(_angle);
		}
		eRect = RectMakeCenter(eX, eY, eWidth, eHeight);
    }
    //else
    //{
    //    spawn();
    //}
}

void Enemy::render(HDC hdc)
{
    if (onRender)
    {
        if (isSpawning)
        {
            IMAGEMANAGER->render("마커", hdc, renderEX - eWidth / 2, renderEY - eHeight / 2, 68, 68, rInt * 34, 0, 34, 34);
        }

        if (isAlive)
        {
            IMAGEMANAGER->render("enemy1", hdc, renderEX - eWidth / 2, renderEY - eHeight / 2, 0, 0, eWidth, eHeight);
            //DrawRectMake(hdc, RectMakeCenter(eX, eY, eWidth, eHeight));
        }
    }
}


void Enemy::release()
{
}

void Enemy::spawn()
{
    eX = RND->getFromInTo(70, 2730);
    eY = RND->getFromInTo(70, 1530);
    isSpawning = true;
    _hp = 8;
    _Count = 0;
}

void Enemy::death()
{
    //_dropIng 만큼 재료 드랍, 사망처리
	drop();
    isAlive = false;
    eX = -500;
    eY = -500;
    renderEX = -500;
    renderEY = -500;
    spawn();
}

void Enemy::drop()
{
	//if()
	
	for (int i = 0; i < _dropIng; i++)
	{
		Drops tmpDrop;
		tmpDrop.init(false, eX + RND->getInt(50), eY + RND->getInt(50), _dropGold, _dropExp);
		vDrops.push_back(tmpDrop);
	}
}

tagDrop Enemy::dropCheck(int pgold, int pexp)
{
    int tmpGold = pgold;
    int tmpExp = pexp;

 //   for (int i = 0; i < vDrops.size();)
	//{
	//	vDrops[i].update();
	//	if (vDrops[i].getOnRender() == false)
	//	{
 //           tmpExp += vDrops[i].getExp();
 //           tmpGold += vDrops[i].getGold();
	//		vDrops.erase(vDrops.begin() + i);
	//	}
	//	else
	//	{
	//		i++;
	//	}
	//}
    for (auto it = vDrops.begin(); it != vDrops.end();)
    {
        it->update();
        if (it->getOnRender() == false)
        {
            tmpGold += it->getGold();
            tmpExp += it->getExp();
            it=vDrops.erase(it);
			SOUNDMANAGER->playSound("getDrops", 0.8);
			//int tmpSoundIndex = RND->getInt(4);
			//switch (tmpSoundIndex)
			//{
			//case 0:
			//{			
			//	break;
			//}
			//case 1:
			//{
			//	SOUNDMANAGER->playEffectSoundWave(TEXT("Resources/music/effectSound/harvest/cartoon_boing_jump_06.wav"));
			//	break;
			//}
			//case 2:
			//{
			//	SOUNDMANAGER->playEffectSoundWave(TEXT("Resources/music/effectSound/harvest/cartoon_boing_jump_07.wav"));
			//	break;
			//}
			//case 3:
			//{
			//	SOUNDMANAGER->playEffectSoundWave(TEXT("Resources/music/effectSound/harvest/cartoon_boing_jump_09.wav"));
			//	break;
			//}
			//}
            continue;
        }
        else
        {
            it++;
        }
    }
    return { tmpGold , tmpExp };
}

void Enemy::dropSet(int px, int py, int cx, int cy, int range)
{

    for (int i = 0; i < vDrops.size();++i)
    {
        vDrops.at(i).setPlayerX(px);
        vDrops.at(i).setPlayerY(py);
        vDrops.at(i).setCameraX(cx);
        vDrops.at(i).setCameraY(cy);
        vDrops.at(i).setRange(range);
    }
}

//void Enemy::roundEnd()
//{
//    for (int i = 0; i < vDrops.size(); i++)
//    {
//        vDrops.at(i).setRange(5000);
//    }
//}



//void Enemy::dUpdate()
//{
//	for (int i = 0; i < vDrops.size();)
//	{
//		if (vDrops.at(i).getOnRender() == false)
//		{
//			vDrops.erase(vDrops.begin() + i);
//		}
//		else
//		{
//			vDrops.at(i).update();
//			i++;
//		}
//	}
//}