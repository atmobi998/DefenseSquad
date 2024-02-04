#include "Models/models.h"
#include "Cell00ProjectileModel.h"

/*
Constructor of Cell0ProjectileModel
*/
Cell00ProjectileModel::Cell00ProjectileModel(CellModel* source, DiseaseModel* target) 
    : ProjectileModel(CELL_00_PROJECTILE, source, target) {
    // Temporary data
    speed = 8.0;
    damage = 1;
}