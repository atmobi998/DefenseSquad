#ifndef __LEVELSCENE_H__
#define __LEVELSCENE_H__
#include "cocos2d.h"
#include "Models/models.h"
#define LOCK_BUTTON "sprites/objects/button/level_button_lock.png"
#define BACK_GROUND_1 "sprites/Background/levelbackground1.png"
#define BACK_GROUND_2 "sprites/Background/levelbackground2.png"
#define BACK_GROUND_3 "sprites/Background/levelbackground3.png"
#define BUTTON_BACK "sprites/objects/button/layer_button_back.png"
#define BUTTON_BACK_CLICKED "sprites/objects/button/layer_button_back_clicked.png"
#define NUMBER_LEVEL 8
USING_NS_CC;
class levelScene :public Scene
{
public:
	CREATE_FUNC(levelScene);
	static Scene* createScene();
	virtual bool init();
	virtual ~levelScene() {};
	virtual void SetBackGround();
	Scene * next;

protected:
	virtual void CreateBackButton();
	virtual void CreateButtonLevel();
};
#endif // !__LEVELSCENE_H__