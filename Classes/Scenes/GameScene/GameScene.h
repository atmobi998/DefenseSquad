#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "cocos2d.h"
#include "Components/GSTutorial.h"
#include "Models/models.h"
#include "GSMap.h"
class GSTutorial;
class GameScene :public cocos2d::Scene 
{
public:
	static GameScene* create(int level) 
	{ 
		GameScene *pRet = new(std::nothrow) GameScene(); 
		if (pRet && pRet->init(level)) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}

	static Scene* createScene(int);
	virtual bool init(int);
	virtual ~GameScene() {delete level;}
	
protected:
	// virtual void controlLayer(LevelModel* level);
	virtual void drawMap();
	virtual void addBackground();
	
	LevelModel* level;
	void updateLevel(float);

	GSTutorial* layer;
};

#endif // !__GAMESCENE_H__