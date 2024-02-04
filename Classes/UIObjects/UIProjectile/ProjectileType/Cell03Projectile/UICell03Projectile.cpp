#include "UIObjects/uiobj.h"
#include "UICell03Projectile.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

/*
Create new instance of UICell03Projectile
*/
UICell03Projectile* UICell03Projectile::create() {
    UICell03Projectile *uiprojectile = new (std::nothrow) UICell03Projectile();
    if (uiprojectile && uiprojectile->initWithFile(CELL_03_PROJECTILE_FILENAME))
    {
        uiprojectile->autorelease();
        uiprojectile->setScaleY(0.75f);
        return uiprojectile;
    }
    CC_SAFE_DELETE(uiprojectile);
    return nullptr;
}

/*
Idle animate
*/
void UICell03Projectile::idleAnimate() {
    auto spin = RotateBy::create(0.5f, 360);
    this->runAction(RepeatForever::create(spin));
}

/*
Destroy animate
*/
void UICell03Projectile::destroyAnimate() {
    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/projectile_destroyed.mp3");

    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    for (unsigned int i = 1; i < 6; i++) {
        auto frame = SpriteFrame::create(CELL_03_DESTROY_FILENAME, Rect(i * 32, 0, 32, 32));
        frames.pushBack(frame);
    }
    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));
    auto remove = RemoveSelf::create();
    auto seq = Sequence::create(animate, remove, nullptr);
    this->runAction(seq);
}