#ifndef __UI_CONTROL_H__
#define __UI_CONTROL_H__

#include "cocos2d.h"
#include "UIControlDefinitions.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class UIControl : public ui::Button {
public:
	virtual void addToScene(cocos2d::Scene* scene);
    virtual void removeFromScene();
};

#endif // !__UI_CONTROL_H__