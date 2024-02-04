#include "GSTutorial.h"
// #include <functional>
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

GSTutorial* GSTutorial::create(Rect rect, string filename) {
    GSTutorial *ret = new (std::nothrow) GSTutorial;
    if (ret)
    {
        ret->initWithOneRect(rect, filename);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

GSTutorial* GSTutorial::create(Rect rect1, Rect rect2, string filename) {
    GSTutorial *ret = new (std::nothrow) GSTutorial;
    if (ret)
    {
        ret->initWithTwoRect(rect1, rect2, filename);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool GSTutorial::initWithOneRect(Rect rect, string filename) {
    Layer::init();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Create black around
    Sprite* up = Sprite::create(TUTORIAL_FORE);
    up->setOpacity(180);
    up->setAnchorPoint(Vec2(0.5f, 0.0f));
    up->setScaleX(visibleSize.width * 1.5f / up->getContentSize().width);
    up->setScaleY(visibleSize.height * 1.5f / up->getContentSize().height);
    this->addChild(up);
    up->setGlobalZOrder(13.0f);
    up->setPosition(visibleSize.width / 2 + origin.x, rect.getMaxY());

    Sprite* down = Sprite::create(TUTORIAL_FORE);
    down->setOpacity(180);
    down->setAnchorPoint(Vec2(0.5f, 1.0f));
    down->setScaleX(visibleSize.width * 1.5f / down->getContentSize().width);
    down->setScaleY(visibleSize.height * 1.5f / down->getContentSize().height);
    this->addChild(down);
    down->setGlobalZOrder(13.0f);
    down->setPosition(visibleSize.width / 2 + origin.x, rect.getMinY());
    
    Sprite* left = Sprite::create(TUTORIAL_FORE);
    left->setOpacity(180);
    left->setAnchorPoint(Vec2(1.0f, 0.0f));
    left->setScaleX(visibleSize.width * 1.5f / left->getContentSize().width);
    left->setScaleY((rect.getMaxY() - rect.getMinY()) / left->getContentSize().height);
    this->addChild(left);
    left->setGlobalZOrder(13.0f);
    left->setPosition(rect.getMinX(), rect.getMinY());

    Sprite* right = Sprite::create(TUTORIAL_FORE);
    right->setOpacity(180);
    right->setAnchorPoint(Vec2(0.0f, 0.0f));
    right->setScaleX(visibleSize.width * 1.5f / right->getContentSize().width);
    right->setScaleY((rect.getMaxY() - rect.getMinY()) / right->getContentSize().height);
    this->addChild(right);
    right->setGlobalZOrder(13.0f);
    right->setPosition(rect.getMaxX(), rect.getMinY());

    // Create tutorial
    auto text = Sprite::create(filename);
    text->setScale(0.9f * visibleSize.width / text->getContentSize().width);
    this->addChild(text);
    text->setGlobalZOrder(13.0f);
    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Create button
    button = ui::Button::create(TUTORIAL_OKAY, TUTORIAL_OKAY_CLICKED, TUTORIAL_OKAY_CLICKED);
    button->setScale(1.25f);
    this->addChild(button);
    button->setGlobalZOrder(13.0f);
    button->setPosition(Vec2(visibleSize.width - 113.75f + origin.x, 44.5f + origin.y));

    return true;
}

bool GSTutorial::initWithTwoRect(Rect rect1, Rect rect2, string filename) {
    Layer::init();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Create black around
    if (rect1.getMaxX() <= rect2.getMinX() || rect2.getMaxX() <= rect1.getMinX()) {
        Rect rectLeft, rectRight;
        if (rect1.getMaxX() <= rect2.getMinX()) {
            rectLeft = rect1;
            rectRight = rect2;
        } else {
            rectRight = rect1;
            rectLeft = rect2;
        }

        Sprite* left = Sprite::create(TUTORIAL_FORE);
        left->setOpacity(180);
        left->setAnchorPoint(Vec2(1.0f, 0.5f));
        left->setScaleX(visibleSize.width * 1.5f / left->getContentSize().width);
        left->setScaleY(visibleSize.height * 1.5f / left->getContentSize().height);
        this->addChild(left);
        left->setGlobalZOrder(13.0f);
        left->setPosition(rectLeft.getMinX(), visibleSize.height / 2 + origin.y);

        Sprite* right = Sprite::create(TUTORIAL_FORE);
        right->setOpacity(180);
        right->setAnchorPoint(Vec2(0.0f, 0.5f));
        right->setScaleX(visibleSize.width * 1.5f / right->getContentSize().width);
        right->setScaleY(visibleSize.height * 1.5f / right->getContentSize().height);
        this->addChild(right);
        right->setGlobalZOrder(13.0f);
        right->setPosition(rectRight.getMaxX(), visibleSize.height / 2 + origin.y);

        if (rectLeft.getMaxX() < rectRight.getMinX()) {
            Sprite* middle = Sprite::create(TUTORIAL_FORE);
            middle->setOpacity(180);
            middle->setAnchorPoint(Vec2(0.0f, 0.5f));
            middle->setScaleX((rectRight.getMinX() - rectLeft.getMaxX()) / middle->getContentSize().width);
            middle->setScaleY(visibleSize.height * 1.5f / middle->getContentSize().height);
            this->addChild(middle);
            middle->setGlobalZOrder(13.0f);
            middle->setPosition(rectLeft.getMaxX(), visibleSize.height / 2 + origin.y);
        }

        Sprite* upLeft = Sprite::create(TUTORIAL_FORE);
        upLeft->setOpacity(180);
        upLeft->setAnchorPoint(Vec2(0.0f, 0.0f));
        upLeft->setScaleX((rectLeft.getMaxX() - rectLeft.getMinX()) / upLeft->getContentSize().width);
        upLeft->setScaleY(visibleSize.height * 1.5f / upLeft->getContentSize().height);
        this->addChild(upLeft);
        upLeft->setGlobalZOrder(13.0f);
        upLeft->setPosition(rectLeft.getMinX(), rectLeft.getMaxY());

        Sprite* upRight = Sprite::create(TUTORIAL_FORE);
        upRight->setOpacity(180);
        upRight->setAnchorPoint(Vec2(0.0f, 0.0f));
        upRight->setScaleX((rectRight.getMaxX() - rectRight.getMinX()) / upRight->getContentSize().width);
        upRight->setScaleY(visibleSize.height * 1.5f / upRight->getContentSize().height);
        this->addChild(upRight);
        upRight->setGlobalZOrder(13.0f);
        upRight->setPosition(rectRight.getMinX(), rectRight.getMaxY());

        Sprite* downLeft = Sprite::create(TUTORIAL_FORE);
        downLeft->setOpacity(180);
        downLeft->setAnchorPoint(Vec2(0.0f, 1.0f));
        downLeft->setScaleX((rectLeft.getMaxX() - rectLeft.getMinX()) / downLeft->getContentSize().width);
        downLeft->setScaleY(visibleSize.height * 1.5f / downLeft->getContentSize().height);
        this->addChild(downLeft);
        downLeft->setGlobalZOrder(13.0f);
        downLeft->setPosition(rectLeft.getMinX(), rectLeft.getMinY());

        Sprite* downRight = Sprite::create(TUTORIAL_FORE);
        downRight->setOpacity(180);
        downRight->setAnchorPoint(Vec2(0.0f, 1.0f));
        downRight->setScaleX((rectRight.getMaxX() - rectRight.getMinX()) / downRight->getContentSize().width);
        downRight->setScaleY(visibleSize.height * 1.5f / downRight->getContentSize().height);
        this->addChild(downRight);
        downRight->setGlobalZOrder(13.0f);
        downRight->setPosition(rectRight.getMinX(), rectRight.getMinY());
    }
    else {
        Rect rectUp, rectDown;
        if (rect1.getMinY() >= rect2.getMaxY()) {
            rectUp = rect1;
            rectDown = rect2;
        } else {
            rectDown = rect1;
            rectUp = rect2;
        }

        Sprite* up = Sprite::create(TUTORIAL_FORE);
        up->setOpacity(180);
        up->setAnchorPoint(Vec2(0.5f, 0.0f));
        up->setScaleX(visibleSize.width * 1.5f / up->getContentSize().width);
        up->setScaleY(visibleSize.height * 1.5f / up->getContentSize().height);
        this->addChild(up);
        up->setGlobalZOrder(13.0f);
        up->setPosition(visibleSize.width / 2 + origin.x, rectUp.getMaxY());

        Sprite* down = Sprite::create(TUTORIAL_FORE);
        down->setOpacity(180);
        down->setAnchorPoint(Vec2(0.5f, 1.0f));
        down->setScaleX(visibleSize.width * 1.5f / down->getContentSize().width);
        down->setScaleY(visibleSize.height * 1.5f / down->getContentSize().height);
        this->addChild(down);
        down->setGlobalZOrder(13.0f);
        down->setPosition(visibleSize.width / 2 + origin.x, rectDown.getMinY());

        if (rectUp.getMinY() != rectDown.getMaxY()) {
            Sprite* middle = Sprite::create(TUTORIAL_FORE);
            middle->setOpacity(180);
            middle->setAnchorPoint(Vec2(0.5f, 1.0f));
            middle->setScaleX(visibleSize.width * 1.5f / middle->getContentSize().width);
            middle->setScaleY((rectUp.getMinY() - rectDown.getMaxY()) / middle->getContentSize().height);
            this->addChild(middle);
            middle->setGlobalZOrder(13.0f);
            middle->setPosition(visibleSize.width / 2 + origin.x, rectUp.getMinY());
        }

        Sprite* leftUp = Sprite::create(TUTORIAL_FORE);
        leftUp->setOpacity(180);
        leftUp->setAnchorPoint(Vec2(1.0f, 0.0f));
        leftUp->setScaleX(visibleSize.width * 1.5f / leftUp->getContentSize().width);
        leftUp->setScaleY((rectUp.getMaxY() - rectUp.getMinY()) / leftUp->getContentSize().height);
        this->addChild(leftUp);
        leftUp->setGlobalZOrder(13.0f);
        leftUp->setPosition(rectUp.getMinX(), rectUp.getMinY());

        Sprite* rightUp = Sprite::create(TUTORIAL_FORE);
        rightUp->setOpacity(180);
        rightUp->setAnchorPoint(Vec2(0.0f, 0.0f));
        rightUp->setScaleX(visibleSize.width * 1.5f / rightUp->getContentSize().width);
        rightUp->setScaleY((rectUp.getMaxY() - rectUp.getMinY()) / rightUp->getContentSize().height);
        this->addChild(rightUp);
        rightUp->setGlobalZOrder(13.0f);
        rightUp->setPosition(rectUp.getMaxX(), rectUp.getMinY());

        Sprite* leftDown = Sprite::create(TUTORIAL_FORE);
        leftDown->setOpacity(180);
        leftDown->setAnchorPoint(Vec2(1.0f, 0.0f));
        leftDown->setScaleX(visibleSize.width * 1.5f / leftDown->getContentSize().width);
        leftDown->setScaleY((rectDown.getMaxY() - rectDown.getMinY()) / leftDown->getContentSize().height);
        this->addChild(leftDown);
        leftDown->setGlobalZOrder(13.0f);
        leftDown->setPosition(rectDown.getMinX(), rectDown.getMinY());

        Sprite* rightDown = Sprite::create(TUTORIAL_FORE);
        rightDown->setOpacity(180);
        rightDown->setAnchorPoint(Vec2(0.0f, 0.0f));
        rightDown->setScaleX(visibleSize.width * 1.5f / rightDown->getContentSize().width);
        rightDown->setScaleY((rectDown.getMaxY() - rectDown.getMinY()) / rightDown->getContentSize().height);
        this->addChild(rightDown);
        rightDown->setGlobalZOrder(13.0f);
        rightDown->setPosition(rectDown.getMaxX(), rectDown.getMinY());
    }

    // Create tutorial
    auto text = Sprite::create(filename);
    text->setScale(0.9f * visibleSize.width / text->getContentSize().width);
    this->addChild(text);
    text->setGlobalZOrder(13.0f);
    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Create button
    button = ui::Button::create(TUTORIAL_OKAY, TUTORIAL_OKAY_CLICKED, TUTORIAL_OKAY_CLICKED);
    button->setScale(1.25f);
    this->addChild(button);
    button->setGlobalZOrder(13.0f);
    button->setPosition(Vec2(visibleSize.width - 113.75f + origin.x, 44.5f + origin.y));

    return true;
}

void GSTutorial::setOkayEvent(function<void()> event) {
    this->call = event;

    button->addTouchEventListener([this](){
        return [&](Ref*, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                this->call();
            }
        };
    }());
}