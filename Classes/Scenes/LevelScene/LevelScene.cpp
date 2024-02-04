#include "LevelScene.h"
#include "UIObjects/uiobj.h"
#include "LevelButton.h"
#include "Scenes/GameScene/GSDefine.h"
#include "SwitchSceneButton.h"
#include "Scenes/MainMenuScene/MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* levelScene::createScene()
{
	return levelScene::create();
}
bool levelScene::init() {
	if (!Scene::init()) return false;

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/LevelScene/levelscene.mp3", true);

	CreateButtonLevel();
	SetBackGround();
	CreateBackButton();
	return true;
}
void levelScene::SetBackGround() {
	auto t = time(NULL);
	auto hour = localtime(&t)->tm_hour;
	auto background = Sprite::create(BACK_GROUND_2);
	if (hour < 6 || hour >= 18) {
		background = Sprite::create(BACK_GROUND_3);
	}
	else if (hour >= 6 && hour < 15) {
		background = Sprite::create(BACK_GROUND_1);
	}
	if (background != nullptr)
	{
		background->setAnchorPoint(Point(0, 0));
		background->setContentSize(Size(WIDTH + VISIBLE_ORIGIN_X, HEIGHT + VISIBLE_ORIGIN_Y));
		background->setPosition(Vec2(0, 0));
		background->setOpacity(175);
		this->addChild(background);
	}
}
void levelScene::CreateButtonLevel() {
	auto data = UserDefault::getInstance();
	int level_current = data->getIntegerForKey("CURRENT_LEVEL", 1);	
	for (int level = 1; level <= 8; level++) {
		if (level <= level_current) {
			levelButton* button = levelButton::create(level);
			button->setPosition(Vec2(level * WIDTH / 9  + VISIBLE_ORIGIN_X,HEIGHT  * 2 / 3 + VISIBLE_ORIGIN_Y));
			this->addChild(button, 5);
		}
		else {
			auto lock = Sprite::create(LOCK_BUTTON);
			lock->setPosition(Vec2(level * WIDTH / 9 + VISIBLE_ORIGIN_X, HEIGHT * 2 / 3 + VISIBLE_ORIGIN_Y));
			this->addChild(lock, 5);
		}
	}
}
void levelScene::CreateBackButton() {
	SwitchSceneButton* back_button = SwitchSceneButton::create( BUTTON_BACK, BUTTON_BACK_CLICKED);
	back_button->setScale(1.25);
	back_button->setPosition(Vec2(WIDTH - 113.75f + VISIBLE_ORIGIN_X, 44.5f + VISIBLE_ORIGIN_Y));
	this->addChild(back_button,5);
}

	