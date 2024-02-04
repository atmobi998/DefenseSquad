#include "UIControlCellBar.h"
#include "Scenes/GameScene/GSDefine.h"
#include "Scenes/GameScene/GSControlLayer.h"
#include <functional>
#include "UINumeric/UINumeric.h"
#include <vector>
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

/*
Add to Scene
*/
void UIControlCellBar::addToScene(Scene* scene) {
	this->scene = scene;
	scene->addChild(this);
	this->setGlobalZOrder(9.0f);
	onTouch();

	loading = Sprite::create(CELLBAR_LOADING_FILENAME);
	loading->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(loading);
	loading->setGlobalZOrder(10.5f);
	loading->setOpacity(170);

	canActivate = false;
}

void UIControlCellBar::touchControlEvent(Ref *sender, ui::Widget::TouchEventType type) {
	if (level->getEnergyValue() < cost && canActivate) {
		level->emphasizeEnergy();
		return;
	}

	if (canActivate) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			CCLOG("Touch");
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			CCLOG("Cell Hold");
			SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");

			// Choosing sprite
			choosing = Sprite::create(CELLBAR_CHOOSING_FILENAME);
			addChild(choosing);
			choosing->setPosition(this->getContentSize() / 2);
			choosing->setGlobalZOrder(9.0f);

			auto controlLayer = GSControlLayer::create(level, choosing);
			scene->addChild(controlLayer, CELLBAR_LAYER_ZORDER);
			controlLayer->setGlobalZOrder(11.5f);
			controlLayer->setPreviewImage(id, distance);
			break;
		}
		default:
			break;
		}
	}
};

UIControlCellBar* UIControlCellBar::create(LevelModel* level, CellId id, int cost, double distance) {
	UIControlCellBar *btn = new (std::nothrow) UIControlCellBar;

	std::string filename;
	std::vector<std::string> icons;

	switch(id) {
	case CELL_00_EOSINOPHILS:
		filename = CELLBAR_00_FILENAME;
		icons.push_back(ICON_ATTACK);
		icons.push_back(ICON_LANE);
		break;
	case CELL_01_ERYTHROCYTES:
		filename = CELLBAR_01_FILENAME;
		icons.push_back(ICON_EFFECT);
		icons.push_back(ICON_LANE);
		break;
	case CELL_02_PLATELETS:
		filename = CELLBAR_02_FILENAME;
		icons.push_back(ICON_DEFENSE);
		icons.push_back(ICON_PATH);
		break;
	case CELL_03_BASOPHILS:
		filename = CELLBAR_03_FILENAME;
		icons.push_back(ICON_ATTACK);
		icons.push_back(ICON_LANE);
		break;
	case CELL_04_MONOCYTES:
		filename = CELLBAR_04_FILENAME;
		icons.push_back(ICON_EFFECT);
		icons.push_back(ICON_PATH);
		break;
	case CELL_05_LYMPHOCYTESB:
		filename = CELLBAR_05_FILENAME;
		icons.push_back(ICON_ATTACK);
		icons.push_back(ICON_LANE);
		break;
	case CELL_06_NEUTROPHILS:
		filename = CELLBAR_06_FILENAME;
		icons.push_back(ICON_EFFECT);
		icons.push_back(ICON_PATH);
		break;
	default:
		filename = CELLBAR_00_FILENAME;
		break;
	}

	if (btn && btn->init(filename, filename, filename, TextureResType::LOCAL))
	{
		btn->level = level;
		btn->id = id;
		btn->cost = cost;
		btn->distance = distance;
		btn->autorelease();
		btn->setScale(CELLBAR_SCALE);

		// Cost show
		auto costShow = UINumeric::create();
		costShow->setScale(0.3f);
		costShow->setPosition(8.0f, 18.0f);
		btn->addChild(costShow);
		costShow->setGlobalZOrder(9.25f);
		costShow->changeValue(cost);

		// Icon type
		for (auto i = 0u; i < icons.size(); i++) {
			auto icon = Sprite::create(icons[i]);
			icon->setPosition(16.0f + i * 20.0f, 65.0f);
			btn->addChild(icon);
			icon->setGlobalZOrder(9.25f);
		}
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

void UIControlCellBar::onTouch() {
	this->addTouchEventListener(CC_CALLBACK_2(UIControlCellBar::touchControlEvent, this));
}

/*
Update recharge loading
*/
void UIControlCellBar::updateRecharge(double percentage) {
	if (abs(0.0 - percentage) < DOUBLE_PRECISION) {
		if (canActivate == false) {
			flashAnimate();
			this->setColor(Color3B::WHITE);
		}
		canActivate = true;
	} else {
		canActivate = false;
		this->setColor(Color3B(190, 190, 190));
	}
	loading->setScaleY(percentage);
}

/*
Flas animate of cell bar
*/
void UIControlCellBar::flashAnimate() {
	auto flash = Sprite::create(CELLBAR_LOADING_COMPLETE_FILENAME);
	flash->setAnchorPoint(Vec2(0.0f, 0.0f));
	flash->setOpacity(0);
	addChild(flash);
	flash->setGlobalZOrder(10.5f);

	// Flashing
	auto fadeIn = FadeTo::create(ANIM_CELLBAR_FLASH, 255);
	auto fadeOut = FadeTo::create(ANIM_CELLBAR_FLASH, 0);
	auto remove = RemoveSelf::create();
	auto seq  = Sequence::create(fadeIn, fadeOut, remove, nullptr);
	flash->runAction(seq);
}