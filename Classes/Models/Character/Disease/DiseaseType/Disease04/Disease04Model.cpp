#include "Models/models.h"
#include "Disease04Model.h"

Disease04Model::Disease04Model() : DiseaseModel(DISEASE_04_POLIO) {
    // Temporary data
    speed = 0.5;
    damage = 2;
    hitRechargeTime = 0.5;
    hp = 10;
}