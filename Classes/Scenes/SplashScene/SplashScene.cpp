#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "Scenes/MainMenuScene/MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SplashScene::create() {
    SplashScene *ret = new (std::nothrow) SplashScene;
    if (ret && ret->init())
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

bool SplashScene::init() {
    auto appear = CallFuncN::create([](Node* node){
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto splash = Sprite::create(SPLASH_FILENAME);
        splash->setOpacity(0);
        node->addChild(splash);
        splash->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        splash->setScale(visibleSize.width * 2.0f / 3.0f / splash->getContentSize().width);
        auto fadeIn = FadeTo::create(0.5f, 255);
        splash->runAction(fadeIn);
    });

    auto delay1 = DelayTime::create(0.5f);

    auto loadMusic = CallFunc::create([](){
        auto data = UserDefault::getInstance();
        auto audio = SimpleAudioEngine::getInstance();

        // Preload here
        audio->preloadBackgroundMusic("audio/background/GameScene/gamescene.mp3");
        audio->preloadBackgroundMusic("audio/background/GameScene/Boss/boss_appear.mp3");
        audio->preloadBackgroundMusic("audio/background/GameScene/Boss/boss_die.mp3");
        audio->preloadBackgroundMusic("audio/background/GameScene/Lose/lose.mp3");
        audio->preloadBackgroundMusic("audio/background/GameScene/Win/win.mp3");
        audio->preloadBackgroundMusic("audio/background/LevelScene/levelscene.mp3");
        audio->preloadBackgroundMusic("audio/background/MainMenu/mainmenu.mp3");

        audio->preloadEffect("audio/soundfx/use/add_cell.mp3");
        audio->preloadEffect("audio/soundfx/use/button.mp3");
        audio->preloadEffect("audio/soundfx/use/collect_energy.mp3");
        audio->preloadEffect("audio/soundfx/use/delete_button.mp3");
        audio->preloadEffect("audio/soundfx/use/earthquake.mp3");
        audio->preloadEffect("audio/soundfx/use/ember.mp3");
        audio->preloadEffect("audio/soundfx/use/final_round.mp3");
        audio->preloadEffect("audio/soundfx/use/freeze.mp3");
        audio->preloadEffect("audio/soundfx/use/projectile_destroyed.wav");
        audio->preloadEffect("audio/soundfx/use/reward.mp3");
        audio->preloadEffect("audio/soundfx/use/projectile_destroyed.mp3");
        audio->preloadEffect("audio/soundfx/use/disease_hit.mp3");
        audio->preloadEffect("audio/soundfx/use/explosion.mp3");

        audio->setBackgroundMusicVolume(data->getFloatForKey("MUSIC_VOLUME", 1.0f));
        audio->setEffectsVolume(data->getFloatForKey("EFFECT_VOLUME", 1.0f));
    });

    auto delay2 = DelayTime::create(1.5f);

    auto changeScene = CallFunc::create([](){
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainMenuScene::create()));
    });

    auto seq = Sequence::create(appear, delay1, loadMusic, delay2, changeScene, nullptr);

    this->runAction(seq);

    return true;
}