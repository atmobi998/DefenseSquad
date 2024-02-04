#ifndef __UI_CELL_04_H__
#define __UI_CELL_04_H__

class UICell;

#define CELL_04_EFFECT_FILENAME "sprites/objects/projectile/cell_04_effect.png"

class UICell04 : public UICell {
public:
    static UICell04* create();
	virtual void addToScene(cocos2d::Scene*);
	virtual void idleAnimate();
	virtual void effectAnimate();
	//virtual void hitAnimate();
	virtual void dieAnimate();
};

#endif // !__UI_CELL_04_H__