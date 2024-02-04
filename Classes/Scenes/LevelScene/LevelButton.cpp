#include "LevelButton.h"
#include "Scenes/GameScene/GameScene.h"
#include "UIObjects/uiobj.h"
#include "UINumeric/UINumeric.h"
#include "SimpleAudioEngine.h"
#define TRANSITION_TIME 0.5f
USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;
levelButton* levelButton::create(int number) {
	levelButton*  button = new(std::nothrow) levelButton;
	std::string filename = "sprites/objects/button/levelButton/numberic";
	std::string png = ".png";
	std::string num = std::to_string(number);
	std::string filenameClicked = filename + num + "_clicked" + png;
	filename = filename + num + png;
	if (button && button->init(filename, filenameClicked, filenameClicked)) {
		CCLOG("true");
		button->level = number;
		button->autorelease();
		button->onTouch();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}
void levelButton::onTouch() {
	this->addTouchEventListener(CC_CALLBACK_2(levelButton::touchControlEvent, this));
}
void levelButton::touchControlEvent(Ref *sender, ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		CCLOG("Touch level!");
		break;
	case ui::Widget::TouchEventType::ENDED:
	{
		CCLOG("level!");
		SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
		auto scene = GameScene::create(level);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		break;
	}
	default:
		break;
	}
}