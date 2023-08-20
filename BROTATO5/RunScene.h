#pragma once
#include "Scene.h"
#include "rotateRender.h"
#include "Player.h"
#include "Enemy.h"
#include "DamageRenderer.h"
#include "WInventory.h"
#include "Guns.h"
#include "statUI.h"
#include "Shop.h"

//테스트
#include "statCard.h"

class RunScene :public Scene
{
protected:
	Player* player;
	vector<Enemy*> vEnemy;
	vector<DamageRenderer> vDRender;
	vector<Button> vShopButton;
	WInventory* WInven;
	statUI* dpStat;
	Button sReRollButton;
	//테스트
	vector<statCard*> vSCard;
	Guns* tmpGun;
	Enemy* tempEnemy;
	Shop _shop;

	tagUpStat statArr[16];

	int _bgmCount;

	int _stageRound;
	int _initRTime;
	int _rTimeCount;
	int _breakTime;
	int _bTimeCount;
	int _rTimer;
	int _hitTimer;
	int statRerollCount;

	bool _onRun;
	bool _openShop;
	bool _ready;
	bool _isClear;
	bool _levelUp;

	int pMaxWeapon;
	int pWeaponIndex;

	int _iEnemyNum;
	int _iIndex;
	int _MaxEnemyNum;
	
	int playerRole;
	float angle;
	POINT renderPt;
	RECT renderArea;
	wchar_t levelUpText[20];

	int lvRerollFee;

	int barWidth;
	int barHeight;

	HPEN oldPen;
	HBRUSH oldBrush;

	HPEN nullPen;
	HBRUSH redBrush;
	HBRUSH greenBrush;

	HFONT TimerFont;
	HFONT LargeFont;
	HFONT mediumFont;
	HFONT smallFont;
	bool _testMode;

public:
	HRESULT init();
	void update();
	void setNewRound();

	void vSCardReRoll();
	void statDataLoad();
	void imageLoad();
	void equipWeapon(int iNum, int grade);
	void makeDRender(int dmg, int x, int y);
	void cameraUpdate();
	void render();
	void release();
	void playerDie();
	float findTarget(int x, int y, int tX, int tY, int range);
	int findEnemy();
	void aimTarget(int ENum);
	void dpTime(HDC hdc);
	void dpInterface(HDC hdc, int destX, int destY);
	void dpShopInterface();
	void setPRole(int prole) { playerRole = prole; }
	HFONT setFont(int fSize, int fWeight, char* fontName);
	void dpText(HDC hdc, int destX, int destY, char* str, HFONT font);
	void dpDamage(HDC hdc, COLORREF, HFONT);
};