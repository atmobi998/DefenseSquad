#include "Models/models.h"
#include "Disease01Model.h"

Disease01Model::Disease01Model() : DiseaseModel(DISEASE_01_SMALLPOX) {
    // Temporary data
    speed = 0.25;
    damage = 1;
    hitRechargeTime = 0.5;
    hp = 12;
}