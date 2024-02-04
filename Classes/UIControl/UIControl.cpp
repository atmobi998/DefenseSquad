#include "UIControl.h"
#include "Scenes/GameScene/GSDefine.h"
USING_NS_CC;

/*
Add to Scene
*/
void UIControl::addToScene(Scene* scene) {
    scene->addChild(this);
}

/*
Remove from Scene
*/
void UIControl::removeFromScene() {
    removeFromParent();
}
