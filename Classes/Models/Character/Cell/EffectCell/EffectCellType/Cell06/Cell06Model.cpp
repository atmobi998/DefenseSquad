#include "Models/models.h"
#include "Cell06Model.h"
#include "UIObjects/uiobj.h"

/*
Cell06Model constructor
*/
Cell06Model::Cell06Model() : EffectCellModel(CELL_06_NEUTROPHILS) {
    rechargeTime = 60.0;
    distance = 1.5;
    cost = 175;
    hp = 80;
    damage = 50;
    beEaten = false;

    // Do not use
    effectRechargeTime = 0.9;
    effectTimeCounter = 0.9;
} 

/*
Cell06Model take effect: None
*/
void Cell06Model::takeEffect() {
    auto diseaseList = level->__getDiseaseList();
    for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
        if (getDistanceToOther(*it) <= distance + ACCEPTING_TIME_ERROR) {
            if ((*it)->getStatus() == FROZEN) {
                    (*it)->deFrozen();
            }
            (*it)->takeDamage(damage);
            if ((*it)->getHP() > 0)
                (*it)->__getUIObject()->hitAnimate((*it)->getDirection());
        }
    }
    hp = 0;
}

/* 
Check if can put the plant on map
*/
bool Cell06Model::canPutOn(LevelModel* level, int cellX, int cellY) {
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

