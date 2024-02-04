#include "TemplateScene.h"
#include "TemplateSceneDefinitions.h"
#include "Components/TemplateComponent/TemplateComponent.h"

USING_NS_CC;

Scene* TemplateScene::createScene()
{
    return TemplateScene::create();
}

// on "init" you need to initialize your instance
bool TemplateScene::init()
{
    // Super init
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
}