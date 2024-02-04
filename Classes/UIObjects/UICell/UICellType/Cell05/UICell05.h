#ifndef __UI_CELL_05_H__
#define __UI_CELL_05_H__

class UICell;
class UICell05 : public UICell {
public:
	static UICell05* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	virtual void attackAnimate();
	//virtual void effectAnimate();
	virtual void hitAnimate();
	virtual void dieAnimate();
};
#endif // !__UI_CELL_05_H__