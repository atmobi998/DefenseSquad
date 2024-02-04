#include "UIObjects/uiobj.h"
#include "UIDisease.h"
#include "UIDiseaseType/UIDiseaseType.h"
#include "Scenes/GameScene/GSDefine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*
Add UIDisease to scene
*/
void UIDisease::addToScene(Scene* scene) {
    scene->addChild(this, DISEASE_LAYER_ZORDER);
	this->shadow->setOpacity(160);

	this->setScale(this->getScale() * 0.1f);
	auto scaleUp = ScaleBy::create(0.25f, 10.0f);
	this->runAction(scaleUp);
}

/*
Create a new instance of UIDisease with DiseaseId
*/
UIDisease* UIDisease::create(DiseaseId id) {
    switch (id) {
    // Case id 00: Rabies
    case DISEASE_00_RABIES:
	{
		auto disease = UIDisease00::create();
		disease->setScale(1.1f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.2f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.5f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_01_SMALLPOX:
	{
		auto disease = UIDisease01::create();
		disease->setScale(2.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.375f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.25f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_02_INFLUENZA:
	{
		auto disease = UIDisease02::create();
		disease->setScale(1.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.25f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.5f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_03_MEASLES:
	{
		auto disease = UIDisease03::create();
		disease->setScale(2.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.35f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.3f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_04_POLIO:
	{
		auto disease = UIDisease04::create();
		disease->setScale(1.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.25f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.5f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_05_MALARIA:
	{
		auto disease = UIDisease05::create();
		disease->setScale(1.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.0f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.2f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
	case DISEASE_06_EBOLA:
	{
		auto disease = UIDisease06::create();
		disease->setScale(2.5f * OBJECT_SCALE);
		disease->setAnchorPoint(Vec2(0.5f, 0.25f));

		disease->shadow = Sprite::create(SHADOW_FILENAME);
		disease->addChild(disease->shadow);
		disease->shadow->setScale(0.5f);
		disease->shadow->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto size = 64.0f;
		auto anchor = disease->getAnchorPoint();

		disease->shadow->setPosition(Vec2(size * anchor.x, size * anchor.y));
		disease->shadow->setGlobalZOrder(2.5f);
		return disease;
		break;
	}
    }

    return nullptr;
}

void UIDisease::attackAnimate(Direction dir) {
	SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/disease_hit.mp3");
	switch (dir) {
	case DOWN:
	{
		auto movetoattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY() - SIZE_OF_SQUARE));
		auto movebackattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY()));
		auto attackseq = Sequence::create(movetoattack, movebackattack, nullptr);
		this->runAction(attackseq);
	}

	break;

	case LEFT:
	{
		auto movetoattack = MoveTo::create(0.2, Vec2(this->getPositionX() - SIZE_OF_SQUARE, this->getPositionY()));
		auto movebackattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY()));
		auto attackseq = Sequence::create(movetoattack, movebackattack, nullptr);
		this->runAction(attackseq);
	}
	break;

	case RIGHT:
	{
		auto movetoattack = MoveTo::create(0.2, Vec2(this->getPositionX() + SIZE_OF_SQUARE / 2, this->getPositionY()));
		auto movebackattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY()));
		auto attackseq = Sequence::create(movetoattack, movebackattack, nullptr);
		this->runAction(attackseq);
	}
	break;

	case UP:
	{
		auto movetoattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY() + SIZE_OF_SQUARE / 2));
		auto movebackattack = MoveTo::create(0.2, Vec2(this->getPositionX(), this->getPositionY()));
		auto attackseq = Sequence::create(movetoattack, movebackattack, nullptr);
		this->runAction(attackseq);
	}
	break;
	default:
		break;
	}
}

void UIDisease::hitAnimate(Direction dir) {
	auto tintTo = cocos2d::TintTo::create(0.1, cocos2d::Color3B::RED);
	auto tintTo_ = cocos2d::TintTo::create(0.1, cocos2d::Color3B::WHITE);
	auto hitanim = cocos2d::Sequence::create(tintTo, tintTo_, nullptr);
	this->runAction(hitanim);

}

void UIDisease::dieAnimate(Direction dir) {
	this->stopAllActions();
	auto fadeout = FadeOut::create(1);
	auto remove = RemoveSelf::create();
	auto seq = Sequence::create(fadeout, remove, nullptr);
	this->runAction(seq);
}