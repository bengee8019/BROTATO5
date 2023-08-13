#pragma once
class Button
{
private:
	RECT _bArea;
	string _key1;
	string _key2;
	int _sNum;
	bool _bOnMouse;
	bool _bSelect;
	bool _onSound;
	bool _active;
public:
	RECT getArea() { return _bArea; }

	//버튼객체 생성시 초기화 함수
	void setButton(int x, int y, int width, int height, string key1, string key2, char* dir1, char* dir2, int sNum);
	int getSNum() { return _sNum; }
	void render(HDC hdc);
	void update(POINT mPt);
	bool getOnMouse() { return _bOnMouse; }
	void setOnMouse(bool onMouse) { _bOnMouse = onMouse; }
	string getKey2() { return _key2; }
	string getKey1() { return _key1; }
	void setActive(bool active) { _active = active; }
	Button();
	~Button();
};

