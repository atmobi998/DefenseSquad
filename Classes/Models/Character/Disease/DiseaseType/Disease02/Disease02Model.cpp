#include "Models/models.h"
#include "Disease02Model.h"
#include "UIObjects/uiobj.h"

Disease02Model::Disease02Model() : DiseaseModel(DISEASE_02_INFLUENZA) {
    // Temporary data
    speed = 2.0;
    damage = 1;
    hitRechargeTime = 0.5;
    hp = 7;

    ignoreCell = true;
    betweenCounter = 0.0;
}

/*
Update of Disease02Model
*/
void Disease02Model::update() {
    // Check if alive
    if (alive && hp <= 0) {
        alive = false;
        level->dumpDisease(this);
        this->level = NULL;

        // Remove any existing status
        if (status == FROZEN) {
            ui->deFrozenAnimate();
        }

        // Destroy UIObject
        ui->dieAnimate(dir);
        //ui->removeFromScene();
        return;
    }

    // Check if any status that prevents moving
    if (status == FROZEN) {
        if (abs(frozenStatusCounter) <= ACCEPTING_TIME_ERROR) {
            // Thawed out
            deFrozen();
        }
        else {
            frozenStatusCounter -= UPDATING_FREQUENCY;
            return;
        }
    }

    if (abs(betweenCounter) <= ACCEPTING_TIME_ERROR) {
        DiseaseModel::update();

        // Check if cell in path
        if (nextPath != path->end()) {
            if ((level->__getMap())[(*nextPath)[0]][(*nextPath)[1]] == ENEMY_PATH_OCCUPIED && ignoreCell == true) {
                ignoreCell = false;
                speed = 0.25;
                betweenCounter = DISEASE_02_BETWEEN_EFFECT_COUNTER;
                action = WAITING;
                ui->idleAnimate(dir);
            }
        }

        // Trigger between effect
        if (action == WAITING && ignoreCell == true) {
            // Replacing path
            auto preDir = dir;
            changeDirectionOnPath();
            if (dir != preDir) {
                dir = preDir;
                ignoreCell = false;
                speed = 0.25;
                betweenCounter = DISEASE_02_BETWEEN_EFFECT_COUNTER;
            }
        }
    }
    else {
        betweenCounter -= UPDATING_FREQUENCY;
    }
}