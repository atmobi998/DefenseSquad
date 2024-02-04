#include "UIObjects/uiobj.h"
#include "UIDisease06.h"
#include "Scenes/GameScene/GSDefine.h"
#include "UIDisease06Definitions.h"
#include <cmath>
#include "SimpleAudioEngine.h"
using namespace std;
using namespace CocosDenshion;

/*
Create new instance of UIDisease06
*/
UIDisease06* UIDisease06::create() {
	UIDisease06 *uidisease = new (std::nothrow) UIDisease06();
    if (uidisease && uidisease->initWithFile(DISEASE_06_FILENAME))
    {
		uidisease->thirdHPCount = 1;
        uidisease->autorelease();
        return uidisease;
    }
    CC_SAFE_DELETE(uidisease);
    return nullptr;
}

void UIDisease06::addToScene(Scene* scene) {
	UIDisease::addToScene(scene);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/GameScene/Boss/boss_appear.mp3", true);
}

void UIDisease06::walkAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_06_SHEETWALK, DISEASE_06_IMGWALK);
	
	const int numberSprite = 16;
	const int maxWord = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	char spriteFrameByName[maxWord] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 4; index++){
			sprintf(spriteFrameByName, "disease06walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 5; index <= 8; index++){
			sprintf(spriteFrameByName, "disease06walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 9; index <= 12; index++){
			sprintf(spriteFrameByName, "disease06walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 13; index <= 16; index++){
			sprintf(spriteFrameByName, "disease06walk%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
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

void UIDisease06::idleAnimate(Direction dir) {
	this->stopAllActionsByTag(ANIM_BASE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DISEASE_06_SHEETIDLE, DISEASE_06_IMGIDLE);

	const int numberSprites = 8;
	const int maxWords = 50;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprites);

	char spriteFrameByName[maxWords] = { 0 };
	switch (dir) {
	case DOWN:
		for (int index = 1; index <= 2; index++) {
			sprintf(spriteFrameByName, "disease06idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case LEFT:
		for (int index = 3; index <= 4; index++) {
			sprintf(spriteFrameByName, "disease06idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case RIGHT:
		for (int index = 5; index <= 6; index++) {
			sprintf(spriteFrameByName, "disease06idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
			animFrames.pushBack(frame);
		}
		break;
	case UP:
		for (int index = 7; index <= 8; index++) {
			sprintf(spriteFrameByName, "disease06idle%d.png", index);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			frame->setAnchorPoint(Point(0.5, 0.25));
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

void UIDisease06::attackAnimate(Direction dir) {

	if (dir == DOWN || dir == LEFT || dir == RIGHT || dir == UP) {
		auto jumpto = JumpTo::create(0.5, Vec2(this->getPositionX(), this->getPositionY() + SIZE_OF_SQUARE), 100, 1);
		auto jumpback = JumpTo::create(0.5, Vec2(this->getPositionX(), this->getPositionY()), 100, 1);
		//auto rotate = RotateBy::create(1.0f, Vec3(360.0f,0,0));
		auto scalef = ScaleBy::create(0.2, 2);
		auto scaleb = ScaleBy::create(0.2, 0.5);
		auto attackseq = Sequence::create(jumpto, scalef, jumpback, DelayTime::create(1), scaleb, nullptr);

		auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
		//auto movetocamera = MoveBy::create(0.5, Vec2(0, 10));
		//auto movebackcamera = MoveBy::create(0.5, Vec2(0, -10));
		//auto seqcamera = Sequence::create(movetocamera, movebackcamera, nullptr);
		auto scalecamf = ScaleBy::create(0.5, 2);
		auto scalecamb = ScaleBy::create(0.5, 0.5);
		//auto tintTo = TintTo::create(0.5, cocos2d::Color3B::RED);
		//auto tintTo_ = TintTo::create(0.5, cocos2d::Color3B::WHITE);
		//auto spawn = Spawn::createWithTwoActions(scalecamf, tintTo);
		//auto spawn1 = Spawn::createWithTwoActions(scalecamb, tintTo_);
		auto seqcamera = Sequence::create(scalecamf, scalecamb, nullptr);
		//camera->runAction(seqcamera);
		//camera->setPosition3D(Vec3(0, 100, 300));
		this->getParent()->runAction(seqcamera);
		this->runAction(attackseq);
	}
}

void UIDisease06::attackAnimateWithSync(Direction dir, function<void()> callBack) {
	auto jump = JumpBy::create(0.5, Vec2(0.0f, 0.0f), SIZE_OF_SQUARE, 1);
	auto changeZOrder = CallFuncN::create([](Node* node){
		node->setLocalZOrder(DISEASE_LAYER_ZORDER);
	});
	this->setLocalZOrder(6);
	auto seq = Sequence::create(jump, changeZOrder, nullptr);
	this->runAction(seq);

	auto shadowDeJump = JumpBy::create(0.5, Vec2(0.0f, 0.0f), 0.0f - SIZE_OF_SQUARE / this->getScale(), 1);
	this->shadow->runAction(shadowDeJump);

	function<function<void()>()> callScene = [this]() -> function<void()> {
		return [&](){
			SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/earthquake.mp3");

			// Make the camera fluctuate
			Vector<FiniteTimeAction*> fluct;
			auto amplifier = CELL_WIDTH / 2;
			for (int i = 0; i < 32; i++, amplifier /= 1.25f) {
				auto fluctLeft = MoveBy::create(0.03125f, Vec2((i % 2 == 0 ? 1 : -1) * amplifier, 0.0f));
				auto fluctRight = MoveBy::create(0.03125f, Vec2((i % 2 == 0 ? -1 : 1) * amplifier, 0.0f));
				fluct.pushBack(fluctLeft);
				fluct.pushBack(fluctRight);
			}
			auto camFluctSeq = Sequence::create(fluct);

			// Make the camera flash
			auto flash = CallFuncN::create([](Node* node){
				auto flashing = Sprite::create(BACKGROUND_FLASH_FILENAME);
				flashing->setOpacity(0);
				node->addChild(flashing, 7);
				flashing->setPosition(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, 
									Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y);
				auto flashIn = FadeTo::create(0.1f, 255);
				auto flashOut = FadeTo::create(0.1f, 0);
				auto remove = RemoveSelf::create();
				auto flashSeq = Sequence::create(flashIn, flashOut, remove, nullptr);
				flashing->runAction(flashSeq);
			});

			this->getParent()->runAction(camFluctSeq);
			this->getParent()->runAction(flash);
		};
	};
	
	auto delay2 = DelayTime::create(0.5f);
	auto sceneSeq = Sequence::create(delay2, CallFunc::create(callScene()), nullptr);
	this->runAction(sceneSeq);

	// Make the ground go wild
	auto wild = CallFuncN::create([](Node* node){
		for (int j = 0; j < 50; j++) {
			auto ground = Sprite::create(DISEASE_06_EFFECT, Rect(0.0f, 0.0f, 32.0f, 32.0f));
			ground->setOpacity(0);
			ground->setScale(1.0f + 0.75f * CCRANDOM_0_1());

			auto delay = DelayTime::create(0.25f * CCRANDOM_0_1());
			auto appear = FadeTo::create(0.0f, 255);

			Vector<SpriteFrame*> frames;
			for (unsigned int i = 0; i < 8; i++) {
				auto frame = SpriteFrame::create(DISEASE_06_EFFECT, Rect(i * 32.0f, 0.0f, 32.0f, 32.0f));
				frames.pushBack(frame);
			}
			auto animate = Repeat::create(Animate::create(Animation::createWithSpriteFrames(frames, 0.0125f)), 3u);
			auto remove = RemoveSelf::create();

			auto seq = Sequence::create(delay, appear, animate, remove, nullptr);

			auto radius = (0.5f + 1.0f * CCRANDOM_0_1()) * CELL_WIDTH;
			auto vecY = (-1.0f + CCRANDOM_0_1() * 1.866f) * radius;
			auto vecX = (CCRANDOM_0_1() <= 0.5f ? 1 : -1) * sqrt(radius * radius - vecY * vecY);
			node->getParent()->addChild(ground, 6);
			ground->setGlobalZOrder(8.0f);
			ground->setPosition(node->getPosition() + Vec2(vecX, vecY));
			ground->runAction(seq);
		}
	});
	auto delay3 = DelayTime::create(0.5f);
	auto camWildSeq = Sequence::create(delay3, wild, nullptr);
	this->runAction(camWildSeq);

	// Callback in earthquake
	auto delay4 = DelayTime::create(0.5f);
	auto call = CallFunc::create(callBack);
	auto callSeq = Sequence::create(delay4, call, nullptr);
	this->runAction(callSeq);
}

void UIDisease06::hitAnimate(Direction dir) {
	UIDisease::hitAnimate(dir);

}

void UIDisease06::dieAnimate(Direction dir) {
	UIDisease::dieAnimate(dir);
}

void UIDisease06::thirdHPAnimate(float percent) {
	if (percent * 3 > thirdHPCount) {
		thirdHPCount += 1;

		auto bandage = Sprite::create(DISEASE_06_BANDAGE);
		this->addChild(bandage);
		bandage->setScale(0.9f + CCRANDOM_0_1() * 0.4f);
		bandage->setRotation(360 * CCRANDOM_0_1());
		bandage->setGlobalZOrder(8.0f);
		bandage->setPosition(32.0f + 15.0f * CCRANDOM_MINUS1_1(), 32.0f + 15.0f * CCRANDOM_MINUS1_1());

		auto scaleLess = ScaleBy::create(0.0f, 0.8f);
		auto delay1 = DelayTime::create(0.75f);
		auto scaleMore = ScaleBy::create(0.0f, 1.25f);
		auto delay2 = DelayTime::create(0.75f);
		auto seq = Sequence::create(scaleLess, delay1, scaleMore, delay2, nullptr);
		bandage->runAction(RepeatForever::create(seq));
	}
}
