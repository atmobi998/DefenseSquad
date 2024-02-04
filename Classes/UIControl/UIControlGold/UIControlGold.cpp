#include "UIControlGold.h"
#include "Scenes/GameScene/GSDefine.h"

USING_NS_CC;

void UIControlGold::setCellPosition(double cellX, double cellY) {
	setPosition(Vec2((float)cellX * CELL_WIDTH + POS_X_ORIGIN, (float)cellY * CELL_WIDTH + POS_Y_ORIGIN));
}

/*
Add UIObjects to Scene
*/
void UIControlGold::addToScene(Scene* scene) {
	scene->addChild(this, GOLD_LAYER_ZORDER);
}

/*
Remove UIObjects from Scene
*/
void UIControlGold::removeFromScene() {
	removeFromParent();
}

void UIControlGold::touchControlEvent(Ref *sender, ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		CCLOG("Touch");
		break;
	case ui::Widget::TouchEventType::ENDED:
		CCLOG("Gold update");
		//update gold
		removeFromScene();
		break;
	default:
		break;
	}
};

UIControlGold* UIControlGold::create() {
	UIControlGold *btn = new (std::nothrow) UIControlGold;
	if (btn && btn->init(IMG_GOLD, IMG_GOLD, IMG_GOLD, TextureResType::LOCAL))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

void UIControlGold::onTouch() {
	this->addTouchEventListener(CC_CALLBACK_2(UIControlGold::touchControlEvent, this));
}
