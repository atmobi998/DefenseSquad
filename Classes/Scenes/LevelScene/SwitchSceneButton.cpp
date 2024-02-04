#include "SwitchSceneButton.h"
#include "UIObjects/uiobj.h"
#include "UINumeric/UINumeric.h"
#include "Scenes/MainMenuScene/MainMenuScene.h"
#include "SimpleAudioEngine.h"
#define TRANSITION_TIME 0.5f
USING_NS_CC;
using namespace CocosDenshion;
//SwitchSceneButton* SwitchSceneButton::create(Scene* scene,std::string button_,std::string button_clicked) {
SwitchSceneButton* SwitchSceneButton::create(std::string button_, std::string button_clicked) {
	SwitchSceneButton* button = new(std::nothrow) SwitchSceneButton;
	if (button && button->init(button_, button_clicked, button_clicked)) {
		CCLOG("true");
		button->onTouch();
		button->autorelease();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}
void SwitchSceneButton::onTouch() {
	this->addTouchEventListener(CC_CALLBACK_2(SwitchSceneButton::touchControlEvent, this));
}
void SwitchSceneButton::touchControlEvent(Ref *sender, ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		CCLOG("Touch back!");
		break;
	case ui::Widget::TouchEventType::ENDED:
	{
		SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
		CCLOG("back!");
		auto scene = MainMenuScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		break;
	}
	default:
		break;
	}
}