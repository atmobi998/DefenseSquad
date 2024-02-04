#ifndef __EFFECTOR_H__
#define __EFFECTOR_H__

class Effector {
protected:
    double effectRechargeTime;
    double effectTimeCounter;
public:
    Effector(){}
    virtual ~Effector(){}
    virtual void takeEffect(){}
};

#endif // !__EFFECTOR_H__