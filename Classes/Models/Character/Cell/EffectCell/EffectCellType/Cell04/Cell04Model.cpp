#include "Models/models.h"
#include "Cell04Model.h"
#include "UIObjects/uiobj.h"

/*
Cell04Model constructor
*/
Cell04Model::Cell04Model() : EffectCellModel(CELL_04_MONOCYTES) {
    rechargeTime = 25.0;
    distance = 1.5;
    cost = 50;
    beEaten = false;

    // Do not use
    hp = 80;
    effectRechargeTime = 0.5;
    effectTimeCounter = 0.5;
} 

/*
Cell04Model take effect: None
*/
void Cell04Model::takeEffect() {
    auto diseaseList = level->__getDiseaseList();
    for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
        if (getDistanceToOther(*it) <= distance + ACCEPTING_TIME_ERROR) {
            if ((*it)->getStatus() != FROZEN) {
                (*it)->setFrozen();
                (*it)->setFronzenCounter(7.0);
            }
        }
    }
    hp = 0;
}

/* 
Check if can put the plant on map
*/
bool Cell04Model::canPutOn(LevelModel* level, int cellX, int cellY) {
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

