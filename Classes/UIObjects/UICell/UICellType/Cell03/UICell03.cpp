#include "UIObjects/uiobj.h"
#include "UICell03.h"

/*
Create a new instance of UICell00
*/
UICell03* UICell03::create() {
    UICell03 *uicell = new (std::nothrow) UICell03();
    if (uicell && uicell->initWithFile(CELL_03_FILENAME))
    {
        uicell->autorelease();
        return uicell;
    }
    CC_SAFE_DELETE(uicell);
    return nullptr;
}
void UICell03::addToScene(cocos2d::Scene* scene) {
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}
void UICell03::idleAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);

	//this->stopActionByTag();

	const int numberSprite = 20;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	int size = cocos2d::Sprite::create(CELL_03_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite; i++) {
		animFrames.pushBack(cocos2d::SpriteFrame::create(CELL_03_FILENAME, cocos2d::Rect(size * i, 0, size, size)));
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);

	//animate->setTag();

	this->setRotation3D(cocos2d::Vec3(0, 180.0f, 0));
	auto idle = cocos2d::RepeatForever::create(animate);
	idle->setTag(ANIM_BASE_TAG);
	this->runAction(idle);
}
void UICell03::attackAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);

	const int numberSprite = 20;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	int size = cocos2d::Sprite::create(CELL_03_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite; i++) {
		animFrames.pushBack(cocos2d::SpriteFrame::create(CELL_03_FILENAME, cocos2d::Rect(size * i, 0, size, size)));
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.025f);
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);

	//animate->setTag();

	this->setRotation3D(cocos2d::Vec3(0, 180.0f, 0));
	auto attack = cocos2d::RepeatForever::create(animate);
	attack->setTag(ANIM_BASE_TAG);
	this->runAction(attack);
}


void UICell03::hitAnimate() {

	auto tintTo = cocos2d::TintTo::create(0.1, cocos2d::Color3B::RED);
	auto tintTo_ = cocos2d::TintTo::create(0.1, cocos2d::Color3B::WHITE);
	auto sequenceSprites = cocos2d::Sequence::create(tintTo, tintTo_, nullptr);
	this->runAction(sequenceSprites);
}
void UICell03::dieAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);

	//this->stopActionByTag();

	auto fadeOut = cocos2d::FadeOut::create(1.0f);
	auto remove = cocos2d::RemoveSelf::create();
	auto sequence = cocos2d::Sequence::create(fadeOut, remove, nullptr);
	this->runAction(sequence);
}