#ifndef __UI_WIN_LAYER_H__
#define __UI_WIN_LAYER_H__

#include "cocos2d.h"
#include <functional>

#define FLASH_FILENAME "sprites/objects/button/result_layer/flash_bg.jpg"
#define FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define VICTORY_FILENAME "sprites/objects/button/result_layer/victory_noti.png"
#define STAR_FILENAME "sprites/objects/button/result_layer/star.png"

#define TEXT_WIN_FILENAME "sprites/objects/button/text_win.png"
#define TEXT_COMPLETE_FILENAME "sprites/objects/button/text_complete.png"
#define MAIN_MENU_BUTTON_FILENAME "sprites/objects/button/layer_button_mainmenu.png"
#define MAIN_MENU_BUTTON_CLICKED_FILENAME "sprites/objects/button/layer_button_mainmenu_clicked.png"
#define NEXT_LEVEL_BUTTON_FILENAME "sprites/objects/button/layer_button_nextlevel.png"
#define NEXT_LEVEL_BUTTON_CLICKED_FILENAME "sprites/objects/button/layer_button_nextlevel_clicked.png"

class LevelModel;
class UIRewardLayer;

class UIWinLayer : public cocos2d::Layer {
public:
    static UIWinLayer* create(LevelModel*);
    bool init(LevelModel*);
protected:
    LevelModel* level;
    UIRewardLayer* rewardLayer;
    std::function<void()> callMessage;
};

#endif // !__UI_RESULT_LAYER_H__