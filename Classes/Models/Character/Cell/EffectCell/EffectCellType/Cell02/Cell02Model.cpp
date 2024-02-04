#include "Models/models.h"
#include "Cell02Model.h"

/*
Cell02Model constructor
*/
Cell02Model::Cell02Model() : EffectCellModel(CELL_02_PLATELETS) {
    rechargeTime = 20.0;
    distance = 0.0;
    cost = 50;
    hp = 60;

    // Do not use
    effectRechargeTime = 30.0;
    effectTimeCounter = 30.0;
} 

/*
Cell02Model take effect: None
*/
void Cell02Model::takeEffect() {

}

/* 
Check if can put the plant on map
*/
bool Cell02Model::canPutOn(LevelModel* level, int cellX, int cellY) {
    if (level != NULL) {
        auto map = level->getMap();
        auto maxX = map.size();
        auto maxY = map[0].size();
        if (cellX < 0 || cellX >= maxX) return false;
        if (cellY < 0 || cellY >= maxY) return false;
        if (map[cellX][cellY] == ENEMY_PATH) return true;
    }
    return false;
}

