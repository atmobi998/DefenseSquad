#ifndef __UI_CONTROL_CELLBAR_H__
#define __UI_CONTROL_CELLBAR_H__

#include "cocos2d.h"
#include "UIControlCellBarDefinitions.h"
#include "../UIControl.h"
#include "Models/models.h"

class UIControlCellBar : public UIControl {
public:
	virtual void addToScene(cocos2d::Scene* scene);
	virtual void onTouch();
	void touchControlEvent(Ref *sender, ui::Widget::TouchEventType type);
	void updateRecharge(double);
	static UIControlCellBar* create(LevelModel*, CellId, int, double);
private:
	CellId id;
	Scene* scene;
	LevelModel* level;
	Sprite* loading;
	Sprite* choosing;
	int cost;
	bool canActivate;
	double distance;
	void flashAnimate();
};

#endif // !__UI_CONTROL_CELLBAR_H__