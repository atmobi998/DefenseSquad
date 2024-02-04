#ifndef __PROJECTILE_MODEL_H__
#define __PROJECTILE_MODEL_H__

#include "ProjectileModelDefinitions.h"
class LevelModel;
class CharacterModel;
struct CellPosition;
class UIProjectile;

class ProjectileModel {
protected:
    LevelModel* level;
    ProjectileId id;
    double cellX;
    double cellY;
    double directionVectorX;
    double directionVectorY;
    double targetX;
    double targetY;
    double speed;
    double damage;
    DiseaseModel* target;
    bool isDestroyed;
    virtual void effectOnHit(){};
    UIProjectile* ui;
public:
    static ProjectileModel* create(ProjectileId id, CellModel* source, DiseaseModel* target);
    ProjectileModel(ProjectileId id, CellModel* source, DiseaseModel* target);
    virtual void update();
    virtual double getPositionCellX();
    virtual double getPositionCellY();
    virtual CellPosition getPosition();
    virtual void hitTarget();
    virtual void __setLevel(LevelModel*);
    virtual void setUIObject(UIProjectile* ui);
    // Get ProjectileId
    virtual ProjectileId getProjectileId() {return id;}
};

#endif // !__PROJECTILE_MODEL_H__