#pragma once

class itemCard
{
private:
	int _itemNum;
	int _itemGrade;
	int _itemPrice;
	int _price;
	int _slotNum;
	string _iKey;
	bool _isSoldOut;

public:
	void init(int iNum, int iGrade, int nowround,string ikey, int sNum);
	void update();
	void render(HDC hdc);
	void release();
	bool getSoldOut() { return _isSoldOut; }
	void setSoldOut(bool sold) { _isSoldOut = sold; }
	int getItemPrice() { return _itemPrice; }
	int getSlotNum() { return _slotNum; }
	void setItemPrice(int price) { _price = price; }
	int getINum() { return _itemNum; }
	int getIGrade() {return _itemGrade;}
	string getIKey() { return _iKey; }

};

