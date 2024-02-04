#include "UITextLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

void UITextLayer::init(string textFileName) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Add foreground
    auto fore = Sprite::create(TEXT_LAYER_FORE_FILENAME);
    this->addChild(fore);
    fore->setGlobalZOrder(12.0f);
    fore->setOpacity(128);
    fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add layer box
    auto box = Sprite::create(TEXT_LAYER_FILENAME);
    this->addChild(box);
    box->setGlobalZOrder(12.0f);
    box->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add text
    auto text = Sprite::create(textFileName);
    text->setScale(480.f / text->getContentSize().width);
    this->addChild(text);
    text->setGlobalZOrder(12.0f);
    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30.0f);

    // Add cancel button
    cancel = ui::Button::create(TEXT_LAYER_CANCEL_FILENAME, TEXT_LAYER_CANCEL_CLICKED_FILENAME, TEXT_LAYER_CANCEL_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> cancelTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:  
                    this->removeFromParent();   
                    break;
                default:
                    break;
            }
        };
    };
    
    cancel->addTouchEventListener(cancelTouch());
    this->addChild(cancel);
    cancel->setGlobalZOrder(12.0f);
    cancel->setPosition(Vec2(visibleSize.width / 2 + origin.x + 105.0f, visibleSize.height / 2 + origin.y - 30.0f));

    // Add okay button
    okay = ui::Button::create(TEXT_LAYER_OKAY_FILENAME, TEXT_LAYER_OKAY_CLICKED_FILENAME, TEXT_LAYER_OKAY_CLICKED_FILENAME);
    this->addChild(okay);
    okay->setGlobalZOrder(12.0f);
    okay->setPosition(Vec2(visibleSize.width / 2 + origin.x - 105.0f, visibleSize.height / 2 + origin.y - 30.0f));
}

void UITextLayer::setOkayTouch(function<void(Ref*, ui::Widget::TouchEventType)> okayTouch) {
    okay->addTouchEventListener(okayTouch);
}

void UITextLayer::setCancelTouch(function<void()> call) {
    tempCall = call;

    function<function<void(Ref*, ui::Widget::TouchEventType)>()> cancelTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                {    
                    this->tempCall();
                    this->removeFromParent();   
                    break;
                }
                default:
                    break;
            }
        };
    };

    cancel->addTouchEventListener(cancelTouch());
}