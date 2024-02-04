#ifndef __GS_TUTORIAL_H__
#define __GS_TUTORIAL_H__

#include "cocos2d.h"
#include <functional>

#define TUTORIAL_FORE "sprites/tutorial/tutorial_fore.png"
#define TUTORIAL_OKAY "sprites/tutorial/layer_button_okay.png"
#define TUTORIAL_OKAY_CLICKED "sprites/tutorial/layer_button_okay_clicked.png"
#define TUTORIAL_1 "sprites/tutorial/tutorial_1.png"
#define TUTORIAL_2 "sprites/tutorial/tutorial_2.png"
#define TUTORIAL_3 "sprites/tutorial/tutorial_3.png"
#define TUTORIAL_4 "sprites/tutorial/tutorial_4.png"
#define TUTORIAL_5 "sprites/tutorial/tutorial_5.png"
#define TUTORIAL_6 "sprites/tutorial/tutorial_6.png"

namespace cocos2d {
    namespace ui {
        class Button;
    };
};

class GSTutorial : public cocos2d::Layer {
public:
    static GSTutorial* create(cocos2d::Rect, std::string);
    static GSTutorial* create(cocos2d::Rect, cocos2d::Rect, std::string);

    bool initWithOneRect(cocos2d::Rect, std::string);
    bool initWithTwoRect(cocos2d::Rect, cocos2d::Rect, std::string);

    void setOkayEvent(std::function<void()>);
private:
    cocos2d::ui::Button* button;
    std::function<void()> call;
};

#endif // !__GS_TUTORIAL_H__