#include "GSBackgroundLayer.h"
#include "GSDefine.h"

USING_NS_CC;

bool GSBackgroundLayer::init() {
	if (!Scene::init())
	{
		return false;
	}
	setBackgroundImagePosition();
	setEnergyBarImage();
	return true;
}

void GSBackgroundLayer::setBackgroundImagePosition()
{
	auto background = Sprite::create(IMG_BG1);
	if (background != nullptr)
	{
		background->setAnchorPoint(Point(0, 0));
		// background->setContentSize(Size(WIDTH, HEIGHT));
		background->setPosition(Vec2(0, 0));
		this->addChild(background);
		background->setGlobalZOrder(-1.0f);
	}
}

void GSBackgroundLayer::setEnergyBarImage() {
	auto energy = Sprite::create(ENERGY_BAR_FILENAME);
	energy->setAnchorPoint(Vec2(0.0f, 0.5f));
	energy->setPosition(Director::getInstance()->getSafeAreaRect().getMinX() + 5.0f + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height * 15 / 16 + Director::getInstance()->getVisibleOrigin().y);
	energy->setScale(Director::getInstance()->getVisibleSize().height / 8 / 90.0f);
	this->addChild(energy);
	energy->setGlobalZOrder(9.0f);
}

