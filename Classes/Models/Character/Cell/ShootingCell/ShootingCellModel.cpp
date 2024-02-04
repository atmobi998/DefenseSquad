#include "Models/models.h"
#include "ShootingCellModel.h"
#include <cmath>
#include "ShootingCellType/ShootingCellType.h"
#include "UIObjects/uiobj.h"
using namespace std;

/* 
Constructor of shooting cell model
*/
ShootingCellModel::ShootingCellModel(CellId cellId, ProjectileId projectileId) : CellModel(cellId) {
    // Temporary data
    this->projectileId = projectileId;
};

/*
Shoot projectile from source to target
*/
void ShootingCellModel::shoot(DiseaseModel* target) {
    if (level != NULL) {
        ui->attackAnimate();
        auto projectile = ProjectileModel::create(projectileId, this, target);
        level->addProjectile(projectile);
        ui->idleAnimate();
    }
}

/*
Update on each updating
*/
void ShootingCellModel::update() {
    CellModel::update();

    if (alive && level != NULL) {
        // Check if recharge time
        if (shootTimeCounter <= ACCEPTING_TIME_ERROR) {
            // Find target in range
            auto diseaseList = level->__getDiseaseList();
            auto target = diseaseList.end();
            for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
                if (getDistanceToOther(*it) <= distance) {
                    if (target != diseaseList.end()) {
                        if (getDistanceToOther(*target) > getDistanceToOther(*it)) {
                            target = it;
                        }
                    }
                    else {
                        target = it;
                    }
                }
            }

            // Shoot to target
            if (target != diseaseList.end()) {
                shoot(*target);
                shootTimeCounter = shootRechargeTime;
            }
        }
        else {
            shootTimeCounter -= UPDATING_FREQUENCY;
        }
    }
}

/* 
Check if can put the plant on map
*/
bool ShootingCellModel::canPutOn(LevelModel* level, int cellX, int cellY) {
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