#ifndef __CELL_03_PROJECTILE_MODEL_H__
#define __CELL_03_PROJECTILE_MODEL_H__

class ProjectileModel;
class CharacterModel;

class Cell03ProjectileModel : public ProjectileModel {
public:
    Cell03ProjectileModel(CellModel*, DiseaseModel*);
    virtual ~Cell03ProjectileModel(){}
protected:
};

#endif // ! __CELL_03_PROJECTILE_MODEL_H__