#ifndef __UI_CELL_02_H__
#define __UI_CELL_02_H__

class UICell;
class UICell02 : public UICell {
public:
    static UICell02* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	//virtual void effectAnimate();
	virtual void hitAnimate();
	virtual void dieAnimate();
};

#endif // !__UI_CELL_02_H__