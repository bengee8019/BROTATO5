#pragma once
#include "GameNode.h"
#include "Button.h"

class Scene : public GameNode
{
protected:
    vector<Button> vButton;
    int selectNum;
    bool sceneChange;
public:
    virtual HRESULT init();
    virtual void update();
    virtual void render();
    virtual void release();

    int getSNum() { return selectNum; }
    void setSNum(int sNum) { selectNum = sNum; }
    int getSChange() { return sceneChange; }
    void setSChange(bool sChange) { sceneChange = sChange; }
};

