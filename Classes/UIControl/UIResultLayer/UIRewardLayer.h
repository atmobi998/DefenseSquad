#ifndef __UI_REWARD_LAYER_H__
#define __UI_REWARD_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>
#include "Models/Character/Cell/CellModelDefinitions.h"

#define REWARD_LAYER_BASE "sprites/objects/button/reward_layer/reward_base.png"
#define REWARD_TEXT "sprites/objects/button/reward_layer/reward_text.png"
#define REWARD_OKAY "sprites/objects/button/layer_button_okay.png"
#define REWARD_OKAY_CLICKED "sprites/objects/button/layer_button_okay_clicked.png"

class UICell;

class UIRewardLayer : public cocos2d::Layer {
public:
    static UIRewardLayer* create(CellId, std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
    void init(CellId, std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
protected:
};

#endif // !__UI_REWARD_LAYER_H__