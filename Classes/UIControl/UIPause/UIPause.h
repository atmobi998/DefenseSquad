#ifndef __UI_PAUSE_H__
#define __UI_PAUSE_H__

#include "../UIControl.h"
#define PAUSE_BUTTON_FILENAME "sprites/objects/button/pause.png"
#define PAUSE_BUTTON_CLICKED_FILENAME "sprites/objects/button/pause_clicked.png"
#define PAUSE_BUTTON_POS_X Director::getInstance()->getSafeAreaRect().getMaxX() - 7.5f - 22.5f * 1.2f + Director::getInstance()->getVisibleOrigin().x
#define PAUSE_BUTTON_POS_Y Director::getInstance()->getVisibleSize().height - 7.5f - 22.5f * 1.2f + Director::getInstance()->getVisibleOrigin().y

class LevelModel;

class UIPause : public UIControl {
public:
    static UIPause* create(LevelModel*);

private:
	virtual void onTouch();
    LevelModel* level;
};

#endif // !__UI_PAUSE_H__