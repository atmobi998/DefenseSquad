#ifndef __NUMERIC_MODEL_H__
#define __NUMERIC_MODEL_H__

#define __HAS_UINUMERIC__
#ifdef __HAS_UINUMERIC__
class UINumeric;    
#endif // __HAS_UINUMERIC__

class NumericModel {
public:
    NumericModel();
    virtual ~NumericModel(){}
    virtual void changeValue(int);
    virtual int getValue();
    #ifdef __HAS_UINUMERIC__
    virtual void setUIObject(UINumeric*);
    virtual UINumeric* __getUIObject() {return ui;}
    #endif // __HAS_UINUMERIC__
protected:
    int value;
    #ifdef __HAS_UINUMERIC__
    UINumeric* ui;
    #endif // __HAS_UINUMERIC__
};

#endif // !__NUMERIC_MODEL_H__