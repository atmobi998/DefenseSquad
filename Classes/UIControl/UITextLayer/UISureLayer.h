#ifndef __UI_SURE_LAYER_H__
#define __UI_SURE_LAYER_H__

#include "UITextLayer.h"

#define SURE_LAYER_TEXT_FILENAME "sprites/objects/button/text_sure.png"

class UISureLayer : public UITextLayer {
public:
    static UISureLayer* create();
    virtual bool init();
};

#endif // !__UI_SURE_LAYER_H__