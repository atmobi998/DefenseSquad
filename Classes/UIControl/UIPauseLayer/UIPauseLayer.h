#ifndef __UI_PAUSE_LAYER_H__
#define __UI_PAUSE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define PAUSE_LAYER_FORE_FILENAME "sprites/objects/button/layer_fore.png"
#define PAUSE_LAYER_FILENAME "sprites/objects/button/layer.png"
#define PAUSE_LAYER_RESUME_FILENAME "sprites/objects/button/layer_button_resume.png"
#define PAUSE_LAYER_RESUME_CLICKED_FILENAME "sprites/objects/button/layer_button_resume_clicked.png"
#define PAUSE_LAYER_RESTART_FILENAME "sprites/objects/button/layer_button_restart.png"
#define PAUSE_LAYER_RESTART_CLICKED_FILENAME "sprites/objects/button/layer_button_restart_clicked.png"
#define PAUSE_LAYER_MAINMENU_FILENAME "sprites/objects/button/layer_button_mainmenu.png"
#define PAUSE_LAYER_MAINMENU_CLICKED_FILENAME "sprites/objects/button/layer_button_mainmenu_clicked.png"
#define PAUSE_LAYER_MUSIC_FILENAME "sprites/objects/button/music.png"
#define PAUSE_LAYER_EFFECT_FILENAME "sprites/objects/button/sound_effect.png"
#define PAUSE_LAYER_SLIDER_FILENAME "sprites/objects/button/slider.png"
#define PAUSE_LAYER_SLIDER_BASE_FILENAME "sprites/objects/button/slider_bar.png"

class LevelModel;

class UIPauseLayer : public cocos2d::Layer {
public:
    static UIPauseLayer* create(LevelModel*);
    void init(LevelModel*);
private:
    LevelModel* level;
    cocos2d::Sprite* music_slider;
    cocos2d::Sprite* effect_slider;
};

#endif // !__UI_PAUSE_LAYER_H__