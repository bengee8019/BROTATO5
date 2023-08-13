#pragma once
#include "GameNode.h"

class GameManager :public GameNode
{
private:
	GameNode* _GN;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	GameManager() {}
	~GameManager() {}

};

