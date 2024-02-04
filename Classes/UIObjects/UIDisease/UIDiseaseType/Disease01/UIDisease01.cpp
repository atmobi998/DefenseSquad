#include "UIObjects/uiobj.h"
#include "UIDisease01.h"
#include "Scenes/GameScene/GSDefine.h"
#include "UIDisease01Definitions.h"

/*
Create new instance of UIDisease01
*/
UIDisease01* UIDisease01::create() {
	UIDisease01 *uidisease = new (std::nothrow) UIDisease01();
    if (uidisease && uidisease->initWithFile(DISEASE_01_FILENAME))
    {
        uidisease->autorelease();
        return uidisease;
    }
    CC_SAFE_DELETE(uidisease);
    return nullptr;
}


void UIDisease01::walkAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_01_SHEETWALK, DISEASE_01_IMGWALK);
	
	const int numberSprite = 16;
	const int maxWord = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	char spriteFrameByName[maxWord] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 4; index++){
			sprintf(spriteFrameByName, "disease01walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 5; index <= 8; index++){
			sprintf(spriteFrameByName, "disease01walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 9; index <= 12; index++){
			sprintf(spriteFrameByName, "disease01walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 13; index <= 16; index++){
			sprintf(spriteFrameByName, "disease01walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	default:
		break;
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);
	repeat->setTag(ANIM_BASE);
	this->runAction(repeat);
}

void UIDisease01::idleAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_01_SHEETIDLE, DISEASE_01_IMGIDLE);

	const int numberSprites = 8;
	const int maxWords = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprites);

	char spriteFrameByName[maxWords] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 2; index++) {
			sprintf(spriteFrameByName, "disease01idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 3; index <= 4; index++) {
			sprintf(spriteFrameByName, "disease01idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 5; index <= 6; index++) {
			sprintf(spriteFrameByName, "disease01idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 7; index <= 8; index++) {
			sprintf(spriteFrameByName, "disease01idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.375));
			animFrames.pushBack(frame);
		}
		break;
	default:
		break;
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);
	repeat->setTag(ANIM_BASE);
	this->runAction(repeat);
}

void UIDisease01::attackAnimate(Direction dir) {
	
	UIDisease::attackAnimate(dir);

	/*
	//this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_01_SHEETATTACK, DISEASE_01_IMGATTACK);

	const int numberSprites = 20;
	const int maxWords = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprites);

	char spriteFrameByName[maxWords] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 5; index++) {
			sprintf(spriteFrameByName, "disease01attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 6; index <= 10; index++) {
			sprintf(spriteFrameByName, "disease01attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 11; index <= 15; index++) {

			sprintf(spriteFrameByName, "disease01attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 16; index <= 20; index++) {
			sprintf(spriteFrameByName, "disease01attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	default:
		break;
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);
	repeat->setTag(ANIM_BASE);
	this->runAction(repeat);
	*/
}

void UIDisease01::hitAnimate(Direction dir) {

	UIDisease::hitAnimate(dir);

}

void UIDisease01::dieAnimate(Direction dir) {
	UIDisease::dieAnimate(dir);
}

