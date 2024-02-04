#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "Models/models.h"

class MainMenuScene :public cocos2d::Scene 
{
public:
	CREATE_FUNC(MainMenuScene);
	static Scene* createScene();
	virtual bool init();
	
protected:
	void addBackground();
	void controlButton();

};

#endif // !__MAIN_MENU_SCENE_H__