#ifndef __SHOOTING_CELL_MODEL_H__
#define __SHOOTING_CELL_MODEL_H__

class CellModel;
class Shooter;

class ShootingCellModel : public CellModel, public Shooter {
protected:

public:
    ShootingCellModel(CellId cellId, ProjectileId);
    virtual ~ShootingCellModel(){};
    virtual void shoot(DiseaseModel* target);
    virtual void update();
    virtual bool canPutOn(LevelModel*, int cellX, int cellY);
};

#endif // !__SHOOTING_CELL_MODEL_H__