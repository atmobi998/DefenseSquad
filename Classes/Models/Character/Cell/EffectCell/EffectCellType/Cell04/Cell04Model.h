#ifndef __CELL_04_MODEL_H__
#define __CELL_04_MODEL_H__

class EffectCellModel;

class Cell04Model : public EffectCellModel {
public:
    Cell04Model();
    virtual ~Cell04Model(){};
protected:
    virtual void takeEffect();
    virtual bool canPutOn(LevelModel*, int cellX, int cellY);
};

#endif // !__CELL_04_H__