#ifndef __GSCONTROLLAYER_H__
#define __GSCONTROLLAYER_H__

#include "cocos2d.h"
#include "Models/models.h"
#include "GSDefine.h"
#include <functional>

#define RADIUS_PREVIEW "sprites/objects/cell/radius_preview.png"

struct position
{
	int x;
	int y;
};

class GSControlLayer : public cocos2d::Layer
{
public:
	static GSControlLayer* create(LevelModel* level_, cocos2d::Sprite* choose) 
	{ 
		GSControlLayer *pRet = new(std::nothrow) GSControlLayer(); 
		if (pRet && pRet->init(choose)) 
		{ 

			pRet->autorelease(); 
			pRet->level = level_;
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event*event);
	void setPreviewImage(CellId id, double);

private:
	float ScaleNumber = 1.0f;
	cocos2d::Point anchonPoint = cocos2d::Point(0.5,0.5);
	std::string link_image;
	CellId Cell_Id;
	cocos2d::Sprite *previewImage ;
	bool buttonCheck = false;
	cocos2d::Sprite* choose;
	double distance;

public:
    virtual bool init(cocos2d::Sprite*);
    void calculateCellsPosition();
	LevelModel* level;
	position cur_ ;
    position cellsPosition_ ;
};

#endif // !__GSCONTROLLAYER_H__