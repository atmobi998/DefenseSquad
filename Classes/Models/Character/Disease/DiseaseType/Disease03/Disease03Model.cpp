#include "Models/models.h"
#include "Disease03Model.h"

Disease03Model::Disease03Model() : DiseaseModel(DISEASE_03_MEASLES) {
    // Temporary data
    speed = 0.25;
    damage = 1;
    hitRechargeTime = 0.5;
    hp = 20;
}