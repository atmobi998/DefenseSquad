#ifndef __MM_BACKGROUND_LAYER_H__
#define __MM_BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <string>
#include <vector>

#define IMG_MMBGMOR "sprites/Background/bg_mainmenu_morning.png"
#define IMG_MMBGAFTER "sprites/Background/bg_mainmenu_afternoon.png"
#define IMG_MMBGNIGHT "sprites/Background/bg_mainmenu_night.png"
#define IMG_NAMEGAME "sprites/Background/defensesquad.png"

class MMBackgroundLayer:public cocos2d :: Layer
{
public:
	CREATE_FUNC(MMBackgroundLayer);

	virtual bool init();

private:
	void setBackgroundImagePosition();
	void setNameGamePosition();	

};
#endif // !__MM_BACKGROUND_LAYER_H__