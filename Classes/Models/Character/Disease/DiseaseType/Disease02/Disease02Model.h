#ifndef __DISEASE_02_MODEL_H__
#define __DISEASE_02_MODEL_H__

#define DISEASE_02_BETWEEN_EFFECT_COUNTER 2.0
class DiseaseModel;

class Disease02Model : public DiseaseModel {
public:
    Disease02Model();
    virtual ~Disease02Model(){}
    virtual void update();
protected:
    double betweenCounter;
};

#endif // !__DISEASE_02_MODEL_H__