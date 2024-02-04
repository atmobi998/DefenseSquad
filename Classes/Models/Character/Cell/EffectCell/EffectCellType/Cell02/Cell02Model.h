#ifndef __CELL_02_MODEL_H__
#define __CELL_02_MODEL_H__

class EffectCellModel;

class Cell02Model : public EffectCellModel {
public:
    Cell02Model();
    virtual ~Cell02Model(){};
protected:
    virtual void takeEffect();
    virtual bool canPutOn(LevelModel*, int cellX, int cellY);
};

#endif // !__CELL_02_H__