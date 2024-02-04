#include "MMControl.h"
#include "Scenes/GameScene/GSDefine.h"
#include "AppDelegate.h"
#include "UIObjects/UICell/UICellDefinitions.h"
#include "Scenes/LevelScene/LevelScene.h"
#include "Components/MMOptions.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

bool MMControl::init()
{
	// Super init
	if (!Layer::init())
	{
		return false;
	}

	addButtonMenu();

	return true;
}

void MMControl::addButtonMenu() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*
	// Add play button
	auto play = ui::Button::create(PLAY_LAYER_FILENAME, PLAY_LAYER_CLICKED_FILENAME, PLAY_LAYER_CLICKED_FILENAME);
	play->addTouchEventListener(CC_CALLBACK_1(MMControlLayer::GoToGameScene, this));
	this->addChild(play);
	play->setPosition(Vec2(WIDTH/2, HEIGHT*5/8));

	// Add options button
	auto options = ui::Button::create(OPTIONS_LAYER_FILENAME, OPTIONS_LAYER_CLICKED_FILENAME, OPTIONS_LAYER_CLICKED_FILENAME);
	options->addTouchEventListener(CC_CALLBACK_1(MMControlLayer::GoToOptionsCom, this));
	this->addChild(options);
	options->setPosition(Vec2(WIDTH / 2, HEIGHT * 4 / 8));

	// Add quit button
	auto quit = ui::Button::create(QUIT_LAYER_FILENAME, QUIT_LAYER_CLICKED_FILENAME, QUIT_LAYER_CLICKED_FILENAME);
	quit->addTouchEventListener(CC_CALLBACK_1(MMControlLayer::ExitGame, this));
	this->addChild(quit);
	quit->setPosition(Vec2(WIDTH / 2, HEIGHT * 3 / 8));
	*/

	Vector<MenuItem*> MenuItems;

	auto play = MenuItemImage::create(MM_PLAY_LAYER_FILENAME, MM_PLAY_LAYER_CLICKED_FILENAME, CC_CALLBACK_1(MMControl::GoToLevelScene, this));
	play->setScale(1.25);
	MenuItems.pushBack(play);

	auto options = MenuItemImage::create(MM_OPTIONS_LAYER_FILENAME, MM_OPTIONS_LAYER_CLICKED_FILENAME, CC_CALLBACK_1(MMControl::GoToOptionsCom, this));
	options->setScale(1.25);
	MenuItems.pushBack(options);

	auto quit = MenuItemImage::create(MM_QUIT_LAYER_FILENAME, MM_QUIT_LAYER_CLICKED_FILENAME, CC_CALLBACK_1(MMControl::ExitGameMain, this));
	quit->setScale(1.25);
	MenuItems.pushBack(quit);

	auto menu = Menu::createWithArray(MenuItems);

	menu->alignItemsVerticallyWithPadding(9.5f);

	menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * (-1/2) + origin.y));
	auto moveto = JumpTo::create(0.75, Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y + 50.f), visibleSize.height/8, 1);

	auto delay4 = DelayTime::create(0.5f);
	auto delay3 = DelayTime::create(1.0f);

	auto rotoplay = [=]() {
		auto roto = RotateBy::create(2, Vec3(0, 360, 0));
		auto delay = DelayTime::create(14);
		auto seqname = Sequence::create(roto, delay, nullptr);
		auto repeat = RepeatForever::create(seqname);
		play->runAction(repeat);
	};

	auto rotooptions = [=]() {
		auto roto1 = RotateBy::create(2, Vec3(0, 360, 0));
		auto delay1 = DelayTime::create(16);
		auto seqname1 = Sequence::create(roto1, delay1, nullptr);
		auto repeat1 = RepeatForever::create(seqname1);
		options->runAction(repeat1);
	};

	auto rotoquit = [=]() {
		auto roto2 = RotateBy::create(2, Vec3(0, 360, 0));
		auto delay2 = DelayTime::create(18);
		auto seqname2 = Sequence::create(roto2, delay2, nullptr);
		auto repeat2 = RepeatForever::create(seqname2);
		quit->runAction(repeat2);
	};

	auto callFuncplay = CallFunc::create(rotoplay);
	auto callFuncoptions = CallFunc::create(rotooptions);
	auto callFuncquit = CallFunc::create(rotoquit);

	menu->runAction(Sequence::create(delay4, moveto, delay3, callFuncplay, callFuncoptions, callFuncquit, nullptr));

	this->addChild(menu);

}

void MMControl::GoToLevelScene(cocos2d::Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
	auto scene = levelScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MMControl::ExitGameMain(cocos2d::Ref *sender)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->end();
	SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
	Director::getInstance()->end();
}

void MMControl::GoToOptionsCom(cocos2d::Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
	auto layer = MMOptions::create();
	this->addChild(layer,1);
}