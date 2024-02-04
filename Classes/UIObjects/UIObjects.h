#ifndef __UI_OBJECTS_H__
#define __UI_OBJECTS_H__

#include "cocos2d.h"
#include "UIObjectsDefinitions.h"

class UIObjects : public cocos2d::Sprite {
public:
    virtual void setCellPosition(double, double);
    virtual void addToScene(cocos2d::Scene*);
    virtual void removeFromScene();
    virtual void setFrozenAnimate();
    virtual void deFrozenAnimate();
protected:
    cocos2d::Vector<cocos2d::Animation*> previousStateAnimations;
    cocos2d::Sprite* shadow;
};

#endif // !__UI_OBJECTS_H__