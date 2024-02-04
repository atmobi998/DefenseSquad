#include "UIObjects/uiobj.h"
#include "UICell06.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

/*
Create a new instance of UICell00
*/
UICell06* UICell06::create() {
	UICell06 *uicell = new (std::nothrow) UICell06();
	if (uicell && uicell->initWithFile(CELL_06_FILENAME, Rect(4 * 46.0f, 0.0f, 46.0f, 46.0f)))
	{
		uicell->autorelease();
		return uicell;
	}
	CC_SAFE_DELETE(uicell);
	return nullptr;
}
void UICell06::addToScene(Scene* scene) {
	//this->setScale(0.75);
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}
void UICell06::idleAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);

	//this->stopActionByTag();

	// const int numberSprite = 65;
	// Vector<SpriteFrame*> animFrames;
	// int size = Sprite::create(CELL_06_FILENAME)->getContentSize().height;
	// animFrames.reserve(numberSprite);
	// for (int i = 0; i < numberSprite; i++) {
	// 	animFrames.pushBack(SpriteFrame::create(CELL_06_FILENAME, Rect(size * i, 0, size, size)));
	// }
	// Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	// Animate *animate = Animate::create(animation);

	//animate->setTag();

	this->setRotation3D(Vec3(0, 180.0f, 0));
	// auto idle = RepeatForever::create(animate);

	// idle->setTag(ANIM_BASE_TAG);

	// this->runAction(idle);

	// Scale and explosion
	auto delay1 = DelayTime::create(0.3f);
	auto delay2 = DelayTime::create(0.3f);
	auto scaleBy2 = ScaleTo::create(0.0f, this->getScale() * 1.5f);
	auto scaleBy3 = ScaleTo::create(0.0f, this->getScale() * 2.25f);
	auto changeRed = TintTo::create(0.0f, Color3B::RED);
	auto scaleSeq = Sequence::create(delay1, scaleBy2, delay2, scaleBy3, changeRed, nullptr);
	this->runAction(scaleSeq);

	auto fluctuateRange = 10.0f;
	auto fluct1 = MoveBy::create(0.025f, Vec2(0.0f - fluctuateRange, 0.0f));
	auto fluct2 = MoveBy::create(0.05f, Vec2(2 * fluctuateRange, 0.0f));
	auto fluct3 = MoveBy::create(0.025f, Vec2(0.0f - fluctuateRange, 0.0f));
	auto fluct4 = MoveBy::create(0.025f, Vec2(0.0f - fluctuateRange / 2, 0.0f));
	auto fluct5 = MoveBy::create(0.05f, Vec2(fluctuateRange, 0.0f));
	auto fluct6 = MoveBy::create(0.025f, Vec2(0.0f - fluctuateRange / 2, 0.0f));
	auto fluct7 = MoveBy::create(0.025f, Vec2(0.0f - fluctuateRange / 4, 0.0f));
	auto fluct8 = MoveBy::create(0.025f, Vec2(fluctuateRange / 4, 0.0f));
	auto fluct9 = DelayTime::create(0.05f);
	auto fluctMonoSeq = Sequence::create(fluct1, fluct2, fluct3, fluct4, fluct5, fluct6, fluct7, fluct8, fluct9, nullptr);
	auto fluctSeq = RepeatForever::create(fluctMonoSeq);
	this->runAction(fluctSeq);
}

void UICell06::effectAnimate() {
	for (int j = 0; j < 80; j++) {
	    auto after = Sprite::create(CELL_06_EFFECT_FILENAME, Rect(0.0f, 0.0f, 64.0f, 64.0f));
	    this->getParent()->addChild(after, PROJECTILE_LAYER_ZORDER);
		after->setGlobalZOrder(8.0f);
	    
	    auto distance = CCRANDOM_0_1() * CELL_WIDTH * 1.8f;
	    auto jumpX = distance * CCRANDOM_MINUS1_1();
	    auto jumpY = (CCRANDOM_0_1() <= 0.5f ? -1 : 1) * sqrt(distance * distance - jumpX * jumpX);

		after->setPosition(this->getPosition() + Vec2(jumpX, jumpY));
		after->setOpacity(0);

		Vector<SpriteFrame*> frames;
		for (unsigned int i = 0; i < 8; i++) {
			auto frame = SpriteFrame::create(CELL_06_EFFECT_FILENAME, Rect(i * 64.0f, 0.0f, 64.0f, 64.0f));
			frames.pushBack(frame);
		}
	    auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.075f));

		auto remove = RemoveSelf::create();
		auto time = CCRANDOM_0_1() * 0.3f;
		auto delay = DelayTime::create(time);

		auto appear = FadeTo::create(0.0f, 255);

	    auto seq = Sequence::create(delay, appear, animate, remove, nullptr);
	    after->runAction(seq);

	    after->setScale(0.15f + 1.5f * CCRANDOM_0_1() * (CELL_WIDTH * 2.0f - distance) / (CELL_WIDTH));
	}
}

void UICell06::dieAnimate() {
	SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/explosion.mp3");
	removeFromParent();
}
