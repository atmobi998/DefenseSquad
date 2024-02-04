#ifndef __UI_NUMERIC_DEFINITIONS_H__
#define __UI_NUMERIC_DEFINITIONS_H__

#define ENERGY_COUNTER_POS_X Director::getInstance()->getSafeAreaRect().getMinX() + 5.0f + 95.0f * Director::getInstance()->getVisibleSize().height / 8 / 90.0f + Director::getInstance()->getVisibleOrigin().x
#define ENERGY_COUNTER_POS_Y Director::getInstance()->getVisibleSize().height / 16 * 15 + Director::getInstance()->getVisibleOrigin().y
#define GOLD_COUNTER_POS_X
#define GOLD_COUNTER_POS_Y

#define NUMERIC_LAYER_ZORDER 9

#define NUMERIC_IMG "sprites/InformationLayer/number.png"

#endif // !__UI_NUMERIC_DEFINITIONS_H__