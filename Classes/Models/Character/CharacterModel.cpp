#include "Models/models.h"
#include "CharacterModel.h"
#include <cmath>

/* 
Constructor of CharacterModel
*/
CharacterModel::CharacterModel(CharacterType type) {
    this->type = type;
    this->level = NULL;
    status = NORMAL;
    frozenStatusCounter = 0.0;
    alive = true;
}

/*
Set level model of the character
*/
void CharacterModel::__setLevel(LevelModel* level) {
    this->level = level;
}

/*
Reduce hp of the Character
*/
void CharacterModel::takeDamage(int damage) {
    hp -= damage;
}

/*
Set status of the character
*/
void CharacterModel::setStatus(CharacterStatus status) {
    this->status = status;
}

/*
Set frozen counter of the character
*/
void CharacterModel::setFronzenCounter(double counter) {
    frozenStatusCounter = counter;
}

/*
Check if the character is alive or not
*/
bool CharacterModel::isAlive() {
    return alive;
}
/*
Set cell position of the character
*/
void CharacterModel::setPosition(double cellX, double cellY) {
    this->cellX = cellX;
    this->cellY = cellY;
}

/* 
Get cell position of the character. The result is a struct with 2 properties: cellX and cellY.
*/
CellPosition CharacterModel::getPosition() {
    return CellPosition(cellX, cellY);
}

/* 
Get cellX position of the character.
*/
double CharacterModel::getPositionCellX() {
    return cellX;
}

/* 
Get cellY position of the character.
*/
double CharacterModel::getPositionCellY() {
    return cellY;
}

/*
Get distance to other character
*/
double CharacterModel::getDistanceToOther(CharacterModel* other) {
    return sqrt((cellX - other->cellX) * (cellX - other->cellX) + (cellY - other->cellY) * (cellY - other->cellY));
}