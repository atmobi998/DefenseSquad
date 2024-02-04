#include "UIPauseLayer.h"
#include "Models/models.h"
#include "ui/CocosGUI.h"
#include "UIControl/UITextLayer/UISureLayer.h"
#include "Scenes/GameScene/GameScene.h"
#include "Scenes/LevelScene/LevelScene.h"
#include <functional>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

UIPauseLayer* UIPauseLayer::create(LevelModel* level) {
    UIPauseLayer *ret = new (std::nothrow) UIPauseLayer;
    if (ret)
    {
        ret->init(level);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void UIPauseLayer::init(LevelModel* level) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    this->level = level;

    // Add foreground
    auto fore = Sprite::create(PAUSE_LAYER_FORE_FILENAME);
    this->addChild(fore);
    fore->setGlobalZOrder(12.0f);
    fore->setOpacity(128);
    fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add layer box
    auto box = Sprite::create(PAUSE_LAYER_FILENAME);
    this->addChild(box);
    box->setGlobalZOrder(12.0f);
    box->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add resume button
    auto resume = ui::Button::create(PAUSE_LAYER_RESUME_FILENAME, PAUSE_LAYER_RESUME_CLICKED_FILENAME, PAUSE_LAYER_RESUME_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> resumeTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                    this->level->resume();
                    this->removeFromParent();   
                    break;
                default:
                    break;
            }
        };
    };
    
    resume->addTouchEventListener(resumeTouch());
    this->addChild(resume);
    resume->setGlobalZOrder(12.0f);
    resume->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 45.0f * 2 + 15.0f * 2));

    // Add restart button
    auto restart = ui::Button::create(PAUSE_LAYER_RESTART_FILENAME, PAUSE_LAYER_RESTART_CLICKED_FILENAME, PAUSE_LAYER_RESTART_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> restartTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
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

                                auto blacken = CallFuncN::create([](Node* node){
                                    auto black = Sprite::create(PAUSE_LAYER_FORE_FILENAME);
                                    black->setOpacity(0);
                                    auto fadeIn = FadeTo::create(0.5f, 255);
                                    black->runAction(fadeIn);
                                    black->setAnchorPoint(Vec2(0.0f, 0.0f));
                                    node->addChild(black);
                                    black->setGlobalZOrder(12.5f);
                                });

                                auto delay = DelayTime::create(0.5f);

                                auto changeScene = CallFunc::create([this](){
                                    return [&](){
                                        auto scene = GameScene::create(this->level->getLevelId());
                                        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
                                    };
                                }());

                                auto seq = Sequence::create(blacken, delay, changeScene, nullptr);
                                this->runAction(seq);
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
    
    restart->addTouchEventListener(restartTouch());
    this->addChild(restart);
    restart->setGlobalZOrder(12.0f);
    restart->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 45.0f + 15.0f));

    // Add mainmenu button
    auto mainmenu = ui::Button::create(PAUSE_LAYER_MAINMENU_FILENAME, PAUSE_LAYER_MAINMENU_CLICKED_FILENAME, PAUSE_LAYER_MAINMENU_CLICKED_FILENAME);
    
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> mainmenuTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
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
                                auto blacken = CallFuncN::create([](Node* node){
                                    auto black = Sprite::create(PAUSE_LAYER_FORE_FILENAME);
                                    black->setOpacity(0);
                                    auto fadeIn = FadeTo::create(0.5f, 255);
                                    black->runAction(fadeIn);
                                    black->setAnchorPoint(Vec2(0.0f, 0.0f));
                                    node->addChild(black);
                                    black->setGlobalZOrder(12.5f);
                                });

                                auto delay = DelayTime::create(0.5f);

                                auto changeScene = CallFunc::create([this](){
                                    return [&](){
                                        auto scene = levelScene::create();
                                        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
                                    };
                                }());

                                auto seq = Sequence::create(blacken, delay, changeScene, nullptr);
                                this->runAction(seq);
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
    
    mainmenu->addTouchEventListener(mainmenuTouch());
    this->addChild(mainmenu);
    mainmenu->setGlobalZOrder(12.0f);
    mainmenu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // Add music slider
    auto music = Sprite::create(PAUSE_LAYER_MUSIC_FILENAME);
    this->addChild(music);
    music->setGlobalZOrder(12.0f);
    music->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height / 2 + origin.y - 45.0f - 15.0f));

    auto music_base = Sprite::create(PAUSE_LAYER_SLIDER_BASE_FILENAME);
    this->addChild(music_base);
    music_base->setGlobalZOrder(12.0f);
    music_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height / 2 + origin.y - 45.0f - 15.0f));

    auto music_volume = UserDefault::getInstance()->getFloatForKey("MUSIC_VOLUME", 1.0f);

    music_slider = Sprite::create(PAUSE_LAYER_SLIDER_FILENAME);
    this->addChild(music_slider);
    music_slider->setGlobalZOrder(12.0f);
    music_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f - (1.0f - music_volume) * 150.0f, visibleSize.height / 2 + origin.y - 45.0f - 15.0f));

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
    auto effect = Sprite::create(PAUSE_LAYER_EFFECT_FILENAME);
    this->addChild(effect);
    effect->setGlobalZOrder(12.0f);
    effect->setPosition(Vec2(visibleSize.width / 2 + origin.x - 87.5f, visibleSize.height / 2 + origin.y - 45.0f * 2 - 15.0f * 2));

    auto effect_base = Sprite::create(PAUSE_LAYER_SLIDER_BASE_FILENAME);
    this->addChild(effect_base);
    effect_base->setGlobalZOrder(12.0f);
    effect_base->setPosition(Vec2(visibleSize.width / 2 + origin.x + 35.0f, visibleSize.height / 2 + origin.y - 45.0f * 2 - 15.0f * 2));

    auto effect_volume = UserDefault::getInstance()->getFloatForKey("EFFECT_VOLUME", 1.0f);

    effect_slider = Sprite::create(PAUSE_LAYER_SLIDER_FILENAME);
    this->addChild(effect_slider);
    effect_slider->setGlobalZOrder(12.0f);
    effect_slider->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110.0f - (1.0f - effect_volume) * 150.0f, visibleSize.height / 2 + origin.y - 45.0f * 2 - 15.0f * 2));

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
}