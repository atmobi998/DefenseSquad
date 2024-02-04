#include "Models/models.h"
#include "Disease06Model.h"
#include "UIObjects/uiobj.h"
#include <functional>
using namespace std;

Disease06Model::Disease06Model() : DiseaseModel(DISEASE_06_EBOLA) {
    // Temporary data
    speed = 0.2;
    damage = 50;
    hitRechargeTime = 2.0;
    maxHP = 175;
    hp = 175;
    distance = 1.5;
    waitingUntilNextMove = 0.0;
}

/*
Boss hit target
*/
void Disease06Model::hitTarget(CellModel*) {
    function<function<void()>()> func = [this]() -> function<void()> {
        return [&]() {
            auto cellList = this->level->__getCellList();
            for (auto it = cellList.begin(); it != cellList.end(); it++) {
                if (this->getDistanceToOther(*it) <= this->distance + 0.000001) {
                    (*it)->takeDamage(this->damage);
                    (*it)->__getUIObject()->hitAnimate();
                }
            }
        };
    };

    ui->attackAnimateWithSync(dir, func());
    // auto cellList = level->__getCellList();
    // for (auto it = cellList.begin(); it != cellList.end(); it++) {
    //     if (getDistanceToOther(*it) <= distance + 0.000001) {
    //         (*it)->takeDamage(damage);
    //         (*it)->__getUIObject()->hitAnimate();
    //     }
    // }

    // // Update counter
    waitingUntilNextMove = 3.0;
    ui->idleAnimate(dir);
}

/*
Update on each updating of Disease06
*/
void Disease06Model::update() {
    ui->thirdHPAnimate(1.0f - ((float) hp) / maxHP);

    // Check waiting for next move
    if (waitingUntilNextMove <= ACCEPTING_TIME_ERROR) {
        DiseaseModel::update();
    }
    else {
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
        waitingUntilNextMove -= UPDATING_FREQUENCY;
    }
}