#include "UIObjects/uiobj.h"
#include "UICell05Projectile.h"
#include <cmath>
#include <functional>
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

/*
Create new instance of UICell05Projectile
*/
UICell05Projectile* UICell05Projectile::create() {
    UICell05Projectile *uiprojectile = new (std::nothrow) UICell05Projectile();
    if (uiprojectile && uiprojectile->initWithFile(CELL_05_PROJECTILE_FILENAME, Rect(0.0f, 0.0f, 32.0f, 32.0f)))
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
void UICell05Projectile::idleAnimate() {
    Vector<SpriteFrame*> frames;
    for (unsigned int i = 0; i < 6; i++) {
        auto frame = SpriteFrame::create(CELL_05_PROJECTILE_FILENAME, Rect(i * 32, 0, 32, 32));
        frames.pushBack(frame);
    }
    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));
    this->runAction(RepeatForever::create(animate));
}

/*
Destroy animate
*/
void UICell05Projectile::destroyAnimate() {
    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/ember.mp3");

    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    for (unsigned int i = 0; i < 6; i++) {
        auto frame = SpriteFrame::create(CELL_05_DESTROY_FILENAME, Rect(i * 32, 0, 32, 32));
        frames.pushBack(frame);
    }
    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));
    auto remove = RemoveSelf::create();

    // Create aftermath

    for (int j = 0; j < 60; j++) {
        auto after = Sprite::create(CELL_05_AFTERMATH_FILENAME, Rect(0.0f, 0.0f, 32.0f, 32.0f));
        this->getParent()->addChild(after, PROJECTILE_LAYER_ZORDER);
        after->setPosition(this->getPosition());
        after->setGlobalZOrder(8.0f);
        Vector<SpriteFrame*> framesIn;
        for (unsigned int i = 0; i < 6; i++) {
            auto frame = SpriteFrame::create(CELL_05_AFTERMATH_FILENAME, Rect(i * 32, 0, 32, 32));
            framesIn.pushBack(frame);
        }
        auto animateIn = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(framesIn, 0.05f)));
        animateIn->setTag(3);
        after->runAction(animateIn);

        auto time = CCRANDOM_0_1() * 0.35f + 0.15f;
        auto distance = CELL_WIDTH * 2.0f / 3 * (1 + CCRANDOM_0_1());
        auto jumpX = distance * CCRANDOM_MINUS1_1();
        auto jumpY = (CCRANDOM_0_1() <= 0.5f ? -1 : 1) * sqrt(distance * distance - jumpX * jumpX);
        auto jumpH = 20.0f + 10.0f * CCRANDOM_0_1();

        auto jump = JumpBy::create(time, Vec2(jumpX, jumpY), jumpH, 1);
        auto call = CallFuncN::create([](Node* node){
            node->stopActionByTag(3);
        });

        auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.025f));

        auto seq = Sequence::create(jump, call, animate, remove, nullptr);
        after->runAction(seq);

        after->setScale(0.15f + 1.05f * CCRANDOM_0_1());
    }

    auto seq = Sequence::create(animate, remove, nullptr);
    this->runAction(seq);
}