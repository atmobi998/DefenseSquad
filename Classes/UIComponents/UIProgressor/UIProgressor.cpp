#include "UIProgressor.h"
#include "Models/models.h"
#include <functional>
#include "SimpleAudioEngine.h"

using namespace std;
USING_NS_CC;
using namespace CocosDenshion;

/*
Constructor of UIProgressor
*/
UIProgressor::UIProgressor(vector<WaveModel>* waves) {
    waveList = waves;
    currentWave = 0;
    currentHugeWave = 0;

    // Set up sprite
    auto inside = Sprite::create(PROGRESSOR_INSIDE_FILENAME);
    inside->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(inside);
    inside->setGlobalZOrder(9.0f);

    fill = Sprite::create(PROGRESSOR_FILL_FILENAME);
    fill->setAnchorPoint(Vec2(0.0f, 0.5f));
    fill->setScaleX(0.001f);
    this->addChild(fill);
    fill->setGlobalZOrder(9.0f);

    auto outside = Sprite::create(PROGRESSOR_FILENAME);
    outside->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(outside);
    outside->setGlobalZOrder(9.0f);

    // Set up flag
    for (unsigned int i = 0; i < waveList->size(); i++) {
        if ((*waveList)[i].isHugeWave()) {
            auto flag =  Sprite::create(PROGRESSOR_FLAG_FILENAME);
            flag->setAnchorPoint(Vec2(0.5f, 0.0f));
            flag->setPosition(inside->getContentSize().width * (i + 1) / waveList->size(), 0.0f);
            this->addChild(flag);
            flag->setGlobalZOrder(8.5f);
            flags.push_back(flag);
        }
    }
}

/*
Create a UIProgressor
*/
UIProgressor* UIProgressor::create(vector<WaveModel>* waves) {
    UIProgressor * ret = new (std::nothrow) UIProgressor(waves);
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

/*
Update on each wave
*/
void UIProgressor::updateOnWave() {
    if (currentWave < waveList->size()) {
        // Update fill bar
        auto scale = ScaleTo::create(0.15f, ((float) currentWave + 1.0f) / waveList->size(), 1.0f);
        fill->runAction(scale);

        // Check hugewave
        if ((*waveList)[currentWave].isHugeWave()) {
            // Animate the flag
            auto move = MoveBy::create(0.75f, Vec2(0.0f, flags[currentHugeWave]->getContentSize().height / 2));
            flags[currentHugeWave]->runAction(move);
            
            currentHugeWave++;

            if (getParent() != nullptr)
            {
                auto scene = getParent();

                // Notification hugeWave
                auto noti = Sprite::create(NOTIFICATION_HUGEWAVE_FILENAME);
                noti->setOpacity(0);
                scene->addChild(noti);
                noti->setGlobalZOrder(11.0f);
                noti->setPosition(NOTIFICATION_POS_X, NOTIFICATION_POS_Y);
                auto fadeIn = FadeTo::create(0.3f, 255);
                auto scaleFit = ScaleTo::create(0.3f, NOTIFICATION_HEIGHT / noti->getContentSize().height);
                auto delay = DelayTime::create(1.5f);
                auto fadeOut = FadeTo::create(0.3f, 0);
                
                function< function<void()> (Node*) > final = [](Node* s) -> function<void()> {                  
                    auto scene = s;
                    return [scene](){
                        SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/final_round.mp3");
                        auto noti = Sprite::create((CCRANDOM_0_1() <= 0.2f) ? NOTIFICATION_HUGEWAVE_JOKE_FILENAME : NOTIFICATION_HUGEWAVE_FINAL_FILENAME);
                        noti->setOpacity(0);
                        scene->addChild(noti);
                        noti->setGlobalZOrder(11.0f);
                        noti->setPosition(NOTIFICATION_POS_X, NOTIFICATION_POS_Y);
                        auto fadeIn = FadeTo::create(0.3f, 255);
                        auto scaleFit = ScaleTo::create(0.3f, NOTIFICATION_HEIGHT / noti->getContentSize().height);
                        auto delay = DelayTime::create(1.5f);
                        auto fadeOut = FadeTo::create(0.3f, 0);
                        auto remove = RemoveSelf::create();
                        auto seq = Sequence::create(scaleFit, delay, fadeOut, remove, nullptr);
                        noti->runAction(fadeIn);
                        noti->runAction(seq);
                    };
                };

                auto callFinal = CallFunc::create(final(scene));
                auto remove = RemoveSelf::create();

                auto seq = (currentHugeWave == flags.size()) ? Sequence::create(scaleFit, delay, fadeOut, callFinal, remove, nullptr) :
                    Sequence::create(scaleFit, delay, fadeOut, remove, nullptr);

                noti->runAction(fadeIn);
                noti->runAction(seq);
            }
        }

        currentWave++;
    }
}