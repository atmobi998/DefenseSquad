#ifndef __UI_CELL_00_H__
#define __UI_CELL_00_H__
#include "cocos2d.h"
class UICell;
class UICell00 : public UICell {
public:
    static UICell00* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	virtual void attackAnimate();
	virtual void hitAnimate();
	virtual void dieAnimate();
};

#endif // !__UI_CELL_00_H__