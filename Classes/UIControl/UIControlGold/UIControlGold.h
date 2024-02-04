#ifndef __UI_CONTROL_GOLD_H__
#define __UI_CONTROL_GOLD_H__

#include "cocos2d.h"
#include "UIControlGoldDefinitions.h"
#include "../UIControl.h"

class UIControlGold : public UIControl {
public:
	virtual void addToScene(cocos2d::Scene* scene);
	virtual void removeFromScene();
	virtual void setCellPosition(double, double);
	void idleAnimate();
	void destroyAnimate();
	void touchControlEvent(Ref *sender, ui::Widget::TouchEventType type);
	virtual void onTouch();
	static UIControlGold* create();
};

#endif // !__UI_CONTROL_GOLD_H__