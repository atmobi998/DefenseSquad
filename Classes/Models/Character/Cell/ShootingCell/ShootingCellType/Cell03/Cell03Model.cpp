#include "Models/models.h"
#include "Cell03Model.h"

/*
Cell03Model constructor
*/
Cell03Model::Cell03Model() : ShootingCellModel(CELL_03_BASOPHILS, CELL_03_PROJECTILE) {
    rechargeTime = 14.0;
    shootRechargeTime = 1.5;
    shootTimeCounter = 1.5;
    distance = 4.0;
    cost = 200;
    hp = 5;
} 

