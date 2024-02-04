#include "GSControlLayer.h"
#include "GSDefine.h"
#include "AppDelegate.h"
#include "UIObjects/UICell/UICellDefinitions.h"
#include "UIObjects/uiobj.h"

USING_NS_CC;
//global variable

bool GSControlLayer::init(Sprite* choose)
{
    // Super init
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->choose = choose;

	Vector<MenuItem*> MenuItems;
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GSControlLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GSControlLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GSControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void GSControlLayer::setPreviewImage(CellId id, double distance) {

	this->Cell_Id = id;
	this->buttonCheck = true;
	this->distance = distance;
	switch (id)
	{
	case CELL_00_EOSINOPHILS:
		this->link_image = CELL_00_FILENAME;
		this->anchonPoint = Point(0.5f, 10.0f / 58);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_01_ERYTHROCYTES:
		this->link_image = CELL_01_FILENAME;
		this->anchonPoint = Point(0.5f, 0.0f);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_02_PLATELETS:
		this->link_image = CELL_02_FILENAME;
		this->anchonPoint = Point(0.5f, 9.0f / 82);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_03_BASOPHILS:
		this->link_image = CELL_03_FILENAME;
		this->anchonPoint = Point(0.5f, 6.0f / 69);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_04_MONOCYTES:
		this->link_image = CELL_04_FILENAME;
		// this->ScaleNumber = 0.75f;
		this->anchonPoint = Point(0.5f, 11.0f / 71);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_05_LYMPHOCYTESB:
		this->link_image = CELL_05_FILENAME;
		this->anchonPoint = Point(0.5f, 2.0f / 42);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case CELL_06_NEUTROPHILS: 
		this->link_image = CELL_06_FILENAME;
		this->anchonPoint = Point(0.5f, 14.0f / 46);
		this->ScaleNumber = 1.1f * OBJECT_SCALE;
		break;
	case REMOVE_CELL:
		this->link_image = REMOVE_CELL_FILENAME;
		this->anchonPoint = Point(0.5f, 0.5f);
		this->ScaleNumber = 2.0f * OBJECT_SCALE;
	default:
		break;
	}

	// Show where can be placed
	CCLOG("Control init");
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 5; y++) {
			if (CellModel::canPutOn(Cell_Id, level, x, y)) {
				auto square = Sprite::create("sprites/objects/cell/placable.png");
				square->setOpacity(160);
				square->setContentSize(Size(CELL_WIDTH, CELL_WIDTH));
				square->setScale(this->getScale() * 0.65f);
				CCLOG("At %d, %d", x, y);
				auto shrink = ScaleBy::create(0.75f, 0.5f);
				auto deShrink = ScaleBy::create(0.75f, 2.0f);
				auto seq = RepeatForever::create(Sequence::create(shrink, deShrink, nullptr));
				square->runAction(seq);

				this->addChild(square);
				square->setGlobalZOrder(1.25f);
				square->setPosition(Vec2(x * CELL_WIDTH + POS_X_ORIGIN, y * CELL_WIDTH + POS_Y_ORIGIN));
			}
		}
	}
}

bool GSControlLayer::onTouchBegan(Touch *touch, Event *event) {

	auto p = touch->getLocation();
	int size = Sprite::create(link_image)->getContentSize().height;
	if (buttonCheck) {
		this->previewImage = Sprite::create(this->link_image,Rect(0,0,size,size));
		this->previewImage->setRotation3D(Vec3(0, 180.0f, 0));
		this->previewImage->setAnchorPoint(this->anchonPoint);
		this->previewImage->setScale(this->ScaleNumber);

		// Radius around
		if (distance > ACCEPTING_TIME_ERROR){
			auto radius = Sprite::create(RADIUS_PREVIEW);
			previewImage->addChild(radius);
			radius->setGlobalZOrder(1.0f);
			radius->setPosition(previewImage->getContentSize() / 2);
			radius->setScale(distance * 2 * SIZE_OF_SQUARE / radius->getContentSize().height / ScaleNumber);
			radius->setOpacity(200);
		}				

		if (GRASS_OUTSIDE(p)) {
			this->previewImage->setColor(Color3B::RED);
			this->previewImage->setOpacity(150);
			this->previewImage->setPosition(Vec2(p.x, p.y));
		}
		else {
			cur_.x = p.x;
			cur_.y = p.y;
			calculateCellsPosition();
			this->previewImage->setPosition(ROW_COLUMN_TO_POSITION(cellsPosition_));

			if (CellModel::canPutOn(this->Cell_Id,this->level,cellsPosition_.x,cellsPosition_.y)) {
				this->previewImage->setColor(Color3B::WHITE);
			}
			else {
				if (Cell_Id != REMOVE_CELL)
					this->previewImage->setColor(Color3B::RED);
				else
					this->previewImage->setColor(Color3B(200, 200, 200));
			}
		}
		this->addChild(this->previewImage);
		previewImage->setGlobalZOrder(1.5f);
	}
	return true;
}

void GSControlLayer::onTouchMoved(Touch *touch, Event *event) {
	auto p = touch->getLocation();
	if (buttonCheck) {
		if (GRASS_OUTSIDE(p)) {
			this->previewImage->setColor(Color3B::RED);
			this->previewImage->setOpacity(150);
			this->previewImage->setPosition(Vec2(p.x, p.y));
		}
		else {
			
			cur_.x = p.x;
			cur_.y = p.y;
			calculateCellsPosition();
			if (CellModel::canPutOn(this->Cell_Id, this->level, cellsPosition_.x, cellsPosition_.y)){
				this->previewImage->setColor(Color3B::WHITE);
			}
			else {
				if (Cell_Id != REMOVE_CELL)
					this->previewImage->setColor(Color3B::RED);
				else
					this->previewImage->setColor(Color3B::GRAY);
			}
			this->previewImage->setPosition(Vec2(ROW_COLUMN_TO_POSITION(cellsPosition_)));
		}
	}

}
void GSControlLayer::onTouchEnded(Touch *touch, Event *event) {

	auto p = touch->getLocation();
	if (buttonCheck) {
		if (!GRASS_OUTSIDE(p)) {
			cur_.x = p.x;
			cur_.y = p.y;
			GSControlLayer::calculateCellsPosition();
			int b = cellsPosition_.x;
			int a = cellsPosition_.y;
			if (Cell_Id != REMOVE_CELL)
				level->addCell(CellModel::create(this->Cell_Id), cellsPosition_.x, cellsPosition_.y);
			else {
				level->findAndRemoveCell(cellsPosition_.x, cellsPosition_.y);
			}
		}
		this->previewImage->removeFromParent();
		if (choose != nullptr)
			choose->removeFromParent();
		this->removeFromParent();	
	}	
	
}
void GSControlLayer::calculateCellsPosition() {
    for(unsigned int i = 0; i < ROWW;i++){
        for (unsigned int j = 0; j < COLUMNN; j++) {
            if (GRASS_INSIDE(cur_, i, j))
            {
                cellsPosition_.x = j;
                cellsPosition_.y = i;
            }
        }
    }

}
