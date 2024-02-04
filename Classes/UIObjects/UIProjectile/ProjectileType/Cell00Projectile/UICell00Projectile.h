#ifndef __UI_CELL_00_PROJECTILE_H__
#define __UI_CELL_00_PROJECTILE_H__

#define CELL_00_DESTROY_FILENAME "sprites/objects/projectile/cell_00_projectile_destroy.png"

class UIProjectile;
class UICell00Projectile : public UIProjectile {
public:
    static UICell00Projectile* create();
    virtual void idleAnimate();
    virtual void destroyAnimate();
};

#endif // !__UI_CELL_00_PROJECTILE_H__