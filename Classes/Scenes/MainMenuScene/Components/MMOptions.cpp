#include "Models/models.h"
#include "MMOptions.h"

#include "ui/CocosGUI.h"
#include "UIControl/UITextLayer/UISureLayer.h"
#include "Scenes/GameScene/GameScene.h"
#include "Scenes/LevelScene/LevelScene.h"
#include <functional>

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

MMOptions* MMOptions::create() {
	MMOptions *ret = new (std::nothrow) MMOptions;
    if (ret)
    {
        ret->init();
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool MMOptions::init() {
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Add foreground
    auto fore = Sprite::create(OPTIONS_LAYER_FORE_FILENAME);
    this->addChild(fore);
    fore->setGlobalZOrder(12.0f);
    fore->setOpacity(128);
    fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add layer box
    auto box = Sprite::create(OPTIONS_LAYER_FILENAME);
    this->addChild(box);
    box->setGlobalZOrder(12.0f);
    box->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    int bias = 0;

#ifdef __CAN_UNLOCK__
    bias = 1;
#endif // DEBUG

#ifndef __CAN_UNLOCK__
	// Add Options Text
	auto optionstext = Sprite::create(OPTIONS_TEXT_FILENAME);
	this->addChild(optionstext);
	optionstext->setGlobalZOrder(12.0f);
	optionstext->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2  + origin.y + 45.f * 2 + 15.f * 2);
#endif // !__CAN_UNLOCK__

    // Add reset button
    auto reset = ui::Button::create(OPTIONS_LAYER_RESET_FILENAME, OPTIONS_LAYER_RESET_CLICKED_FILENAME, OPTIONS_LAYER_RESET_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> resetTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:  
                {
                    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);

                    function<function<void()>()> cancelTouch = [this]() -> function<void()> {
                        return [&]() {
                            SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                            Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this, true);
                        };
                    };

                    function<function<void(Ref*, ui::Widget::TouchEventType)>()> okayTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
                        return [&](Ref* sender, ui::Widget::TouchEventType type) {
                            if (type == ui::Widget::TouchEventType::ENDED) {
                                SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");

                                UserDefault::getInstance()->setIntegerForKey("CURRENT_LEVEL", 1);
                                UserDefault::getInstance()->setIntegerForKey("CURRENT_CELL", 0);
                                UserDefault::getInstance()->setBoolForKey("TUTORIAL", true);

                                Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
                                this->removeFromParent();
                            }
                        };
                    };

                    auto sureLayer = UISureLayer::create();
                    sureLayer->setCancelTouch(cancelTouch());
                    sureLayer->setOkayTouch(okayTouch());
                    this->addChild(sureLayer);
                }
                default:
                    break;
            }
        };
    };

    reset->addTouchEventListener(resetTouch());
    this->addChild(reset);
    reset->setGlobalZOrder(12.0f);
    reset->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60.0f * (1 - bias)));

#ifdef __CAN_UNLOCK__
// Add unlock button
    auto unlock = ui::Button::create(OPTIONS_LAYER_UNLOCK_FILENAME, OPTIONS_LAYER_UNLOCK_CLICKED_FILENAME, OPTIONS_LAYER_UNLOCK_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> unlockTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:  
                {
                    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);

                    function<function<void()>()> cancelTouch = [this]() -> function<void()> {
                        return [&]() {
                            SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                            Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this, true);
                        };
                    };

                    function<function<void(Ref*, ui::Widget::TouchEventType)>()> okayTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
                        return [&](Ref* sender, ui::Widget::TouchEventType type) {
                            if (type == ui::Widget::TouchEventType::ENDED) {
                                SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");

                                UserDefault::getInstance()->setIntegerForKey("CURRENT_LEVEL", 9);
                                UserDefault::getInstance()->setIntegerForKey("CURRENT_CELL", 6);
                                UserDefault::getInstance()->setBoolForKey("TUTORIAL", false);

                                Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
                                this->removeFromParent();
                            }
                        };
                    };

                    auto sureLayer = UISureLayer::create();
                    sureLayer->setCancelTouch(cancelTouch());
                    sureLayer->setOkayTouch(okayTouch());
                    this->addChild(sureLayer);
                }
                default:
                    break;
            }
        };
    };
    unlock->addTouchEventListener(unlockTouch());
    this->addChild(unlock);
    unlock->setGlobalZOrder(12.0f);
    unlock->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60.0f));
