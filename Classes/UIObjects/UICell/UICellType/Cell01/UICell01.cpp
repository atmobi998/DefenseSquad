#include "UIObjects/uiobj.h"
#include "UICell01.h"
using namespace std;
USING_NS_CC;
/*
Create a new instance of UICell00
*/
UICell01* UICell01::create() {
    UICell01 *uicell = new (std::nothrow) UICell01();
    if (uicell && uicell->initWithFile(CELL_01_FILENAME))
    {
        uicell->autorelease();
        return uicell;
    }
    CC_SAFE_DELETE(uicell);
    return nullptr;
}
void UICell01::addToScene(Scene* scene) {
	scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
	this->idleAnimate();
}
void UICell01::idleAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	const int numberSprite = 33;
	Vector<SpriteFrame*> animFrames;
	int size = Sprite::create(CELL_01_FILENAME)->getContentSize().height;
	animFrames.reserve(numberSprite);
	for (int i = 0; i < numberSprite; i++) {
		animFrames.pushBack(SpriteFrame::create(CELL_01_FILENAME, Rect(size * i, 0, size, size)));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	Animate *animate = Animate::create(animation);
	this->setRotation3D(Vec3(0, 180.0f, 0));
	auto idle = RepeatForever::create(animate);
	idle->setTag(ANIM_BASE_TAG);

	this->runAction(idle);
}
void UICell01::effectAnimate() {
	
}
void UICell01::effectAnimate(function<void()> call) {
	//auto rotate = RotateBy::create(0.5f, -360.0f);
	auto move = JumpBy::create(0.75f, Vec2(0.0f, 0.0f), CELL_WIDTH, 1);
	auto changeOrange = TintTo::create(0.0f, Color3B(255, 201, 15));
	auto changeWhite = TintTo::create(0.0f, Color3B::WHITE);
	auto seq = Sequence::create(changeOrange, move, changeWhite, nullptr);

	auto moveShadow = JumpBy::create(0.75f, Vec2(0.0f, 0.0f), 0.0f - (CELL_WIDTH) / this->getScale(), 1);

	auto delay = DelayTime::create(0.375f);
	auto func = CallFunc::create(call);
	auto seq2 = Sequence::create(delay, func, nullptr);

	//this->runAction(rotate);
	this->runAction(seq);
	this->runAction(seq2);
	shadow->runAction(moveShadow);
}
void UICell01::hitAnimate() {
	auto tintTo = TintTo::create(0.1, Color3B::RED);
	auto tintTo_ = TintTo::create(0.1, Color3B::WHITE);
	auto sequenceSprites = Sequence::create(tintTo, tintTo_, nullptr);
	this->runAction(sequenceSprites);
}
void UICell01::dieAnimate() {
	this->stopAllActionsByTag(ANIM_BASE_TAG);
	auto fadeOut = FadeOut::create(1.0f);
	auto remove = RemoveSelf::create();
	auto sequence = Sequence::create(fadeOut, remove, nullptr);
	this->runAction(sequence);
}