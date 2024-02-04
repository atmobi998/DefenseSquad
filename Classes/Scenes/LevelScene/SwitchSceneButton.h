#ifndef __SWITCHSCENEBUTTON_H__
#define __SWITCHSCENEBUTTON_H__
#include "cocos2d.h"
#include "Models/models.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class SwitchSceneButton :public ui::Button
{
public:
	//static SwitchSceneButton* create(Scene* scene, std::string button_, std::string button_clicked);
	static SwitchSceneButton* create(std::string button_, std::string button_clicked);
	//Scene* scene;
private:
	void touchControlEvent(Ref *sender, ui::Widget::TouchEventType type);
	virtual void onTouch();
	
};

#endif // !__SWITCHSCENEBUTTON_H__