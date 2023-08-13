#pragma once

class DamageRenderer
{
private:
	string tmpStr;
	char cstr[10];
	int numWidth, numHeight;
	int numberIndex;
	int _x, _y;
	int _renderX, _renderY;
	int CameraX, CameraY;

	int _dmg;
	int _tickCount;
	int hitFrame;
	bool _timeOut;
	
public:
	void init(int dmg, int x, int y);
	void update(int cX, int cY);
	void render(HDC hdc);
	bool getTimeOut() { return _timeOut; }

	DamageRenderer();
	~DamageRenderer();

};

