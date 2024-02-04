#include "UINumeric.h"
#include "../Scenes/GameScene/GSDefine.h"

USING_NS_CC;


/*
Add to Scene
*/
void UINumeric::addToScene(Scene* scene) {
    scene->addChild(this, NUMERIC_LAYER_ZORDER);
	this->setGlobalZOrder(10.0f);
}

/*
Remove from Scene
*/
void UINumeric::removeFromScene() {
    removeFromParent();
}


void UINumeric::changeValue(int value) {
	for (auto digit : digitList) {
		this->removeChild(digit);
	}
	digitList.clear();

	std::string number = std::to_string(value);
	for (int j = 0; j < number.length(); j++) {
		int i = number[j];
		i = i - 48;
		auto sprite = Sprite::create(NUMERIC_IMG);
		auto ith_number = Sprite::create(NUMERIC_IMG, Rect(sprite->getContentSize().width / 10 * i, 0, sprite->getContentSize().width / 10, sprite->getContentSize().height));
		sprite->setContentSize(Size(sprite->getContentSize().width * scale, sprite->getContentSize().height * scale));
		ith_number->setAnchorPoint(Vec2(0.0f, 0.5f));
		ith_number->setContentSize(Size(ith_number->getContentSize().width * scale, ith_number->getContentSize().height * scale));
		ith_number->setPosition(Vec2(ith_number->getContentSize().width * (1/2 + j), 0.0f));
		this->addChild(ith_number, NUMERIC_LAYER_ZORDER);
		ith_number->setGlobalZOrder(10.0f);
		digitList.pushBack(ith_number);
	}
}

UINumeric* UINumeric::create() {
	UINumeric * ret = new (std::nothrow) UINumeric;
    if (ret && ret->init())
    {
		ret->scale = 0.67;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void UINumeric::emphasizeAnimate() {
	for (auto sprite : digitList) {
		auto blinkRed = TintTo::create(0.05f, Color3B::RED);
		auto blinkWhite = TintTo::create(0.05f, Color3B::WHITE);
		auto delay = DelayTime::create(0.05f);
		auto seq = Sequence::create(blinkRed, blinkWhite, delay, blinkRed, blinkWhite, nullptr);
		sprite->runAction(seq);
	}
}