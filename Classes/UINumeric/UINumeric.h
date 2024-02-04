#ifndef __UI_NUMERIC_H__
#define __UI_NUMERIC_H__

#include "cocos2d.h"
#include "UINumericDefinitions.h"
#include "../Models/models.h"


class UINumeric : public cocos2d::Node {
	cocos2d::Vector<cocos2d::Sprite*> digitList;
	float scale;
public:
	virtual void addToScene(cocos2d::Scene* scene);
    virtual void removeFromScene();
	virtual void changeValue(int);
	virtual void setScale(float _scale) {scale *= _scale;}
	virtual void emphasizeAnimate();
	static UINumeric* create();
};

#endif // !__UI_NUMERIC_H__