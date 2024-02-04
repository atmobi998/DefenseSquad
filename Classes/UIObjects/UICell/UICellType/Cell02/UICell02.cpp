#include "UIObjects/uiobj.h"
#include "UICell02.h"

/*
Create a new instance of UICell00
*/
UICell02* UICell02::create() {
    UICell02 *uicell = new (std::nothrow) UICell02();
    if (uicell && uicell->initWithFile(CELL_02_FILENAME))
    {
        uicell->autorelease();
        return uicell;
    }
    CC_SAFE_DELETE(uicell);
    return nullptr;
}
void UICell02::addToScene(cocos2d::Scene* scene) {
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}
void UICell02::idleAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	
	//this->stopActionByTag();

	const int numberSprite = 18;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	int size = cocos2d::Sprite::create(CELL_02_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite; i++) {
		animFrames.pushBack(cocos2d::SpriteFrame::create(CELL_02_FILENAME, cocos2d::Rect(size * i, 0, size, size)));
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);

	//animate->setTag();

	this->setRotation3D(cocos2d::Vec3(0, 180.0f, 0));
	auto idle = cocos2d::RepeatForever::create(animate);
	idle->setTag(ANIM_BASE_TAG);

	this->runAction(idle);
}

void UICell02::hitAnimate() {

	auto tintTo = cocos2d::TintTo::create(0.1, cocos2d::Color3B::RED);
	auto tintTo_ = cocos2d::TintTo::create(0.1, cocos2d::Color3B::WHITE);
	auto sequenceSprites = cocos2d::Sequence::create(tintTo, tintTo_, nullptr);
	this->runAction(sequenceSprites);

}
void UICell02::dieAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	
	//this->stopActionByTag();

	auto fadeOut = cocos2d::FadeOut::create(1.0f);
	auto remove = cocos2d::RemoveSelf::create();
	auto sequence = cocos2d::Sequence::create(fadeOut, remove, nullptr);
	this->runAction(sequence);
}