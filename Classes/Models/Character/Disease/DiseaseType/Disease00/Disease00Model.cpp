#include "Models/models.h"
#include "Disease00Model.h"

Disease00Model::Disease00Model() : DiseaseModel(DISEASE_00_RABIES) {
    // Temporary data
    speed = 0.25;
    damage = 1;
    hitRechargeTime = 0.5;
    hp = 5;
}