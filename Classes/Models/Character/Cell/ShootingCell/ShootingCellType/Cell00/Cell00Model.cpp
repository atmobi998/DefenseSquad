#include "Models/models.h"
#include "Cell00Model.h"

/*
Cell00Model constructor
*/
Cell00Model::Cell00Model() : ShootingCellModel(CELL_00_EOSINOPHILS, CELL_00_PROJECTILE) {
    rechargeTime = 12.0;
    shootRechargeTime = 1.0;
    shootTimeCounter = 1.0;
    distance = 2.0;
    cost = 100;
    hp = 5;
} 

