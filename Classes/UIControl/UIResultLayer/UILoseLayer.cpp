#include "UILoseLayer.h"
#include "Models/models.h"
#include "UIControl/UITextLayer/UITextGeneralLayer.h"
#include <functional>
#include "Scenes/GameScene/GameScene.h"
#include "Scenes/MainMenuScene/MainMenuScene.h"
#include "Scenes/LevelScene/LevelScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

UILoseLayer* UILoseLayer::create(LevelModel* level) {
    UILoseLayer *ret = new (std::nothrow) UILoseLayer;
    if (ret && ret->init(level))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool UILoseLayer::init(LevelModel* level) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    this->level = level;

    // Flash upon
    auto flashing = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
    
        auto flash = Sprite::create(FLASH_FILENAME);
        flash->setOpacity(0);
        auto fadeIn = FadeTo::create(0.1f, 255);
        auto fadeOut = FadeTo::create(0.1f, 0);
        auto remove = RemoveSelf::create();
        auto sequence = Sequence::create(fadeIn, fadeOut, remove, nullptr);
        node->addChild(flash);
        flash->setGlobalZOrder(12.0f);
        flash->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        flash->runAction(sequence);
    });

    auto delay1 = DelayTime::create(0.5f);

    // Appear foreground
    auto foring = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto fore = Sprite::create(FORE_FILENAME);
        fore->setOpacity(0);
        auto fadeIn = FadeTo::create(0.5f, 160);
        node->addChild(fore);
        fore->setGlobalZOrder(12.0f);
        fore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        fore->runAction(fadeIn);
    });

    // Appear victory text
    auto lose = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto victory = Sprite::create(LOSE_FILENAME);
        victory->setOpacity(0);
        victory->setScale(0.75f);

        node->addChild(victory, 1);
        victory->setGlobalZOrder(12.0f);
        victory->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        
        auto fadeIn = FadeTo::create(2.5f, 255);
        auto scaleIn = ScaleTo::create(2.5f, 1.0f);
        auto delay = DelayTime::create(2.0f);
        auto fadeOut = FadeTo::create(2.0f, 0);
        auto remove = RemoveSelf::create();

        auto sequence = Sequence::create(fadeIn, delay, fadeOut, remove, nullptr);

        victory->runAction(scaleIn);
        victory->runAction(sequence);        
    });

    auto delay2 = DelayTime::create(6.0f);

    // Appear lose message
    auto message = CallFunc::create([this](){
        return [&](){
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            auto message = UITextGeneralLayer::create(TEXT_LOSE_FILENAME, MAIN_MENU_BUTTON_FILENAME, MAIN_MENU_BUTTON_CLICKED_FILENAME, RESTART_BUTTON_FILENAME, RESTART_BUTTON_CLICKED_FILENAME, false);
            this->addChild(message);
            message->setPositionY(0.0f - visibleSize.height / 2);
            auto jump = JumpBy::create(0.5f, Vec2(0.0f, visibleSize.height / 2), visibleSize.height / 4, 1);
            message->runAction(jump);

            // Restart button
            function<function<void(Ref*, ui::Widget::TouchEventType)>()> restartTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
                return [&](Ref* sender, ui::Widget::TouchEventType type) {
                    if (type == ui::Widget::TouchEventType::ENDED) {
                        SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                        auto blacken = CallFuncN::create([](Node* node){
                            auto black = Sprite::create(FORE_FILENAME);
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

            // Main menu button
            function<function<void(Ref*, ui::Widget::TouchEventType)>()> mainmenuTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
                return [&](Ref* sender, ui::Widget::TouchEventType type) {
                    if (type == ui::Widget::TouchEventType::ENDED) {
                        SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                        auto blacken = CallFuncN::create([](Node* node){
                            auto black = Sprite::create(FORE_FILENAME);
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

            message->setButtonRightTouch(restartTouch());
            message->setButtonLeftTouch(mainmenuTouch());
        };
    }());

    // Finalize
    auto seq = Sequence::create(flashing, delay1, foring, lose, delay2, message, nullptr);
    this->runAction(seq);
    
    return true;
}