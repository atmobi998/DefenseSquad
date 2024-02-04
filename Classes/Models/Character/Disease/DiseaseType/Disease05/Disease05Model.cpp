#include "Models/models.h"
#include "Disease05Model.h"

Disease05Model::Disease05Model() : DiseaseModel(DISEASE_05_MALARIA) {
    // Temporary data
    speed = 1.0;
    damage = 1;
    hitRechargeTime = 0.5;
    hp = 1;
}