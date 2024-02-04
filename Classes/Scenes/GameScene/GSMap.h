#ifndef __GSMAP_H__
#define __GSMAP_H__

#include "cocos2d.h"
#include "Models/models.h"
#include "GSDefine.h"
struct positionCell
{
	int x;
	int y;
};
class GSMap : public cocos2d::Layer{
public:
	CREATE_FUNC(GSMap);
	bool init();
	void createMap(LevelModel *level);	
};


#endif // !__GSMAP_H__