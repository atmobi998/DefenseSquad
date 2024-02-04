#ifndef __EFFECT_CELL_MODEL_H__
#define __EFFECT_CELL_MODEL_H__

class Effector;
class CellModel;

class EffectCellModel : public CellModel, public Effector {
public:
    EffectCellModel(CellId id);
    virtual ~EffectCellModel(){}
protected:
    virtual void takeEffect(){};
    virtual void update();
};

#endif // !__EFFECT_CELL_MODEL_H__