#endif // DEBUG
	
    // Add okay button
    auto okay = ui::Button::create(OPTIONS_LAYER_OKAY_FILENAME, OPTIONS_LAYER_OKAY_CLICKED_FILENAME, OPTIONS_LAYER_OKAY_CLICKED_FILENAME);
	
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> okayTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
			
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED: 
				{
                    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
					Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
					this->removeFromParent();
					break;
				}
                default:
                    break;
            }
			

        };
    };
	
	okay->addTouchEventListener(okayTouch());
	//Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this, true);
    this->addChild(okay);
	okay->setGlobalZOrder(12.0f);
	okay->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 45.0f * 2 - 15.0f * 2));

    // Add music slider
    auto music = Sprite::create(OPTIONS_LAYER_MUSIC_FILENAME);
    this->addChild(music);
    music->setGlobalZOrder(12.0f);
    music->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height / 2 + origin.y + 60.0f * (1 + bias)));
	//music->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height * 0.675 + origin.y - 45.0f - 15.0f));

    auto music_base = Sprite::create(OPTIONS_LAYER_SLIDER_BASE_FILENAME);
    this->addChild(music_base);
    music_base->setGlobalZOrder(12.0f);
    music_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height / 2 + origin.y + 60.0f * (1 + bias)));
	//music_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height * 0.675 + origin.y - 45.0f - 15.0f));

    auto music_volume = UserDefault::getInstance()->getFloatForKey("MUSIC_VOLUME", 1.0f);

    music_slider = Sprite::create(OPTIONS_LAYER_SLIDER_FILENAME);
    this->addChild(music_slider);
    music_slider->setGlobalZOrder(12.0f);
    music_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f - (1.0f - music_volume) * 150.0f, visibleSize.height / 2 + origin.y + 60.0f * (1 + bias)));
	//music_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f, visibleSize.height * 0.675 + origin.y - 45.0f - 15.0f));

    // Function set
    function<function<bool(Touch*, Event*)>()> emptyMusic = [this]() -> function<bool(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            if (this->music_slider->getBoundingBox().containsPoint(touch->getLocation()))
                return true;
            else
                return false;
        };
    };

    function<function<void(Touch*, Event*)>()> dragMusic = [this]() -> function<void(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            auto posTouch = touch->getLocation().x;
            CCLOG("%f", posTouch);

            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            auto left = visibleSize.width / 2 + origin.x - 40.0f;
            auto right = visibleSize.width / 2 + origin.x + 110.0f;

            this->music_slider->setPositionX(fmin(right, fmax(left, posTouch)));
            CCLOG("%f Slider", this->music_slider->getPositionX());

            auto volume = (this->music_slider->getPositionX() - left) / 150.0f;
            auto audio = SimpleAudioEngine::getInstance();
            audio->setBackgroundMusicVolume(volume);
        };
    };

    function<function<void(Touch*, Event*)>()> afterDragMusic = [this]() -> function<void(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            auto left = visibleSize.width / 2 + origin.x - 40.0f;
            auto right = visibleSize.width / 2 + origin.x + 110.0f;

            auto volume = (this->music_slider->getPositionX() - left) / 150.0f;
            UserDefault::getInstance()->setFloatForKey("MUSIC_VOLUME", volume);
            UserDefault::getInstance()->flush();

            auto audio = SimpleAudioEngine::getInstance();
            audio->setBackgroundMusicVolume(volume);
        };
    };

    auto slideMusic = EventListenerTouchOneByOne::create();
	slideMusic->setSwallowTouches(true);
	slideMusic->onTouchBegan = emptyMusic();
	slideMusic->onTouchMoved = dragMusic();
	slideMusic->onTouchEnded = afterDragMusic();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(slideMusic, music_slider);

    // Add effect slider
    auto effect = Sprite::create(OPTIONS_LAYER_EFFECT_FILENAME);
    this->addChild(effect);
    effect->setGlobalZOrder(12.0f);
	effect->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height / 2 + origin.y + 60.0f * bias));
    //effect->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height * 0.65 + origin.y - 45.0f * 2 - 15.0f * 2));

    auto effect_base = Sprite::create(OPTIONS_LAYER_SLIDER_BASE_FILENAME);
    this->addChild(effect_base);
    effect_base->setGlobalZOrder(12.0f);
	effect_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height / 2 + origin.y + 60.0f * bias));
    //effect_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height * 0.65  + origin.y - 45.0f * 2 - 15.0f * 2));

    auto effect_volume = UserDefault::getInstance()->getFloatForKey("EFFECT_VOLUME", 1.0f);

    effect_slider = Sprite::create(OPTIONS_LAYER_SLIDER_FILENAME);
    this->addChild(effect_slider);
    effect_slider->setGlobalZOrder(12.0f);
	effect_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f - (1.0f - effect_volume) * 150.0f, visibleSize.height / 2 + origin.y + 60.0f * bias));
    //effect_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f, visibleSize.height * 0.65 + origin.y - 45.0f * 2 - 15.0f * 2));

    // Function set
    function<function<bool(Touch*, Event*)>()> emptyEffect = [this]() -> function<bool(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            if (this->effect_slider->getBoundingBox().containsPoint(touch->getLocation()))
                return true;
            else
                return false;
        };
    };

    function<function<void(Touch*, Event*)>()> dragEffect = [this]() -> function<void(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            auto posTouch = touch->getLocation().x;
            CCLOG("%f", posTouch);

            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            auto left = visibleSize.width / 2 + origin.x - 40.0f;
            auto right = visibleSize.width / 2 + origin.x + 110.0f;

            this->effect_slider->setPositionX(fmin(right, fmax(left, posTouch)));
            CCLOG("%f Slider", this->effect_slider->getPositionX());
        };
    };

    function<function<void(Touch*, Event*)>()> afterDragEffect = [this]() -> function<void(Touch*, Event*)> {
        return [&](Touch* touch, Event* event) {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            auto left = visibleSize.width / 2 + origin.x - 40.0f;
            auto right = visibleSize.width / 2 + origin.x + 110.0f;

            auto volume = (this->effect_slider->getPositionX() - left) / 150.0f;
            UserDefault::getInstance()->setFloatForKey("EFFECT_VOLUME", volume);
            UserDefault::getInstance()->flush();

            auto audio = SimpleAudioEngine::getInstance();
            audio->setEffectsVolume(volume);
        };
    };

    auto slideEffect = EventListenerTouchOneByOne::create();
	slideEffect->setSwallowTouches(true);
	slideEffect->onTouchBegan = emptyEffect();
	slideEffect->onTouchMoved = dragEffect();
	slideEffect->onTouchEnded = afterDragEffect();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(slideEffect, effect_slider);
	return true;
	
}