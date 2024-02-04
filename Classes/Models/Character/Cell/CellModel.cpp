#include "Models/models.h"
#include "CellModel.h"
#include "UIObjects/uiobj.h"
#include "ShootingCell/ShootingCellType/ShootingCellType.h"
#include "EffectCell/EffectCellType/EffectCellType.h"
#include "cocos2d.h"

/* 
Constructor of CellModel
*/
CellModel::CellModel(CellId id) : CharacterModel(CELL) {
    this->id = id;
    ui = nullptr;
    beEaten = true;
}

/* 
Create new instance of CellModel with factory
*/
CellModel* CellModel::create(CellId id) {
    switch (id) {
    case CELL_00_EOSINOPHILS:
        return new Cell00Model();
    case CELL_01_ERYTHROCYTES:
        return new Cell01Model();
    case CELL_02_PLATELETS:
        return new Cell02Model();
    case CELL_03_BASOPHILS:
        return new Cell03Model();
    case CELL_04_MONOCYTES:
        return new Cell04Model();
    case CELL_05_LYMPHOCYTESB:
        return new Cell05Model();
    case CELL_06_NEUTROPHILS:
        return new Cell06Model();
    }
    return nullptr;
} 

/*
Update on each updating
*/
void CellModel::update() {
    // Check for available hp
    if (hp <= 0 && alive && level != NULL) {
        alive = false;
        level->dumpCell(this);
        this->level = NULL;

        // Destroy UIObject
        ui->dieAnimate();
        //ui->removeFromScene();
        return;
    }
}

/*
Set UI Object for the CellModel
*/
void CellModel::setUIObject(UICell* ui) {
    this->ui = ui;
    ui->idleAnimate();
}

/*
Check if a CellId can be put on level
*/
bool CellModel::canPutOn(CellId id, LevelModel* level, int cellX, int cellY) {
    if (level != nullptr) {
        auto map = level->__getMap();
        int col = map.size();
        int row = map[0].size();
        if (cellX < 0 || cellX >= col) return false;
        if (cellY < 0 || cellY >= row) return false;
        switch (id) {
        // Normal cell
        case CELL_00_EOSINOPHILS:
        case CELL_01_ERYTHROCYTES:
        case CELL_03_BASOPHILS:
        case CELL_05_LYMPHOCYTESB:
            if (map[cellX][cellY] == EMPTY_CAN_PUT) return true;
            else return false;
            break;
        
        // On path cell
        case CELL_02_PLATELETS:
        case CELL_04_MONOCYTES:
        case CELL_06_NEUTROPHILS:
            if (map[cellX][cellY] == ENEMY_PATH) return true;
            else return false;
            break;

        // On occupied
        case REMOVE_CELL:
            if (map[cellX][cellY] == EMPTY_CAN_PUT_OCCUPIED || map[cellX][cellY] == ENEMY_PATH_OCCUPIED) return true;
            else return false;
            break;
        }
    }
    else
        return false;
}