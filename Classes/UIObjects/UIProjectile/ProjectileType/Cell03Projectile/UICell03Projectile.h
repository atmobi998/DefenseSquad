#ifndef __UI_CELL_03_PROJECTILE_H__
#define __UI_CELL_03_PROJECTILE_H__

#define CELL_03_DESTROY_FILENAME "sprites/objects/projectile/cell_03_projectile_destroy.png"

class UIProjectile;
class UICell03Projectile : public UIProjectile {
public:
    static UICell03Projectile* create();
    virtual void idleAnimate();
    virtual void destroyAnimate();
};

#endif // !__UI_CELL_03_PROJECTILE_H__