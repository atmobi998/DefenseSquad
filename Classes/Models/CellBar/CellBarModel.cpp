#include "Models/models.h"
#include "CellBarModel.h"
#include "UIControl/UIControlCellBar/UIControlCellBar.h"
#include <cmath>

/* 
Constructor of CellBarModel
*/
CellBarModel::CellBarModel(CellId id) {
    auto cellModel = CellModel::create(id);

    this->level = nullptr;
    this->id = id;
    this->rechargeTime = cellModel->getRechargeTime();
    this->distance = cellModel->getDistance();
    switch (id) {
    case CELL_01_ERYTHROCYTES:
        this->rechargeTimeCounter = rechargeTime - 0.5;
        break;
    default:
        this->rechargeTimeCounter = rechargeTime / 2;
        break;
    }
    this->cost = cellModel->getCost();

    delete cellModel;
}

/*
Update upon each updating
*/
void CellBarModel::update() {
    if (level != nullptr) {
        rechargeTimeCounter = std::min(rechargeTimeCounter + UPDATING_FREQUENCY, rechargeTime);

        #ifdef __HAS_UICELLBAR__
        // Updating UIControlCellBar
        ui->updateRecharge(getRechargePercent());
        #endif // __HAS_UICELLBAR__
    }
}

#ifdef __HAS_UICELLBAR__
/* 
Set UIControlCellBar 
*/
void CellBarModel::setUIObject(UIControlCellBar* ui) {
    this->ui = ui;

    // Set something with ui
}
#endif // __HAS_UICELLBAR__