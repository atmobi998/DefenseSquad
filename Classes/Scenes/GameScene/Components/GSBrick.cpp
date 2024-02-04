#define BRICK_FILE_NAME "sprites/MapLayer/brick.png"
#define BRICK_EMPTY_FILE_NAME "sprites/MapLayer/empty.png"
#include "GSBrick.h"
#include <functional>
USING_NS_CC;

/*
Create method
*/
GSBrick* GSBrick::create() {
    GSBrick *sprite = new (std::nothrow) GSBrick;
    if (sprite && sprite->initWithFile(BRICK_EMPTY_FILE_NAME))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

/*
Create pieces
*/
Sprite* GSBrick::createPiece(int piece) {
    auto rect = [piece]() -> Rect {
        auto row = 4 - (piece - 1) / 3;
        auto col = 0 + (piece - 1) % 3;
        return Rect(32.0f * col, 32.0f * row, 32.0f, 32.0f);
    }();

    return Sprite::create(BRICK_FILE_NAME, rect);
}

/*
Put pieces into places
*/
void GSBrick::putPiecesIntoPlace(bool left, bool right, bool up, bool down) {
    std::function<void(Sprite*)> reSizeWithBrick = [this](Sprite* sprite) {
        sprite->setContentSize(this->getContentSize() / 3);
    };
    auto width = this->getContentSize().width;

    // In the center
    auto centerPiece = createPiece(5);
    reSizeWithBrick(centerPiece);
    centerPiece->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(centerPiece);
    centerPiece->setGlobalZOrder(0.5f);
    centerPiece->setPosition(width / 3, width / 3);

    // The 4 edges
    // Left side
    Sprite* leftPiece;
    if (left) leftPiece = createPiece(5);
    else leftPiece = createPiece(4);
    reSizeWithBrick(leftPiece);
    leftPiece->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(leftPiece);
    leftPiece->setGlobalZOrder(0.5f);
    leftPiece->setPosition(0.0f, width / 3);
    // Right side
    Sprite* rightPiece;
    if (right) rightPiece = createPiece(5);
    else rightPiece = createPiece(6);
    reSizeWithBrick(rightPiece);
    rightPiece->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(rightPiece);
    rightPiece->setGlobalZOrder(0.5f);
    rightPiece->setPosition(width * 2 / 3, width / 3);
    // Up side
    Sprite* upPiece;
    if (up) upPiece = createPiece(5);
    else upPiece = createPiece(8);
    reSizeWithBrick(upPiece);
    upPiece->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(upPiece);
    upPiece->setGlobalZOrder(0.5f);
    upPiece->setPosition(width / 3, width * 2 / 3);
    // Down side
    Sprite* downPiece;
    if (down) downPiece = createPiece(5);
    else downPiece = createPiece(2);
    reSizeWithBrick(downPiece);
    downPiece->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(downPiece);
    downPiece->setGlobalZOrder(0.5f);
    downPiece->setPosition(width / 3, 0.0f);

    // Four corners
    // Upper left
    Sprite* upperLeft;
    if (up && left) upperLeft = createPiece(13);
    else if (!up && left) upperLeft = createPiece(8);
    else if (up && !left) upperLeft = createPiece(4);
    else upperLeft = createPiece(7);
    reSizeWithBrick(upperLeft);
    upperLeft->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(upperLeft);
    upperLeft->setGlobalZOrder(0.5f);
    upperLeft->setPosition(0.0f, width * 2 / 3);
    // Upper right
    Sprite* upperRight;
    if (up && right) upperRight = createPiece(14);
    else if (!up && right) upperRight = createPiece(8);
    else if (up && !right) upperRight = createPiece(6);
    else upperRight = createPiece(9);
    reSizeWithBrick(upperRight);
    upperRight->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(upperRight);
    upperRight->setGlobalZOrder(0.5f);
    upperRight->setPosition(width * 2 / 3, width * 2 / 3);
    // Lower left
    Sprite* lowerLeft;
    if (down && left) lowerLeft = createPiece(10);
    else if (!down && left) lowerLeft = createPiece(2);
    else if (down && !left) lowerLeft = createPiece(4);
    else lowerLeft = createPiece(1);
    reSizeWithBrick(lowerLeft);
    lowerLeft->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(lowerLeft);
    lowerLeft->setGlobalZOrder(0.5f);
    lowerLeft->setPosition(0.0f, 0.0f);
    // Lower right
    Sprite* lowerRight;
    if (down && right) lowerRight = createPiece(11);
    else if (!down && right) lowerRight = createPiece(2);
    else if (down && !right) lowerRight = createPiece(6);
    else lowerRight = createPiece(3);
    reSizeWithBrick(lowerRight);
    lowerRight->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(lowerRight);
    lowerRight->setGlobalZOrder(0.5f);
    lowerRight->setPosition(width * 2 / 3, 0.0f);
}