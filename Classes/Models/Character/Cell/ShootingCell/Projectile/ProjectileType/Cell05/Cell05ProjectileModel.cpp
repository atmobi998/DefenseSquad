#include "Models/models.h"
#include "Cell05ProjectileModel.h"
#include "UIObjects/uiobj.h"

/*
Constructor of Cell0ProjectileModel
*/
Cell05ProjectileModel::Cell05ProjectileModel(CellModel* source, DiseaseModel* target) 
    : ProjectileModel(CELL_05_PROJECTILE, source, target) {
    // Temporary data
    speed = 8.0;
    damage = 1;
    distance = 0.75;
}

/*
Take damage and take effect upon hitting target
*/
void Cell05ProjectileModel::hitTarget() {
    if (!isDestroyed) {
        auto diseaseList = level->__getDiseaseList();
        for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
            if (target->getDistanceToOther(*it) <= distance + 0.000001)
            {
                if ((*it)->getStatus() == FROZEN) {
                    (*it)->deFrozen();
                }
                (*it)->takeDamage(damage);
                if ((*it)->getHP() > 0)
                    (*it)->__getUIObject()->hitAnimate((*it)->getDirection());
            }
        }
        
        effectOnHit();
        isDestroyed = true;
        level->dumpProjectile(this);

        // Destroy UIObject
        ui->destroyAnimate();
        //ui->removeFromScene();
    }
}