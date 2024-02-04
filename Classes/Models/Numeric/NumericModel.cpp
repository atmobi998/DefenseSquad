#include "Models/models.h"
#include "NumericModel.h"
#include "UINumeric/UINumeric.h"

/*
Constructor of Numeric Model
*/
NumericModel::NumericModel() {
    value = 0;
}

/*
Change value of the model
*/
void NumericModel::changeValue(int value) {
    this->value = value;
    #ifdef __HAS_UINUMERIC__
    ui->changeValue(value);
    #endif // __HAS_UINUMERIC__
}

/*
Set ui object of Numeric Model
*/
#ifdef __HAS_UINUMERIC__
void NumericModel::setUIObject(UINumeric* ui) {
    this->ui = ui;
}
#endif // __HAS_UINUMERIC__

/*
Get current value of the model
*/
int NumericModel::getValue() {
    return value;
}
