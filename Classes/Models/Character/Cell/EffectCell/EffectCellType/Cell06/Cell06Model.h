#ifndef __CELL_06_MODEL_H__
#define __CELL_06_MODEL_H__

class EffectCellModel;

class Cell06Model : public EffectCellModel {
public:
    Cell06Model();
    virtual ~Cell06Model(){};
protected:
    virtual void takeEffect();
    virtual bool canPutOn(LevelModel*, int cellX, int cellY);
    int damage;
};

#endif // !__CELL_06_H__