#include "UIWinLayer.h"
#include "Models/models.h"
#include "UIRewardLayer.h"
#include "Scenes/GameScene/GameScene.h"
#include "Scenes/LevelScene/LevelScene.h"
#include "UIControl/UITextLayer/UITextGeneralLayer.h"
#include "UIControl/UITextLayer/UITextSingleLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

UIWinLayer* UIWinLayer::create(LevelModel* level) {
    UIWinLayer *ret = new (std::nothrow) UIWinLayer;
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

bool UIWinLayer::init(LevelModel* level) {
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
    auto victory = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto victory = Sprite::create(VICTORY_FILENAME);
        victory->setOpacity(0);
        victory->setScale(3.0f);

        node->addChild(victory, 1);
        victory->setGlobalZOrder(12.0f);
        victory->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        
        auto fadeIn = FadeTo::create(0.15f, 255);
        auto scaleIn = ScaleTo::create(0.3f, 1.0f);
        auto delay = DelayTime::create(1.0f);
        auto fadeOut = FadeTo::create(1.0f, 0);
        auto remove = RemoveSelf::create();

        auto sequence = Sequence::create(fadeIn, delay, fadeOut, remove, nullptr);

        victory->runAction(scaleIn);
        victory->runAction(sequence);        
    });

    auto delay2 = DelayTime::create(0.3f);

    // Appear stars
    auto stars = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        for (int j = 0; j < 100; j++) {
            auto star = Sprite::create(STAR_FILENAME);
            auto scale = CCRANDOM_0_1() * 0.85f + 0.15f;
            star->setScale(scale);
            
            auto time = CCRANDOM_0_1() * 1.0f + 1.0f;
            auto rotate = RotateBy::create(time + 0.5f, CCRANDOM_MINUS1_1() * 720.0f);
            
            auto jump = JumpBy::create(time + 0.5f, Vec2(CCRANDOM_MINUS1_1() * 1.5f * visibleSize.width / 2, CCRANDOM_MINUS1_1() * 1.5f * visibleSize.height / 2), (CCRANDOM_0_1() * 0.5f + 0.5f) * visibleSize.height / 10, 1);
            
            auto delay = DelayTime::create(time);
            auto fadeOut = FadeTo::create(0.5f, 0);
            auto remove = RemoveSelf::create();
            auto seq = Sequence::create(delay, fadeOut, remove, nullptr);

            node->addChild(star);
            star->setGlobalZOrder(12.0f);
            star->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
            star->runAction(rotate);
            star->runAction(jump);
            star->runAction(seq);
        }
    });

    auto delay3 = DelayTime::create(2.0f);

    // Appear win message
    this->callMessage = [this](){
        return [&](){
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            // Nextlevel button
            function<function<void(Ref*, ui::Widget::TouchEventType)>()> nextTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
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
                                auto scene = GameScene::create(this->level->getLevelId() + 1);
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

            if (this->level->getLevelId() < 8 && this->level->getLevelId() == UserDefault::getInstance()->getIntegerForKey("CURRENT_LEVEL", 1) - 1) {
                auto message = UITextGeneralLayer::create(TEXT_WIN_FILENAME, MAIN_MENU_BUTTON_FILENAME, MAIN_MENU_BUTTON_CLICKED_FILENAME, NEXT_LEVEL_BUTTON_FILENAME, NEXT_LEVEL_BUTTON_CLICKED_FILENAME, false);
                this->addChild(message);
                message->setPositionY(0.0f - visibleSize.height / 2);
                auto jump = JumpBy::create(0.5f, Vec2(0.0f, visibleSize.height / 2), visibleSize.height / 4, 1);
                message->runAction(jump);

                message->setButtonRightTouch(nextTouch());
                message->setButtonLeftTouch(mainmenuTouch());
            }
            else if (this->level->getLevelId() < 8 && this->level->getLevelId() != UserDefault::getInstance()->getIntegerForKey("CURRENT_LEVEL", 1) - 1) {
                auto message = UITextSingleLayer::create(TEXT_WIN_FILENAME, MAIN_MENU_BUTTON_FILENAME, MAIN_MENU_BUTTON_CLICKED_FILENAME, false);
                this->addChild(message);
                message->setPositionY(0.0f - visibleSize.height / 2);
                auto jump = JumpBy::create(0.5f, Vec2(0.0f, visibleSize.height / 2), visibleSize.height / 4, 1);
                message->runAction(jump);
                message->setButtonTouch(mainmenuTouch());
            }
            else {
                auto message = UITextSingleLayer::create(TEXT_COMPLETE_FILENAME, MAIN_MENU_BUTTON_FILENAME, MAIN_MENU_BUTTON_CLICKED_FILENAME, false);
                this->addChild(message);
                message->setPositionY(0.0f - visibleSize.height / 2);
                auto jump = JumpBy::create(0.5f, Vec2(0.0f, visibleSize.height / 2), visibleSize.height / 4, 1);
                message->runAction(jump);
                message->setButtonTouch(mainmenuTouch());
            }
        };
    }();

    auto message = CallFunc::create(this->callMessage);

    // Appear reward message
    auto reward = CallFunc::create([this](){
        return [&](){
            SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/reward.mp3");

            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto origin = Director::getInstance()->getVisibleOrigin();

            this->rewardLayer = UIRewardLayer::create((CellId) this->level->getReward(), [this](){
                return [&](Ref*, ui::Widget::TouchEventType type){
                    if (type == ui::Widget::TouchEventType::ENDED) {
                        SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                        auto visibleSize = Director::getInstance()->getVisibleSize();
                        auto origin = Director::getInstance()->getVisibleOrigin();

                        auto move = MoveBy::create(0.5f, Vec2(0.0f, visibleSize.height));
                        auto remove = RemoveSelf::create();
                        auto seq = Sequence::create(move, remove, nullptr);
                        this->rewardLayer->runAction(seq);
                        this->callMessage();
                    }
                };
            }());

            this->addChild(this->rewardLayer);
            this->rewardLayer->setPositionY(0.0f - visibleSize.height / 2);
            auto jump = JumpBy::create(0.5f, Vec2(0.0f, visibleSize.height / 2), visibleSize.height / 4, 1);
            this->rewardLayer->runAction(jump);
        };
    }());

    // Finalize
    auto data = UserDefault::getInstance();
    auto currentLevel = data->getIntegerForKey("CURRENT_LEVEL", 1);
    auto currentCell = data->getIntegerForKey("CURRENT_CELL", 0);
    auto rewardCell = level->getReward();

    if (rewardCell != -1 && rewardCell > currentCell) {
        auto seq = Sequence::create(flashing, delay1, foring, victory, delay2, stars, delay3, reward, nullptr);
        this->runAction(seq);
    }
    else {
        auto seq = Sequence::create(flashing, delay1, foring, victory, delay2, stars, delay3, message, nullptr);
        this->runAction(seq);
    }

    if (level->getLevelId() == currentLevel) {
        data->setIntegerForKey("CURRENT_LEVEL", level->getLevelId() + 1);
        data->flush();
    }

    if (rewardCell != -1 && rewardCell > currentCell) {
        data->setIntegerForKey("CURRENT_CELL", rewardCell);
        data->flush();
    }
    
    return true;
}