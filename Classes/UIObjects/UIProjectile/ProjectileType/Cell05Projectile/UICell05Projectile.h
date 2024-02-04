#ifndef __UI_CELL_05_PROJECTILE_H__
#define __UI_CELL_05_PROJECTILE_H__

#define CELL_05_DESTROY_FILENAME "sprites/objects/projectile/cell_05_projectile_destroy.png"
#define CELL_05_AFTERMATH_FILENAME "sprites/objects/projectile/cell_05_projectile_aftermath.png"

class UIProjectile;
class UICell05Projectile : public UIProjectile {
public:
    static UICell05Projectile* create();
    virtual void idleAnimate();
    virtual void destroyAnimate();
};

#endif // !__UI_CELL_05_PROJECTILE_H__