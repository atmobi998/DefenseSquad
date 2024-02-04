#ifndef __UI_LOSE_LAYER_H__
#define __UI_LOSE_LAYER_H__

#include "cocos2d.h"

#define FLASH_FILENAME "sprites/objects/button/result_layer/flash_bg.jpg"
#define FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define LOSE_FILENAME "sprites/objects/button/result_layer/lose_noti.png"

#define TEXT_LOSE_FILENAME "sprites/objects/button/text_lose.png"
#define MAIN_MENU_BUTTON_FILENAME "sprites/objects/button/layer_button_mainmenu.png"
#define MAIN_MENU_BUTTON_CLICKED_FILENAME "sprites/objects/button/layer_button_mainmenu_clicked.png"
#define RESTART_BUTTON_FILENAME "sprites/objects/button/layer_button_restart.png"
#define RESTART_BUTTON_CLICKED_FILENAME "sprites/objects/button/layer_button_restart_clicked.png"

class LevelModel;

class UILoseLayer : public cocos2d::Layer {
public:
    static UILoseLayer* create(LevelModel*);
    bool init(LevelModel*);
protected:
    LevelModel* level;
};

#endif // !__UI_RESULT_LAYER_H__