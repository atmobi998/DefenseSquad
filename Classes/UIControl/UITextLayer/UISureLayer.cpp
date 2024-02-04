#include "UISureLayer.h"
USING_NS_CC;
using namespace std;

UISureLayer* UISureLayer::create() {
    UISureLayer *ret = new (std::nothrow) UISureLayer;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool UISureLayer::init() {
    UITextLayer::init(SURE_LAYER_TEXT_FILENAME);
    return true;
}