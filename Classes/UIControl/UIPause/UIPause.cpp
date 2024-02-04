#include "UIPause.h"
#include "Models/models.h"
#include "UIControl/UIPauseLayer/UIPauseLayer.h"
#include "SimpleAudioEngine.h"
#include <functional>
using namespace std;
using namespace CocosDenshion;

UIPause* UIPause::create(LevelModel* level) {
	UIPause *btn = new (std::nothrow) UIPause;
	if (btn && btn->init(PAUSE_BUTTON_FILENAME, PAUSE_BUTTON_CLICKED_FILENAME, PAUSE_BUTTON_CLICKED_FILENAME))
	{
		btn->level = level;
        btn->setScale(1.2f);
		btn->autorelease();
        btn->onTouch();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

void UIPause::onTouch() {
    function<function<void(Ref*, ui::Widget::TouchEventType)>()> pauseTouch = [this]() -> function<void(Ref*, ui::Widget::TouchEventType)> {
        return [&](Ref *sender, ui::Widget::TouchEventType type){
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("Touch pause");
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCLOG("Pause!");
                SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/button.mp3");
                level->pause();
                auto pauseLayer = UIPauseLayer::create(level);
                getParent()->addChild(pauseLayer, 12);
                pauseLayer->setGlobalZOrder(12.0f);
                break;
            }
            default:
                break;
            }
        };
    };

	this->addTouchEventListener(pauseTouch());
}