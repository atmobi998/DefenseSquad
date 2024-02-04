#include "UITextGeneralLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

UITextGeneralLayer* UITextGeneralLayer::create(string textImage, string leftImage, string leftClicked, string rightImage, string rightClicked, bool fore) {
    UITextGeneralLayer *ret = new (std::nothrow) UITextGeneralLayer;
    if (ret)
    {
        ret->init(textImage, leftImage, leftClicked, rightImage, rightClicked, fore);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void UITextGeneralLayer::init(string textImage, string leftImage, string leftClicked, string rightImage, string rightClicked, bool fore) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Add foreground
    if (fore) {
        auto fore = Sprite::create(TEXT_GENERAL_LAYER_FORE_FILENAME);
        this->addChild(fore);
        fore->setGlobalZOrder(12.0f);
        fore->setOpacity(128);
        fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    }

    // Add layer box
    auto box = Sprite::create(TEXT_GENERAL_LAYER_FILENAME);
    this->addChild(box);
    box->setGlobalZOrder(12.0f);
    box->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add text
    auto text = Sprite::create(textImage);
    text->setScale(480.f / text->getContentSize().width);
    this->addChild(text);
    text->setGlobalZOrder(12.0f);
    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30.0f);

    // Add right button
    buttonRight = ui::Button::create(rightImage, rightClicked, rightClicked);
    this->addChild(buttonRight);
    buttonRight->setGlobalZOrder(12.0f);
    buttonRight->setPosition(Vec2(visibleSize.width / 2 + origin.x + 105.0f, visibleSize.height / 2 + origin.y - 30.0f));

    // Add left button
    buttonLeft = ui::Button::create(leftImage, leftClicked, leftClicked);
    this->addChild(buttonLeft);
    buttonLeft->setGlobalZOrder(12.0f);
    buttonLeft->setPosition(Vec2(visibleSize.width / 2 + origin.x - 105.0f, visibleSize.height / 2 + origin.y - 30.0f));
}

void UITextGeneralLayer::setButtonRightTouch(function<void(Ref*, ui::Widget::TouchEventType)> touch) {
    buttonRight->addTouchEventListener(touch);
}

void UITextGeneralLayer::setButtonLeftTouch(function<void(Ref*, ui::Widget::TouchEventType)> touch) {
    buttonLeft->addTouchEventListener(touch);
}