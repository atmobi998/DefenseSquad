#ifndef __CELL_MODEL_H__
#define __CELL_MODEL_H__

class CharacterModel;
class LevelModel;
class UICell;
#include "CellModelDefinitions.h"

class CellModel : public CharacterModel {
protected:
    CellId id;
    int cost;
    double distance;
    double rechargeTime;
    UICell* ui;
    bool beEaten;
public:
    static CellModel* create(CellId id);
    CellModel(CellId id);
    virtual ~CellModel(){};

    // Return the distance 
    virtual double getDistance() {return distance;}
    virtual bool canPutOn(LevelModel* level, int cellX, int cellY){return false;}
    static bool canPutOn(CellId, LevelModel* level, int cellX, int cellY);
    virtual void update();
    virtual void setUIObject(UICell* ui);
    virtual UICell* __getUIObject() {return ui;}
    // Get CellId
    virtual CellId getCellId() {return id;}
    // Get cost
    virtual int getCost() {return cost;}
    // Get recharge time
    virtual double getRechargeTime() {return rechargeTime;}
    // Check if can be eaten
    virtual bool canBeEaten() {return beEaten;}
};

#endif // !__CELL_MODEL_H__