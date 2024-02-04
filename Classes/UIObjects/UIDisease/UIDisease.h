#ifndef __UI_DISEASE_H__
#define __UI_DISEASE_H__

#include "UIDiseaseDefinitions.h"
#include "cocos2d.h"
#include "Models/Character/Disease/DiseaseModelDefinitions.h"
#include <functional>

class UIObjects;

class UIDisease : public UIObjects {
public:
    static UIDisease* create(DiseaseId);
    virtual void addToScene(cocos2d::Scene*);
    virtual void idleAnimate(Direction dir) {}
    virtual void walkAnimate(Direction dir) {}
	virtual void attackAnimate(Direction dir);
	virtual void hitAnimate(Direction dir);
	virtual void dieAnimate(Direction dir);
    virtual void attackAnimateWithSync(Direction dir, std::function<void()> callBack){}
    virtual void thirdHPAnimate(float) {}
};

#endif // !__UI_DISEASE_H__