#ifndef __CELL_05_PROJECTILE_MODEL_H__
#define __CELL_05_PROJECTILE_MODEL_H__

class ProjectileModel;
class CharacterModel;

class Cell05ProjectileModel : public ProjectileModel {
public:
    Cell05ProjectileModel(CellModel*, DiseaseModel*);
    virtual ~Cell05ProjectileModel(){}
    virtual void hitTarget();
protected:
    double distance;
};

#endif // ! __CELL_05_PROJECTILE_MODEL_H__