#include "UIObjects/uiobj.h"
#include "UICell.h"
#include "UICellType/UICellType.h"
USING_NS_CC;

/*
Add UICell to scene
*/
void UICell::addToScene(Scene* scene) {
    scene->addChild(this, CELL_LAYER_ZORDER);
	this->shadow->setOpacity(160);
}

/*
Create a new instance of UICell with CellId
*/
UICell* UICell::create(CellId id) {
	switch (id) {
		// Case id 00: Eosinophils
	case CELL_00_EOSINOPHILS:
	{
		auto cell = UICell00::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Vec2(0.5f, 10.0f / 58));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.65f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_00_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);

		return cell;
		break;
	}

		// Case id 01: Ethry
	case CELL_01_ERYTHROCYTES:
	{
		auto cell = UICell01::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 0.0f));
		// cell->setAnchorPoint(Point(0.5f, 9.0f / 82));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.35f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_01_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);

		return cell;
		break;
	}
//////////////////////////////////////////
	case CELL_02_PLATELETS:
	{
		auto cell = UICell02::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 5.0f / 82));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.45f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_02_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);
		return cell;
		break;
	}
	case CELL_03_BASOPHILS:
	{
		auto cell = UICell03::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 6.0f / 69));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.55f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_03_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);
		return cell;
		break;
	}
	case CELL_04_MONOCYTES:
	{
		auto cell = UICell04::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 11.0f / 71));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.85f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_04_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);
		return cell;
		break;
	}
	case CELL_05_LYMPHOCYTESB:
	{
		auto cell = UICell05::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 2.0f / 42));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.4f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_05_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);
		return cell;
		break;
	}

	case CELL_06_NEUTROPHILS:
	{
		auto cell = UICell06::create();
		cell->setScale(1.1f * OBJECT_SCALE);
		cell->setAnchorPoint(Point(0.5f, 14.0f / 46));

		cell->shadow = Sprite::create(SHADOW_FILENAME);
		cell->addChild(cell->shadow);
		cell->shadow->setScale(0.4f);
		cell->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = Sprite::create(CELL_05_FILENAME)->getContentSize();
		auto anchor = cell->getAnchorPoint();

		cell->shadow->setPosition(Vec2(size.height * anchor.x, size.height * anchor.y));
		cell->shadow->setGlobalZOrder(2.5f);
		return cell;
		break;
	}
	}
    return nullptr;
}