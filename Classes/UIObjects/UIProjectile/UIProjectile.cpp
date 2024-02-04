#include "UIObjects/uiobj.h"
#include "UIProjectile.h"
#include "ProjectileType/UIProjectileType.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

/*
Add UIProjectile to scene
*/
void UIProjectile::addToScene(Scene* scene) {
    scene->addChild(this, PROJECTILE_LAYER_ZORDER);
}

/*
Create a new instance of UIProjectile with ProjectileId
*/
UIProjectile* UIProjectile::create(ProjectileId id) {
    switch (id) {
    // Case id 00: Rabies
    case CELL_00_PROJECTILE:
    {
        auto proj = UICell00Projectile::create();
        proj->setScale(1.1f * OBJECT_SCALE, 0.78f * OBJECT_SCALE);
        return proj;
    }
    case CELL_03_PROJECTILE:
    {
        auto proj = UICell03Projectile::create();
        proj->setScale(1.1f * OBJECT_SCALE);
        return proj;
    }
    case CELL_05_PROJECTILE:
    {
        auto proj = UICell05Projectile::create();
        proj->setScale(1.5f * OBJECT_SCALE);
        return proj;
    }
    default:
        return UICell00Projectile::create();
    }
    return nullptr;
}

/*
Destroy animation
*/
void UIProjectile::destroyAnimate() {
    SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/projectile_destroyed.wav");
    removeFromParent();
}

/*
Override parent method
*/
void UIProjectile::setCellPosition(double cellX, double cellY) {
    UIObjects::setCellPosition(cellX, cellY);
    setGlobalZOrder(8.0f);
}