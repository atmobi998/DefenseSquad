#ifndef __UI_CELL_03_H__
#define __UI_CELL_03_H__

class UICell;
class UICell03 : public UICell {
public:
    static UICell03* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	virtual void attackAnimate();
	//virtual void effectAnimate();
	virtual void hitAnimate();
	virtual void dieAnimate();
};

#endif // !__UI_CELL_03_H__