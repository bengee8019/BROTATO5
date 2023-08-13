#pragma once
#include "Scene.h"
#include "Button.h"
class SelectScene :public Scene
{
private:
	int _sNum;
public:
	HRESULT init();
	void update();
	void render();
	void release();

};

