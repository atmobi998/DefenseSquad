#include "UIControlEnergy.h"
#include "Scenes/GameScene/GSDefine.h"
#include "UIObjects/uiobj.h"
#include "Models/models.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

void UIControlEnergy::setCellPosition(double cellX, double cellY) {
	setPosition(Vec2((float)cellX * CELL_WIDTH + POS_X_ORIGIN, (float)cellY * CELL_WIDTH + POS_Y_ORIGIN));
	setPosition(getPosition() + Vec2(0.0f, 80.0f));
	setGlobalZOrder(7.0f - cellY / 5.0f);
}

/*
Add UIObjects to Scene
*/
void UIControlEnergy::addToScene(Scene* scene) {
	canCollect = true;
	scene->addChild(this, ENERGY_LAYER_ZORDER);
	idleAnimate();
	onTouch();
}

/*
Remove UIObjects from Scene
*/
void UIControlEnergy::removeFromScene() {
    removeFromParent();
}

void UIControlEnergy::touchControlEvent(Ref *sender, ui::Widget::TouchEventType type) {
	if (canCollect) {
		std::function< std::function<void()> (LevelModel*) > func = [](LevelModel* level) -> std::function<void()> {
				auto target = level;
				return [target] () {
					target->addEnergyValue(50);
				};
		};

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			CCLOG("Touch");
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Energy update");
			canCollect = false;
			SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/collect_energy.mp3");
			destroyAnimate(func(level));
			break;
		default:
			break;
		}
	}
};

UIControlEnergy* UIControlEnergy::create(LevelModel* level) {
	UIControlEnergy *btn = new (std::nothrow) UIControlEnergy;
	if (btn && btn->init(IMG_ENERGY, IMG_ENERGY, IMG_ENERGY, TextureResType::LOCAL))
	{
		btn->level = level;
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

void UIControlEnergy::onTouch() {
	this->addTouchEventListener(CC_CALLBACK_2(UIControlEnergy::touchControlEvent, this));
}

/*
Pop up animation
*/
void UIControlEnergy::appearAnimate() {
	this->setScale(0.4f);
	auto scaleUp = ScaleTo::create(ANIM_ENERGY_POPUP_DURATION / 2, 1.0f);
	auto jump = JumpBy::create(ANIM_ENERGY_POPUP_DURATION, Vec2(CCRANDOM_MINUS1_1() * CELL_WIDTH, 0 - CELL_WIDTH / 4 * (CCRANDOM_0_1() * 0.75f + 0.25f) - 80.0f), CELL_WIDTH * (1.5f + 0.25f * CCRANDOM_0_1()), 1);
	this->runAction(jump);
	this->runAction(scaleUp);
}

/*
Idle animation
*/
void UIControlEnergy::idleAnimate() {
	auto sheet = Sprite::create("sprites/objects/pickup/animEnergy.png");
	auto width = sheet->getContentSize().width;
	auto height = sheet->getContentSize().height;
	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < 6; i++) {
		animFrames.pushBack(SpriteFrame::create("sprites/objects/pickup/animEnergy.png", Rect(i * width / 6, 0, width / 6, height)));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 8.0f);
	auto animate = Animate::create(animation);

	child = Sprite::create("sprites/objects/pickup/animEnergy.png", Rect(0, 0, width / 6, height));
	child->setAnchorPoint(Vec2(0.0f, 0.0f));
	child->runAction(RepeatForever::create(animate));
	this->addChild(child);
	child->setGlobalZOrder(8.0f);
}

/*
Destroy animation
*/
void UIControlEnergy::destroyAnimate(std::function<void()> func) {
	child->setGlobalZOrder(10.5f);
	auto pos = getParent()->convertToNodeSpace(getPosition());
	auto move = MoveBy::create(ANIM_ENERGY_DESTROY_DURATION, Vec2(0 - pos.x, Director::getInstance()->getVisibleSize().height - pos.y));
	auto fade = FadeTo::create(ANIM_ENERGY_DESTROY_DURATION, 0);
	auto call = CallFuncN::create([] (Node* node) {
		node->getParent()->removeFromParent();
	});
	auto callback = CallFunc::create(func);
	auto seq = Sequence::create(fade, call, callback, nullptr);
	child->runAction(move);
	child->runAction(seq);
}
