#ifndef __CELL_01_MODEL_H__
#define __CELL_01_MODEL_H__

class EffectCellModel;

class Cell01Model : public EffectCellModel {
public:
    Cell01Model();
    virtual ~Cell01Model(){};
protected:
    virtual void takeEffect();
    virtual bool canPutOn(LevelModel*, int cellX, int cellY);
};

#endif // !__CELL_01_H__