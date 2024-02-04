#include "ui/CocosGUI.h"
#include "UITextSingleLayer.h"

USING_NS_CC;
using namespace std;

UITextSingleLayer* UITextSingleLayer::create(string textImage, string buttonImage, string buttonClicked, bool fore) {
    UITextSingleLayer *ret = new (std::nothrow) UITextSingleLayer;
    if (ret)
    {
        ret->init(textImage, buttonImage, buttonClicked, fore);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void UITextSingleLayer::init(string textImage, string buttonImage, string buttonClicked, bool fore) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Add foreground
    if (fore) {
        auto fore = Sprite::create(TEXT_SINGLE_LAYER_FORE_FILENAME);
        this->addChild(fore);
        fore->setGlobalZOrder(12.0f);
        fore->setOpacity(128);
        fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    }

    // Add layer box
    auto box = Sprite::create(TEXT_SINGLE_LAYER_FILENAME);
    this->addChild(box);
    box->setGlobalZOrder(12.0f);
    box->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add text
    auto text = Sprite::create(textImage);
    text->setScale(480.f / text->getContentSize().width);
    this->addChild(text);
    text->setGlobalZOrder(12.0f);
    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30.0f);

    // Add button
    button = ui::Button::create(buttonImage, buttonClicked, buttonClicked);
    this->addChild(button);
    button->setGlobalZOrder(12.0f);
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30.0f));
}

void UITextSingleLayer::setButtonTouch(function<void(Ref*, ui::Widget::TouchEventType)> touch) {
    button->addTouchEventListener(touch);
}