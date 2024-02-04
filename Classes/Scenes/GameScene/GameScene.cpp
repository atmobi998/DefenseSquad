#include "GameScene.h"
#include "GSControlLayer.h"
#include "UIObjects/uiobj.h"
#include "GSBackgroundLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
Scene* GameScene::createScene(int level)
{
	return GameScene::create(level);
}
bool GameScene::init(int _level) {
	if (!Scene::init()) return false;
	level = new LevelModel(_level, this);
	level->startCounting();

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/GameScene/gamescene.mp3", true);

	drawMap();
	addBackground();
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateLevel), 0.01f);

	// Playing tutorial
	if (UserDefault::getInstance()->getBoolForKey("TUTORIAL", true) && _level == 1) {
		auto untilStart = DelayTime::create(1.0f);
		auto instructBegin = CallFunc::create([this](){
			return [&](){
				this->level->pause();
				this->layer = GSTutorial::create(Rect(0.0f, 0.0f, 1.0f, 1.0f), TUTORIAL_1);
				this->addChild(this->layer);

				this->layer->setOkayEvent([this](){
					return [&](){
						this->layer->removeFromParent();
						this->level->resume();
					};
				}());
			};
		}());

		auto untilEnergy = DelayTime::create(2.0f);
		auto instructEnergy = CallFunc::create([this](){
			return [&](){
				this->level->pause();
				this->layer = GSTutorial::create(Rect(Director::getInstance()->getSafeAreaRect().getMinX() + 5.0f + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height * 14 / 16 + Director::getInstance()->getVisibleOrigin().y, Director::getInstance()->getVisibleSize().height / 8 / 90.0f * 238.0f, Director::getInstance()->getVisibleSize().height / 8), TUTORIAL_2);
				this->addChild(this->layer);

				this->layer->setOkayEvent([this](){
					return [&](){
						this->level->resume();
						this->layer->removeFromParent();
					};
				}());
			};
		}());

		auto untilEnemy = DelayTime::create(2.5f);
		auto instructEnemy = CallFunc::create([this](){
			return [&](){
				this->level->pause();
				this->layer = GSTutorial::create(Rect(GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * 6, GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE * 4, SIZE_OF_SQUARE, SIZE_OF_SQUARE), TUTORIAL_3);
				this->addChild(this->layer);

				this->layer->setOkayEvent([this](){
					return [&](){
						this->level->resume();
						this->layer->removeFromParent();
					};
				}());
			};
		}());

		auto untilCell = DelayTime::create(1.0f);
		auto instructCell = CallFunc::create([this](){
			return [&](){
				this->level->pause();
				this->layer = GSTutorial::create(
					Rect(Director::getInstance()->getSafeAreaRect().getMinX() + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height / 16 * 12 + Director::getInstance()->getVisibleOrigin().y, 160.0f * Director::getInstance()->getVisibleSize().height / 8 / 90, Director::getInstance()->getVisibleSize().height / 8),
					Rect(GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * 4, GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE, SIZE_OF_SQUARE, SIZE_OF_SQUARE),
					TUTORIAL_4
				);
				this->addChild(this->layer);

				this->layer->setOkayEvent([this](){
					return [&](){
						this->level->resume();
						this->layer->removeFromParent();
					};
				}());
			};
		}());

		auto seq = Sequence::create(untilStart, instructBegin, untilEnergy, instructEnergy, untilEnemy, instructEnemy, untilCell, instructCell, nullptr);
		this->runAction(seq);
	}

	return true;
}

void GameScene::updateLevel(float) {
	level->update();
}
void GameScene::drawMap() {
	auto drawMapp = GSMap::create();
	drawMapp->createMap(level);
	this->addChild(drawMapp);
	drawMapp->setGlobalZOrder(0.0f);
}

void GameScene::addBackground() {
	auto backgroundLayer = GSBackgroundLayer::create();
	this->addChild(backgroundLayer);
	backgroundLayer->setGlobalZOrder(-1.0f);
}
