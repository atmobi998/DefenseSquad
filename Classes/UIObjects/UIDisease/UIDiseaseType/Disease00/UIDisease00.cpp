#include "UIObjects/uiobj.h"
#include "UIDisease00.h"
#include "Scenes/GameScene/GSDefine.h"
#include "UIDisease00Definitions.h"

/*
Create new instance of UIDisease00
*/
UIDisease00* UIDisease00::create() {
    UIDisease00 *uidisease = new (std::nothrow) UIDisease00();
    if (uidisease && uidisease->initWithFile(DISEASE_00_FILENAME))
    {
        uidisease->autorelease();
        return uidisease;
    }
    CC_SAFE_DELETE(uidisease);
    return nullptr;
}


void UIDisease00::walkAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_00_SHEETWALK, DISEASE_00_IMGWALK);
	
	const int numberSprite = 16;
	const int maxWord = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	char spriteFrameByName[maxWord] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 4; index++){
			sprintf(spriteFrameByName, "disease00walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 5; index <= 8; index++){
			sprintf(spriteFrameByName, "disease00walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 9; index <= 12; index++){
			sprintf(spriteFrameByName, "disease00walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 13; index <= 16; index++){
			sprintf(spriteFrameByName, "disease00walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
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

void UIDisease00::idleAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_00_SHEETIDLE, DISEASE_00_IMGIDLE);

	const int numberSprites = 16;
	const int maxWords = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprites);
	char spriteFrameByName[maxWords] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 4; index++) {
			sprintf(spriteFrameByName, "disease00idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 5; index <= 8; index++) {
			sprintf(spriteFrameByName, "disease00idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 9; index <= 12; index++) {

			sprintf(spriteFrameByName, "disease00idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 13; index <= 16; index++) {
			sprintf(spriteFrameByName, "disease00idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5f, 0.2f));
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

void UIDisease00::attackAnimate(Direction dir) {
	/*
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_00_SHEETATTACK, DISEASE_00_IMGATTACK);

	const int numberSprites = 24;
	const int maxWords = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprites);

	// chuỗi trung gian để đọc tên ảnh trong file format
	char spriteFrameByName[maxWords] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 6; index++) {
			sprintf(spriteFrameByName, "disease00attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 7; index <= 12; index++) {
			sprintf(spriteFrameByName, "disease00attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 13; index <= 18; index++) {

			sprintf(spriteFrameByName, "disease00attack%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 19; index <= 24; index++) {
			sprintf(spriteFrameByName, "disease00attack%d.png", index);
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
	// Chạy Acction animation với số lần lặp vô hạn.
	this->runAction(repeat);
	
	*/
	
	UIDisease::attackAnimate(dir);
	
}

void UIDisease00::hitAnimate(Direction dir) {
	UIDisease::hitAnimate(dir);
}

void UIDisease00::dieAnimate(Direction dir) {
	UIDisease::dieAnimate(dir);
}

