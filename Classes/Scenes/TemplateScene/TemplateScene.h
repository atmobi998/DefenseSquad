#ifndef __TEMPLATESCENE_H__
#define __TEMPLATESCENE_H__

#include "cocos2d.h"

class TemplateScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TemplateScene);
private:
    void goToNextScene();
    void goToPreviousScene();
};

#endif // !__TEMPLATESCENE_H__