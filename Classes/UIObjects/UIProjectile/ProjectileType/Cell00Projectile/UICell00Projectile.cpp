#include "UIObjects/uiobj.h"
#include "UICell00Projectile.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

/*
Create new instance of UICell00Projectile
*/
UICell00Projectile* UICell00Projectile::create() {
    UICell00Projectile *uiprojectile = new (std::nothrow) UICell00Projectile();
    if (uiprojectile && uiprojectile->initWithFile(CELL_00_PROJECTILE_FILENAME))
    {
        uiprojectile->autorelease();
        return uiprojectile;
    }
    CC_SAFE_DELETE(uiprojectile);
    return nullptr;
}

/*
Idle animate
*/
void UICell00Projectile::idleAnimate() {
    auto spin = RotateBy::create(0.25f, 360);
    this->runAction(RepeatForever::create(spin));
}

/*
Destroy animate
*/
void UICell00Projectile::destroyAnimate() {
    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/projectile_destroyed.mp3");

    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    for (unsigned int i = 1; i < 6; i++) {
        auto frame = SpriteFrame::create(CELL_00_DESTROY_FILENAME, Rect(i * 32, 0, 32, 32));
        frames.pushBack(frame);
    }
    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));
    auto remove = RemoveSelf::create();
    auto seq = Sequence::create(animate, remove, nullptr);
    this->runAction(seq);
}