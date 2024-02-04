#include "GSMap.h"
#include "AppDelegate.h"
#include "Components/GSFlag.h"
#include "Components/GSBrick.h"
#include <functional>

USING_NS_CC;

bool GSMap::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return true;
}
void GSMap::createMap(LevelModel *level) {
	int a = level->getMap().size();
	int b = level->getMap()[0].size(); 

	auto mapImage = Sprite::create("sprites/MapLayer/khonggian.png");
	mapImage->setContentSize(Size(SIZE_OF_SQUARE * COLUMNN, SIZE_OF_SQUARE * ROWW));
	mapImage->setAnchorPoint(Vec2(0,0));
	positionCell temp;
	mapImage->setPosition(Vec2(GRASS_ORIGIN_POSITION_X, GRASS_ORIGIN_POSITION_Y));

	auto map = level->getMap();
	std::function<bool(int, int)> checkPath = [&map](int i, int j) -> bool {
		return (map[i][j] == 5 || map[i][j] == 1 || map[i][j] == 2);
	};

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			temp.x = i;
			temp.y = j;
			if (checkPath(i, j)) {
				// auto enemyWay = Sprite::create("sprites/MapLayer/black.png");
				// enemyWay->setContentSize(Size(SIZE_OF_SQUARE, SIZE_OF_SQUARE));
				// enemyWay->setPosition(ROW_COLUMN_TO_POSITION(temp));
				// this->addChild(enemyWay);

				// Draw bricks
				bool left, right, up, down;
				left = right = up = down = false;
				
				if (i > 0) {
					if (checkPath(i - 1, j)) left = true;
				}
				if (i < a - 1) {
					if (checkPath(i + 1, j)) right = true;
				}
				if (j > 0) {
					if (checkPath(i, j - 1)) down = true;
				}
				if (j < b - 1) {
					if (checkPath(i, j + 1)) up = true;
				}

				auto brick = GSBrick::create();
				brick->setContentSize(Size(SIZE_OF_SQUARE, SIZE_OF_SQUARE));
				brick->setPosition(ROW_COLUMN_TO_POSITION(temp));
				this->addChild(brick);
				brick->setGlobalZOrder(0.0f);
				brick->putPiecesIntoPlace(left, right, up, down);

				// Draw beginpoint of the path
				auto beginPaths = level->getBeginPaths();
				for (auto it = beginPaths.begin(); it != beginPaths.end(); it++) {
					if ((*it)[0] == i && (*it)[1] == j) {
						auto tent = Sprite::create("sprites/objects/disease/tent.png");
						tent->setScale(1.25f * SIZE_OF_SQUARE / 98.0f);
						tent->setAnchorPoint(Vec2(0.5f, 18.0f / 80));
						tent->setPosition(ROW_COLUMN_TO_POSITION(temp));
						this->addChild(tent);
						tent->setGlobalZOrder(2.0f + 5.0f - j / 5.0f);
					}
				}
				
				// Draw endpoint of the path
				auto endPaths = level->getEndPaths();
				for (auto it = endPaths.begin(); it != endPaths.end(); it++) {
					if ((*it)[0] == i && (*it)[1] == j) {
						auto flag = GSFlag::create();
						flag->setAnchorPoint(Vec2(0.75f, 0.125f));
						flag->setPosition(ROW_COLUMN_TO_POSITION(temp));
						flag->flutterAnimate();
						this->addChild(flag);
						flag->setGlobalZOrder(2.0f + 5.0f - j / 5.0f);
					}
				}
			}
		}
	}
	this->addChild(mapImage);
	mapImage->setGlobalZOrder(0.0f);
}