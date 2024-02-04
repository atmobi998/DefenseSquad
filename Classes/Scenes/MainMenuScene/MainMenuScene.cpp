#include "MainMenuScene.h"
#include "UIObjects/uiobj.h"
#include "MMBackgroundLayer.h"
#include "MMControl.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}
bool MainMenuScene::init() {
	if (!Scene::init()) return false;
	
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/MainMenu/mainmenu.mp3", true);

	addBackground();
	controlButton();
	return true;
}


void MainMenuScene::addBackground() {
	auto backgroundLayer = MMBackgroundLayer::create();
	this->addChild(backgroundLayer, -1);
}


void MainMenuScene::controlButton() {
	auto buttonLayer = MMControl::create();
	this->addChild(buttonLayer, -1);
}

