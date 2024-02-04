#ifndef __UI_TEXT_GENERAL_LAYER_H__
#define __UI_TEXT_GENERAL_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

#define TEXT_GENERAL_LAYER_FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define TEXT_GENERAL_LAYER_FILENAME "sprites/objects/button/text_layer_base.png"

class UITextGeneralLayer : public cocos2d::Layer {
public:
    static UITextGeneralLayer* create(std::string textImage, std::string leftImage, std::string leftClicked, std::string rightImage, std::string rightClicked, bool fore);
    virtual void init(std::string textImage, std::string leftImage, std::string leftClicked, std::string rightImage, std::string rightClicked, bool fore);
    virtual void setButtonLeftTouch(std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
    virtual void setButtonRightTouch(std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
private:
    cocos2d::ui::Button* buttonLeft;
    cocos2d::ui::Button* buttonRight;
};

#endif // !__UI_TEXT_LAYER_H__