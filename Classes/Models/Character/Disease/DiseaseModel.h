#ifndef __DISEASE_MODEL_H__
#define __DISEASE_MODEL_H__

#include "DiseaseModelDefinitions.h"
#include <vector>
class CharacterModel;
class CellModel;
class LevelModel;
class UIDisease;

class DiseaseModel : public CharacterModel {
protected:
    DiseaseId id;
    DiseaseAction action;
    Direction dir;
    double speed;
    int damage;
    double hitRechargeTime;
    bool ignoreCell;
    std::vector< std::vector<int> >* path;
    std::vector< std::vector<int> >::iterator currentPath;
    std::vector< std::vector<int> >::iterator nextPath;
    virtual void changeDirectionOnPath();
    virtual void changeDirectionToTarget(CellModel*);
    UIDisease* ui;
public:
    static DiseaseModel* create(DiseaseId);
    DiseaseModel(DiseaseId);
    virtual ~DiseaseModel();
    virtual void update();
    virtual void hitTarget(CellModel* target);
    virtual void __setLevel(LevelModel*);
    virtual DiseaseId __getDiseaseId();
    virtual void setUIObject(UIDisease* ui);
    virtual UIDisease* __getUIObject() {return ui;}
    // Get DiseaseId
    virtual DiseaseId getDiseaseId() {return id;}
    virtual Direction getDirection() {return dir;}
    virtual void setFrozen();
    virtual void deFrozen();
};

#endif // !__DISEASE_MODEL_H__