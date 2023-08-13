#include "Stdafx.h"
#include "maingame.h"



HRESULT maingame::init()
{
	GameNode::init(true);
	sceneChange = false;
	nowScene = 1;
	playerRole = 0;
	_title = new TitleScene;
	_title->init();
	_select = new SelectScene;
	_run = new RunScene;
	firstRun = true;

	_currentScene = _title;
	//_currentScene->init();


	assert(_currentScene != nullptr,"MainGame 초기화 부분에서 노드 파트 오류 발생");

	return S_OK;
}

//sNum:			0: Quit		1:  Title,	2:	Select,		3: Run,		4: Shop,	5: Result


void maingame::update()
{
	GameNode::update();
	switch (nowScene)
	{
	case 1:
	{
		sceneChange = _title->getSChange();
		if (sceneChange)
		{
			nowScene = _title->getSNum();
		}
		break;
	}
	case 2:
	{
		sceneChange = _select->getSChange();
		if (sceneChange)
		{
			nowScene = 3;
		}
		playerRole = _select->getSNum();
		if (playerRole == 1)
		{
			playerRole = RND->getFromInTo(2, 4);
		}

		break;
	}
	/*case 3:
	{
		sceneChange = _run->getSChange();
		if (sceneChange)
		{
			switch()
		}
		break;
	}*/
	}


	if (sceneChange)
	{
		switch (nowScene)
		{
		case 10:
		{
			PostQuitMessage(0);
		}
	 
		case 1:
		{
			_currentScene = _title;
			_title->setSChange(false);
			_select->setSChange(false);
			_run->setSChange(false);
			break;
		}

		case 2:
		{
			_currentScene = _select;
			_select->init();
			_title->setSChange(false);
			_select->setSChange(false);
			_run->setSChange(false);
			break;
		}
		case 3:
		{
			_currentScene = _run;
			_run->setPRole(playerRole);
			if (firstRun)
			{
				_run->init();
				firstRun = false;
			}
			_title->setSChange(false);
			_select->setSChange(false);
			_run->setSChange(false);
			break;
		}

		}
	}
	_currentScene->update();


	//if () _currentScene = _select;
	//if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON)) _currentScene = _start;

}

void maingame::render()
{
	_currentScene->render();
}

void maingame::release()
{
	SAFE_DELETE(_title);
	SAFE_DELETE(_select);
	SAFE_DELETE(_run);
}
