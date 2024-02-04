#ifndef __GS_FLAG_H__
#define __GS_FLAG_H__

#include "cocos2d.h"
#define GS_FLAG_FILENAME "sprites/MapLayer/flag.png"

class GSFlag : public cocos2d::Sprite {
public:
    static GSFlag* create();
    void flutterAnimate();
};

#endif // !__GS_FLAG_H__