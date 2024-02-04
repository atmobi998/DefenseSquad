#ifndef __UI_CONTROL_CELLBAR_DEFINITIONS_H__
#define __UI_CONTROL_CELLBAR_DEFINITIONS_H__

#include "Models/Character/Cell/CellModelDefinitions.h"

#define DOUBLE_PRECISION 0.000001

#define CELLBAR_LAYER_ZORDER 10

#define CELLBAR_POSITION_X Director::getInstance()->getSafeAreaRect().getMinX() + 8.0f + 72.0f * Director::getInstance()->getVisibleSize().height / 8 / 90.0f + Director::getInstance()->getVisibleOrigin().x
#define CELLBAR_POSITION_Y(index) Director::getInstance()->getVisibleSize().height / 16 * (13 - 2 * index) + Director::getInstance()->getVisibleOrigin().y

#define CELLBAR_SCALE Director::getInstance()->getVisibleSize().height / 8 / 90.0f

#define CELLBAR_LOADING_FILENAME "sprites/objects/cell/cellbar/cellbar_loading.png"
#define CELLBAR_LOADING_COMPLETE_FILENAME "sprites/objects/cell/cellbar/cellbar_loading_complete.png"
#define CELLBAR_CHOOSING_FILENAME "sprites/objects/cell/cellbar/cellbar_choosing.png"
#define ANIM_CELLBAR_FLASH 0.1f

#define CELLBAR_00_FILENAME "sprites/objects/cell/cellbar/cellbar_00.png"
#define CELLBAR_01_FILENAME "sprites/objects/cell/cellbar/cellbar_01.png"
#define CELLBAR_02_FILENAME "sprites/objects/cell/cellbar/cellbar_02.png"
#define CELLBAR_03_FILENAME "sprites/objects/cell/cellbar/cellbar_03.png"
#define CELLBAR_04_FILENAME "sprites/objects/cell/cellbar/cellbar_04.png"
#define CELLBAR_05_FILENAME "sprites/objects/cell/cellbar/cellbar_05.png"
#define CELLBAR_06_FILENAME "sprites/objects/cell/cellbar/cellbar_06.png"

#define ICON_ATTACK "sprites/objects/cell/cellbar/icon_attack.png"
#define ICON_DEFENSE "sprites/objects/cell/cellbar/icon_defense.png"
#define ICON_EFFECT "sprites/objects/cell/cellbar/icon_effect.png"
#define ICON_PATH "sprites/objects/cell/cellbar/icon_path.png"
#define ICON_LANE "sprites/objects/cell/cellbar/icon_lane.png"

#endif // !__UI_CONTROL_CELLBAR_DEFINITIONS_H__