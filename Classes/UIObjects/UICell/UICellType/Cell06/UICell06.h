#ifndef __UI_CELL_06_H__
#define __UI_CELL_06_H__

class UICell;

#define CELL_06_EFFECT_FILENAME "sprites/objects/projectile/cell_06_effect.png"

class UICell06 : public UICell {
public:
	static UICell06* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	virtual void effectAnimate();
	//virtual void hitAnimate();
	virtual void dieAnimate();
};
#endif // !__UI_CELL_05_H__L_H__