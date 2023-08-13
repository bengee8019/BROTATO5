#pragma once
#include "GameNode.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "RunScene.h"

class maingame :public GameNode
{
private:
	bool sceneChange;
	int nowScene;
	TitleScene* _title;
	SelectScene* _select;
	RunScene* _run;
	bool firstRun;

	GameNode* _currentScene;

	int playerRole;

public:

	HRESULT init();
	void update();
	void render();
	void release();

	maingame() : _currentScene(_title) {}
	~maingame() {}
};

