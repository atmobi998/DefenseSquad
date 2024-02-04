#ifndef __UI_CELL_H__
#define __UI_CELL_H__

#include "UICellDefinitions.h"
#include "cocos2d.h"
#include <functional>

class UIObjects;

class UICell : public UIObjects {
public:
    static UICell* create(CellId);
    virtual void addToScene(cocos2d::Scene*);
    virtual void idleAnimate() {}
    virtual void attackAnimate() {}
    virtual void effectAnimate() {}
    virtual void effectAnimate(std::function<void()>) {}
    virtual void hitAnimate() {}
    virtual void dieAnimate() {}
};

#endif // !__UI_CELL_H__