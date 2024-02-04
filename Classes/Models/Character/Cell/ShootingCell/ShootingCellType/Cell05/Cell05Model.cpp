#include "Models/models.h"
#include "Cell05Model.h"

/*
Cell05Model constructor
*/
Cell05Model::Cell05Model() : ShootingCellModel(CELL_05_LYMPHOCYTESB, CELL_05_PROJECTILE) {
    rechargeTime = 14.0;
    shootRechargeTime = 1.5;
    shootTimeCounter = 1.5;
    distance = 2.75;
    cost = 175;
    hp = 5;
} 

