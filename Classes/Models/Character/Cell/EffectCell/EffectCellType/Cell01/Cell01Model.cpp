#include "Models/models.h"
#include "Cell01Model.h"
#include "UIObjects/uiobj.h"
#include <functional>
using namespace std;

/*
Cell01Model constructor
*/
Cell01Model::Cell01Model() : EffectCellModel(CELL_01_ERYTHROCYTES) {
    rechargeTime = 12.0;
    effectRechargeTime = 12.0;
    effectTimeCounter = 9.0;
    distance = 0.0;
    cost = 50;
    hp = 5;
} 

/*
Cell01Model take effect: create energy
*/
void Cell01Model::takeEffect() {
    function<function<void()>()> func = [this]() -> function<void()> {
        return [&](){
            if (level != NULL) {
                level->addEnergyObject(cellX, cellY);
            }
        };
    };

    ui->effectAnimate(func());
}

/* 
Check if can put the plant on map
*/
bool Cell01Model::canPutOn(LevelModel* level, int cellX, int cellY) {
    if (level != NULL) {
        auto map = level->getMap();
        auto maxX = map.size();
        auto maxY = map[0].size();
        if (cellX < 0 || cellX >= maxX) return false;
        if (cellY < 0 || cellY >= maxY) return false;
        if (map[cellX][cellY] == EMPTY_CAN_PUT) return true;
    }
    return false;
}

