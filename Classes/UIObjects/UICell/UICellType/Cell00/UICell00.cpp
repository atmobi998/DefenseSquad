#include "UIObjects/uiobj.h"
#include "UICell00.h"


/*
Create a new instance of UICell00
*/
UICell00* UICell00::create() {
    UICell00 *uicell = new (std::nothrow) UICell00();
    if (uicell && uicell->initWithFile(CELL_00_FILENAME))
    {
        uicell->autorelease();
        return uicell;
    }
	
    CC_SAFE_DELETE(uicell);
    return nullptr;
}
void UICell00::addToScene(cocos2d::Scene* scene) {
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}

void UICell00::idleAnimate() {

	const int numberSprite = 29;
	//this->stopAllActions();
	
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	int size = cocos2d::Sprite::create(CELL_00_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite ; i++) {
		auto Frame = cocos2d::SpriteFrame::create(CELL_00_FILENAME, cocos2d::Rect(size * i, 0, size, size));
		animFrames.pushBack(Frame);
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames,0.05f);	
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);
		
	this->setRotation3D(cocos2d::Vec3(0, 180.0f, 0));
	auto idle = cocos2d::RepeatForever::create(animate);
	idle->setTag(ANIM_BASE_TAG);

	this->runAction(idle);
}

void UICell00::attackAnimate() {
	//this->stopAllActions();
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	//this->stopActionByTag();
	
	const int numberSprite = 29;

	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);
	int size = cocos2d::Sprite::create(CELL_00_FILENAME)->getContentSize().height;
	for (int i = 0; i < numberSprite ; i++) {
		animFrames.pushBack(cocos2d::SpriteFrame::create(CELL_00_FILENAME, cocos2d::Rect(size * i, 0, size, size)));
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames,0.025f);
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);
	
	this->setRotation3D(cocos2d::Vec3(0, 180.0f, 0));

	auto attack = cocos2d::RepeatForever::create(animate);
	attack->setTag(ANIM_BASE_TAG);	

	this->runAction(attack);
	
	
}
void UICell00::hitAnimate() {

	auto tintTo = cocos2d::TintTo::create(0.1, cocos2d::Color3B::RED);
	auto tintTo_ = cocos2d::TintTo::create(0.1, cocos2d::Color3B::WHITE);
	auto sequenceSprites = cocos2d::Sequence::create(tintTo, tintTo_, nullptr);
	this->runAction(sequenceSprites);
}

void UICell00::dieAnimate() {

	//this->stopActionByTag();

	this->stopAllActionsByTag(ANIM_BASE_TAG);

	auto fadeOut = cocos2d::FadeOut::create(1.0f);
	auto remove = cocos2d::RemoveSelf::create();
	auto sequence = cocos2d::Sequence::create(fadeOut, remove, nullptr);
	this->runAction(sequence);
}
