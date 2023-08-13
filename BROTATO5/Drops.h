#pragma once

struct tagDrop
{
	int gold;
	int exp;
};

class Drops
{
private:
	bool _isItem;
	bool _onRender;
	string _key;
	int _x, _y;
	int _cX, _cY;
	int width, height;
	int _gold;
	int _exp;
	int _px, _py;
	int _range;

public:
	void init(bool isitem, int x, int y, int gold, int exp);
	//void setPInfo(int px, int py, int range);
	void render(HDC hdc);
	void update();
	void release();

	bool getOnRender() { return _onRender; }

	int getDX() { return _x; }
	int getDY() { return _y; }
	void setCameraX(int cx) { _cX = cx; }
	void setCameraY(int cy) { _cY = cy; }
	void setPlayerX(int px) { _px = px; }
	void setPlayerY(int py) { _py = py; }

	int getExp() { return _exp; }
	int getGold() { return _gold; }
	void setRange(int range) { _range = 20 * range; }

};

