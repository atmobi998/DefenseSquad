#include "GSFlag.h"
USING_NS_CC;

/*
Create new object of GSFlag UI
*/
GSFlag* GSFlag::create() {
    GSFlag *sprite = new (std::nothrow) GSFlag;
    if (sprite && sprite->initWithFile(GS_FLAG_FILENAME, Rect(0, 0, 80, 80)))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

/*
Fluttering animation
*/
void GSFlag::flutterAnimate() {
    Vector<SpriteFrame*> frames;
    for (int i = 0; i < 5; i++) {
        auto frame = SpriteFrame::create(GS_FLAG_FILENAME, Rect(80 * i, 0, 80, 80));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8.0f);
    auto animate = Animate::create(animation);

    this->runAction(RepeatForever::create(animate));
}