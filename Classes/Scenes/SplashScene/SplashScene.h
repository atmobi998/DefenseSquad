#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

#define SPLASH_FILENAME "sprites/Background/splash_info.png"

class SplashScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* create();
    virtual bool init();
};

#endif // !__SPLASH_SCENE_H__
