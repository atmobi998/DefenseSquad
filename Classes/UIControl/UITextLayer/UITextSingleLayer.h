#ifndef __UI_TEXT_SINGLE_LAYER_H__
#define __UI_TEXT_SINGLE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

#define TEXT_SINGLE_LAYER_FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define TEXT_SINGLE_LAYER_FILENAME "sprites/objects/button/text_layer_base.png"

class UITextSingleLayer : public cocos2d::Layer {
public:
    static UITextSingleLayer* create(std::string textImage, std::string buttonImage, std::string buttonClicked, bool fore);
    virtual void init(std::string textImage, std::string buttonImage, std::string buttonClicked, bool fore);
    virtual void setButtonTouch(std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
protected:
    cocos2d::ui::Button* button;
};

#endif // !__UI_TEXT_LAYER_H__