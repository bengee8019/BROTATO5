#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
public:
private:
	bitset<KEY_MAX> KeyUp;
	bitset<KEY_MAX> KeyDown;
public:
	KeyManager();
	~KeyManager();
	HRESULT init(void);
	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp() { return KeyUp; }
	bitset<KEY_MAX> getKeyDown() { return KeyDown; }

	void setKeyUp(int key, bool state) { KeyUp.set(key, state); }
	void setKeyDown(int key, bool state) { KeyDown.set(key, state); }

};

