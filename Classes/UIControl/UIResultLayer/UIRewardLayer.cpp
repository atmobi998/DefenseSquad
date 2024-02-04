#include "UIRewardLayer.h"
#include "UIObjects/uiobj.h"
#include "Models/Character/Cell/CellModelDefinitions.h"

USING_NS_CC;
using namespace std;

UIRewardLayer* UIRewardLayer::create(CellId id, function<void(Ref*, ui::Widget::TouchEventType)> call) {
    UIRewardLayer *ret = new (std::nothrow) UIRewardLayer;
    if (ret)
    {
        ret->init(id, call);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void UIRewardLayer::init(CellId id, function<void(Ref*, ui::Widget::TouchEventType)> call) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Reward base
    auto base = Sprite::create(REWARD_LAYER_BASE);
    this->addChild(base);
    base->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    base->setGlobalZOrder(12.0f);

    // UICell
    auto cell = UICell::create(id);
    this->addChild(cell);
    cell->setAnchorPoint(Vec2(0.5f, 0.5f));
    cell->setPosition(visibleSize.width / 2 + origin.x - 165.0f, visibleSize.height / 2 + origin.y);
    cell->setGlobalZOrder(12.0f);
    cell->idleAnimate();

    // Your reward
    auto yourReward = Sprite::create(REWARD_TEXT);
    yourReward->setScale(300.0f / yourReward->getContentSize().width);
    this->addChild(yourReward);
    yourReward->setPosition(visibleSize.width / 2 + origin.x + 90.0f, visibleSize.height / 2 + origin.y + 120.0f);
    yourReward->setGlobalZOrder(12.0f);

    // Description
    string descriptionText = "sprites/objects/button/reward_layer/text_cell0";
    descriptionText = descriptionText + to_string((int) id);
    descriptionText = descriptionText + ".png";
    auto desciption = Sprite::create(descriptionText);
    desciption->setScale(300.0f / desciption->getContentSize().width);
    this->addChild(desciption);
    desciption->setPosition(visibleSize.width / 2 + origin.x + 90.0f, visibleSize.height / 2 + origin.y);
    desciption->setGlobalZOrder(12.0f);

    // Okay button
    auto button = ui::Button::create(REWARD_OKAY, REWARD_OKAY_CLICKED, REWARD_OKAY_CLICKED);
    this->addChild(button);
    button->setGlobalZOrder(12.0f);
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x + 90.0f, visibleSize.height / 2 + origin.y - 120.0f));
    button->addTouchEventListener(call);
}