#ifndef __UI_PROGRESSOR_H__
#define __UI_PROGRESSOR_H__

#include "cocos2d.h"
#include <vector>
class WaveModel;

#define PROGRESSOR_POS_X Director::getInstance()->getVisibleSize().width - Director::getInstance()->getVisibleSize().height / 16 - 320.0f + Director::getInstance()->getVisibleOrigin().x
#define PROGRESSOR_POS_Y Director::getInstance()->getVisibleSize().height / 16 + Director::getInstance()->getVisibleOrigin().y

#define PROGRESSOR_FILENAME "sprites/InformationLayer/progressor.png"
#define PROGRESSOR_INSIDE_FILENAME "sprites/InformationLayer/progressor_inside.png"
#define PROGRESSOR_FILL_FILENAME "sprites/InformationLayer/progressor_fill.png"
#define PROGRESSOR_FLAG_FILENAME "sprites/InformationLayer/progressor_flag.png"

#define NOTIFICATION_POS_X Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x
#define NOTIFICATION_POS_Y Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y

#define NOTIFICATION_HEIGHT Director::getInstance()->getVisibleSize().height / 8

#define NOTIFICATION_LAYER_ZORDER 10

#define NOTIFICATION_HUGEWAVE_FILENAME "sprites/InformationLayer/huge_wave.png"
#define NOTIFICATION_HUGEWAVE_FINAL_FILENAME "sprites/InformationLayer/huge_wave_final.png"
#define NOTIFICATION_HUGEWAVE_JOKE_FILENAME "sprites/InformationLayer/huge_wave_final_joke.png"

class UIProgressor : public cocos2d::Node {
public:
    UIProgressor(std::vector<WaveModel>*);
    static UIProgressor* create(std::vector<WaveModel>*);
    void updateOnWave();
protected:
    std::vector<WaveModel>* waveList;
    unsigned int currentWave;
    unsigned int currentHugeWave;
    cocos2d::Sprite* fill;
    std::vector<cocos2d::Sprite*> flags;
};

#endif // !__UI_PROGRESSOR_H__