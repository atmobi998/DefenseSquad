#include "UIObjects.h"
#include "Scenes/GameScene/GSDefine.h"
#include <cmath>
using namespace std;
USING_NS_CC;

/*
Convert from cell position to screen position
*/
void UIObjects::setCellPosition(double cellX, double cellY) {
    setPosition(cellX * CELL_WIDTH + POS_X_ORIGIN, cellY * CELL_WIDTH + POS_Y_ORIGIN);
    setGlobalZOrder(2.0f + 5.0f - cellY / 5.0f);

	//setPosition(GRASS_POSITION_LEFT + SIZE_OF_SQUARE * cellX + SIZE_OF_SQUARE / 2, GRASS_POSITION_BOTTOM + SIZE_OF_SQUARE * (cellY + 1) - SIZE_OF_SQUARE / 2);
}

/*
Add UIObjects to Scene
*/
void UIObjects::addToScene(Scene* scene) {
    scene->addChild(this);
    this->shadow->setOpacity(160);
}

/*
Remove UIObjects from Scene
*/
void UIObjects::removeFromScene() {
    removeFromParent();
}

/*
Set UIObject frozen
*/
void UIObjects::setFrozenAnimate() {
    Node* tempParent = Node::create();

    // Add temporary parent to scene
    auto tempPos = this->getPosition();
    this->getParent()->addChild(tempParent, 3);
    tempParent->setPosition(tempPos.x, tempPos.y);
    this->removeFromParentAndCleanup(false);
    tempParent->addChild(this);
    this->setPosition(0.0f, 0.0f);
    this->setLocalZOrder(3);
    this->setColor(Color3B(0, 162, 232));
    this->shadow->pause();
    this->pause();
    tempParent->pause();
}

/*
Defreeze the UIObject
*/
void UIObjects::deFrozenAnimate() {
    Node* tempParent = this->getParent();

    // Change parent to scene
    auto tempPos = tempParent->getPosition();
    this->removeFromParentAndCleanup(false);
    tempParent->getParent()->addChild(this, 3);
    this->setPosition(tempPos.x, tempPos.y);
    this->setColor(Color3B(255, 255, 255));
    this->resume();
    this->shadow->resume();
    tempParent->removeFromParent();
}