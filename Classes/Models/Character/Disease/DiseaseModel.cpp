#include "Models/models.h"
#include "DiseaseModel.h"
#include <cmath>
#include "UIObjects/uiobj.h"
#include "DiseaseType/DiseaseType.h"
using namespace std;

/*
Constructor of DiseaseModel
*/
DiseaseModel::DiseaseModel(DiseaseId id) : CharacterModel(DISEASE), id(id), action(WAITING), dir(LEFT) {
    level = NULL;
    path = NULL;
    ignoreCell = false;
}

/* 
Set level model of disease
*/
void DiseaseModel::__setLevel(LevelModel* level) {
    if (level != NULL) {
        this->level = level;
        path = level->__getEnemyPath();
        currentPath = path->begin();
        nextPath = currentPath + 1;
        setPosition((*currentPath)[0], (*currentPath)[1]);
        changeDirectionOnPath();
    }
}

/* 
Create new instance of DiseaseModel with Factory
*/
DiseaseModel* DiseaseModel::create(DiseaseId id) {
    switch (id) {
    case DISEASE_00_RABIES:
        return new Disease00Model();
    case DISEASE_01_SMALLPOX:
        return new Disease01Model();
    case DISEASE_02_INFLUENZA:
        return new Disease02Model();
    case DISEASE_03_MEASLES:
        return new Disease03Model();
    case DISEASE_04_POLIO:
        return new Disease04Model();
    case DISEASE_05_MALARIA:
        return new Disease05Model();
    case DISEASE_06_EBOLA:
        return new Disease06Model();
    }
    return nullptr;
}

/*
Change direction of disease on the walking path
*/
void DiseaseModel::changeDirectionOnPath() {
    // End of path
    if (nextPath == path->end()) {
        return;
    }

    // Change direction
    if ((*nextPath)[0] == (*currentPath)[0]) {
        if ((*nextPath)[1] < (*currentPath)[1])
            dir = DOWN;
        else
            dir = UP;
    }
    else if ((*nextPath)[0] < (*currentPath)[0]) {
        dir = LEFT;
    }
    else
        dir = RIGHT;
}

/*
Change direction of disease to the target
*/
void DiseaseModel::changeDirectionToTarget(CellModel* target) {
    auto deltaX = target->getPositionCellX() - cellX;
    auto deltaY = target->getPositionCellY() - cellY;
    if (abs(deltaX) < abs(deltaY)) {
        if (deltaY > 0.0) dir = UP;
        else dir = DOWN;
    }
    else {
        if (deltaX > 0.0) dir = RIGHT;
        else dir = LEFT;
    }
}

/*
Destructor of DIseasModel
*/
DiseaseModel::~DiseaseModel() {

}

/*
Update on each updating
*/
void DiseaseModel::update() {
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

    if (alive && level != NULL) {
        // Search if any cell to attack
        auto cellList = level->__getCellList();
        auto target = cellList.end();
        for (auto it = cellList.begin(); it != cellList.end(); it++) {
            if (getDistanceToOther(*it) <= 1.0 + 0.0000002 && (*it)->canBeEaten()) {
                // Check if a passed target
                auto pre = currentPath;
                if (abs((*it)->getPositionCellX() - (*pre)[0]) <= 0.0000002 && abs((*it)->getPositionCellY() - (*pre)[1]) <= 0.0000002) {
                    continue;
                }

                if (pre != path->begin()) {
                    pre--;
                    if (abs((*it)->getPositionCellX() - (*pre)[0]) <= 0.0000002 && abs((*it)->getPositionCellY() - (*pre)[1]) <= 0.0000002) {
                        continue;
                    }
                }

                target = it;
                break;
            }
        }

        // Detect enemy
        if (target != cellList.end() && !ignoreCell) {
            action = ATTACKING;
        }

        // If is attacking
        if (action == ATTACKING) {
            // Detect to attack
            if (target != cellList.end()) {
                changeDirectionToTarget(*target);
                
                // Check if recharge time
                auto timePoint = level->getTimeCounter() / hitRechargeTime;
                auto roundTimePoint = round(timePoint);
                auto deltaError = timePoint - roundTimePoint;
                if (deltaError >= -ACCEPTING_TIME_ERROR && deltaError <= ACCEPTING_TIME_ERROR) {
                    hitTarget(*target);
                    ui->idleAnimate(dir);
                    changeDirectionOnPath();
                }
            }
            else {
                action = WAITING;
                ui->idleAnimate(dir);
            }
        }

        // If is waiting
        if (action == WAITING) {
            // Change to walking
            action = WALKING;
            changeDirectionOnPath();
            ui->walkAnimate(dir);
        }

        // If is walking
        if (action == WALKING) {
            // Update position
            auto directionVectorX = 0.0;
            auto directionVectorY = 0.0;
            if (dir == UP) {directionVectorY = 1.0;}
            else if (dir == DOWN) {directionVectorY = -1.0;}
            else if (dir == RIGHT) {directionVectorX = 1.0;}
            else directionVectorX = -1.0;
            cellX += directionVectorX * UPDATING_FREQUENCY * speed;
            cellY += directionVectorY * UPDATING_FREQUENCY * speed;

            // Change position of UIObject
            ui->setCellPosition(cellX, cellY);

            // Check if the axis is an interger
            auto roundX = round(cellX);
            auto roundY = round(cellY);
            if (abs(cellX - roundX) <= ACCEPTING_TIME_ERROR && abs(cellY - roundY) <= ACCEPTING_TIME_ERROR) {
                action = WAITING;
                ui->idleAnimate(dir);
                if (nextPath != path->end()) {
                    if (abs((*nextPath)[0] - cellX) <= ACCEPTING_TIME_ERROR && abs((*nextPath)[1] - cellY) <= ACCEPTING_TIME_ERROR) {
                        currentPath++;
                        nextPath++;

                        // Losing condition
                        if (nextPath == path->end()) {
                            level->setLose();
                        }
                    }
                }
            }
        }
    }
}

/*
Attack on target
*/
void DiseaseModel::hitTarget(CellModel* target) {
    ui->attackAnimate(dir);
    target->takeDamage(damage);
    target->__getUIObject()->hitAnimate();
}

/*
Get value of disease id. Should not be used outside models
*/
DiseaseId DiseaseModel::__getDiseaseId() {
    return id;
}

/*
Set UI Object for the DiseaseModel
*/
void DiseaseModel::setUIObject(UIDisease* ui) {
    this->ui = ui;
    ui->idleAnimate(dir);
}

/*
Set frozen
*/
void DiseaseModel::setFrozen() {
    this->setStatus(FROZEN);
    ui->setFrozenAnimate();
}

/*
Defrozen
*/
void DiseaseModel::deFrozen() {
    this->setStatus(NORMAL);
    this->setFronzenCounter(0.0);
    ui->deFrozenAnimate();
}