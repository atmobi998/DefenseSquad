#ifndef __UI_DISEASE_00_H__
#define __UI_DISEASE_00_H__

#include "cocos2d.h"
using namespace cocos2d;

class UIDisease;
class UIDisease00 : public UIDisease {
public:
    static UIDisease00* create();
	//virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate(Direction dir);
	virtual void walkAnimate(Direction dir);
	virtual void attackAnimate(Direction dir);
	virtual void hitAnimate(Direction dir);
	virtual void dieAnimate(Direction dir);

	Animation *animation;
	Animate* animate;
};

#endif // !__UI_DISEASE_00_H__