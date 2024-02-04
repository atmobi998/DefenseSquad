#include "UIObjects/uiobj.h"
#include "UICell04.h"
#include "Scenes/GameScene/GSDefine.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
/*
Create a new instance of UICell00
*/
UICell04* UICell04::create() {
    UICell04 *uicell = new (std::nothrow) UICell04();
    if (uicell && uicell->initWithFile(CELL_04_FILENAME))
    {
        uicell->autorelease();
        return uicell;
    }
    CC_SAFE_DELETE(uicell);
    return nullptr;
}
void UICell04::addToScene(Scene* scene) {
	// this->setScale(0.75);
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}
void UICell04::idleAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);

	//this->stopActionByTag();

	const int numberSprite = 33;
	Vector<SpriteFrame*> animFrames;
	int size = Sprite::create(CELL_04_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite; i++) {
		animFrames.pushBack(SpriteFrame::create(CELL_04_FILENAME, Rect(size * i, 0, size, size)));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	Animate *animate = Animate::create(animation);
	
	//animate->setTag();

	this->setRotation3D(Vec3(0, 180.0f, 0));
	auto idle = RepeatForever::create(animate);

	idle->setTag(ANIM_BASE_TAG);

	this->runAction(idle);

	auto tintTo = TintTo::create(0.1f, Color3B::BLUE);
	auto tintTo_ = TintTo::create(0.1f, Color3B::WHITE);
	auto sequenceSprites = Sequence::create(tintTo, tintTo_, tintTo->clone(), tintTo_->clone(), nullptr);

	auto scale_ = ScaleBy::create(0.5f, 0.5f);
	auto rescale = ScaleBy::create(0.5f, 2.0f);
	auto seq2 = Sequence::create(scale_, rescale, nullptr);

	auto mySpawn = Spawn::createWithTwoActions(seq2, sequenceSprites);
	this->runAction(mySpawn);
}
void UICell04::effectAnimate() {
	for (int j = 0; j < 80; j++) {
	    auto after = Sprite::create(CELL_04_EFFECT_FILENAME, Rect(0.0f, 0.0f, 32.0f, 32.0f));
	    this->getParent()->addChild(after, PROJECTILE_LAYER_ZORDER);
		after->setGlobalZOrder(8.0f);
	    after->setPosition(this->getPosition());

		auto rotate = RepeatForever::create(RotateBy::create(1.0f, 360 * CCRANDOM_MINUS1_1()));
		rotate->setTag(3);
		after->runAction(rotate);

	    auto time = CCRANDOM_0_1() * 0.7f + 0.3f;
	    auto distance = CELL_WIDTH * (1.0f  + CCRANDOM_0_1()) * 0.8f;
	    auto jumpX = distance * CCRANDOM_MINUS1_1();
	    auto jumpY = (CCRANDOM_0_1() <= 0.5f ? -1 : 1) * sqrt(distance * distance - jumpX * jumpX);
	    auto jumpH = 40.0f + 20.0f * CCRANDOM_0_1();

	    auto jump = JumpBy::create(time + 0.25f, Vec2(jumpX, jumpY), jumpH, 1);
	    auto call = CallFuncN::create([](Node* node){
	        node->stopActionByTag(3);
	    });

		Vector<SpriteFrame*> frames;
		for (unsigned int i = 1; i < 6; i++) {
			auto frame = SpriteFrame::create(CELL_04_EFFECT_FILENAME, Rect(i * 32, 0, 32, 32));
			frames.pushBack(frame);
		}
	    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));

		auto remove = RemoveSelf::create();
		auto delay = DelayTime::create(time);

	    auto seq = Sequence::create(delay, call, animate, remove, nullptr);
	    after->runAction(seq);
		after->runAction(jump);

	    after->setScale(0.15f + 1.2f * CCRANDOM_0_1());
	}
}

void UICell04::dieAnimate() {
	this->removeFromParent();
	 SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/freeze.mp3");
}

