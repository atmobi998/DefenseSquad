#include "Models/models.h"
#include "ProjectileModel.h"
#include <cmath>
#include <iostream>
#include "UIObjects/uiobj.h"
#include "ProjectileType/ProjectileType.h"
using namespace std;

/*
Create a projectile model with factory
*/
ProjectileModel* ProjectileModel::create(ProjectileId id, CellModel* source, DiseaseModel* target) {
    switch (id) {
    case CELL_00_PROJECTILE:
        return new Cell00ProjectileModel(source, target);
    case CELL_03_PROJECTILE:
        return new Cell03ProjectileModel(source, target);
    case CELL_05_PROJECTILE:
        return new Cell05ProjectileModel(source, target);
    default:
        return new Cell00ProjectileModel(source, target);
    }
    return nullptr;
}

/*
Constructor of projectile model
*/
ProjectileModel::ProjectileModel(ProjectileId id, CellModel* source, DiseaseModel* target) {
    this->level = NULL;
    this->id = id;
    this->target = target;
    isDestroyed = false;

    // Set up source and target position
    cellX = source->getPositionCellX();
    cellY = source->getPositionCellY();
    targetX = target->getPositionCellX();
    targetY = target->getPositionCellY();
    double distance = sqrt((cellX - targetX) * (cellX - targetX) + (cellY - targetY) * (cellY - targetY));
    directionVectorX = (targetX - cellX) / distance;
    directionVectorY = (targetY - cellY) / distance; 
}

/*
Set level model of the projectile
*/
void ProjectileModel::__setLevel(LevelModel* level) {
    this->level = level;
}

/*
Get cell position X
*/
double ProjectileModel::getPositionCellX() {
    return cellX;
}

/*
Get cell position Y
*/
double ProjectileModel::getPositionCellY() {
    return cellY;
}

/*
Get cell position
*/
CellPosition ProjectileModel::getPosition() {
    return CellPosition(cellX, cellY);
}

/*
Update on each updating
*/
void ProjectileModel::update() {
    if (!isDestroyed) {
        // Check position
        if ((cellX - targetX) * directionVectorX >= 0.0 && (cellY - targetY) * directionVectorY >= 0.0) {
            // Destroyed and take effect
            hitTarget();
        }
        else {
            // Update position
            cellX += directionVectorX * UPDATING_FREQUENCY * speed;
            cellY += directionVectorY * UPDATING_FREQUENCY * speed;

            // Change position of UIObject
            ui->setCellPosition(cellX, cellY);
        }
    }
}

/*
Take damage and take effect upon hitting target
*/
void ProjectileModel::hitTarget() {
    if (!isDestroyed) {
        target->takeDamage(damage);
        if (target->getHP() > 0)
            target->__getUIObject()->hitAnimate(target->getDirection());
        effectOnHit();
        isDestroyed = true;
        level->dumpProjectile(this);

        // Destroy UIObject
        ui->destroyAnimate();
        //ui->removeFromScene();
    }
}

/*
Set UI Object for the ProjectileModel
*/
void ProjectileModel::setUIObject(UIProjectile* ui) {
    this->ui = ui;
    ui->idleAnimate();
}