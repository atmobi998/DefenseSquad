#ifndef __GS_BRICK_H__
#define __GS_BRICK_H__

#include "cocos2d.h"

class GSBrick : public cocos2d::Sprite {
public:
    static GSBrick* create();
    cocos2d::Sprite* createPiece(int);
    void putPiecesIntoPlace(bool, bool, bool, bool);
};

#endif // !__GS_BRICK_H__