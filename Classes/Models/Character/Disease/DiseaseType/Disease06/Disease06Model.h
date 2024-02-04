#ifndef __DISEASE_06_MODEL_H__
#define __DISEASE_06_MODEL_H__

#include <list>
class DiseaseModel;
class CellModel;

class Disease06Model : public DiseaseModel {
public:
    Disease06Model();
    virtual ~Disease06Model(){}
    virtual void hitTarget(CellModel* target);
    virtual void update();
protected:
    double distance;
    double waitingUntilNextMove;
    int maxHP;
};

#endif // !__DISEASE_06_MODEL_H__