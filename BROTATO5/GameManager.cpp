#include "Stdafx.h"
#include "GameManager.h"
#include "maingame.h"

HRESULT GameManager::init(void)
{
	GameNode::init(true);
	_GN = new maingame;
	_GN->init();

	return S_OK;
}

void GameManager::release(void)
{
	_GN->release();
	GameNode::release();
}

void GameManager::update(void)
{
	GameNode::update();
	_GN->update();
}

void GameManager::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================

	_GN->render();

	// ========================================================
	this->getBackBuffer()->render(this->getHDC(), 0, 0);
}
