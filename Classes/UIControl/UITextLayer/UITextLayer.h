#ifndef __UI_TEXT_LAYER_H__
#define __UI_TEXT_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

#define TEXT_LAYER_FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define TEXT_LAYER_FILENAME "sprites/objects/button/text_layer_base.png"
#define TEXT_LAYER_OKAY_FILENAME "sprites/objects/button/layer_button_okay.png"
#define TEXT_LAYER_OKAY_CLICKED_FILENAME "sprites/objects/button/layer_button_okay_clicked.png"
#define TEXT_LAYER_CANCEL_FILENAME "sprites/objects/button/layer_button_cancel.png"
#define TEXT_LAYER_CANCEL_CLICKED_FILENAME "sprites/objects/button/layer_button_cancel_clicked.png"

class UITextLayer : public cocos2d::Layer {
public:
    virtual void init(std::string);
    virtual void setOkayTouch(std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)>);
    virtual void setCancelTouch(std::function<void()>);
private:
    cocos2d::ui::Button* cancel;
    cocos2d::ui::Button* okay;
    std::function<void()> tempCall;
};

#endif // !__UI_TEXT_LAYER_H__