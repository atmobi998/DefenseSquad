#ifndef __UI_OBJECTS_DEFINITIONS_H__
#define __UI_OBJECTS_DEFINITIONS_H__

#define HEIGHT_R Director::getInstance()->getVisibleSize().height
#define WIDTH_R Director::getInstance()->getVisibleSize().width

#define TOP_R HEIGHT_R * 7/8

#define GRASS_POSITION_LEFT_R WIDTH_R * 3/16
#define GRASS_POSITION_RIGHT_R WIDTH_R * 15/16
#define GRASS_POSITION_TOP_R HEIGHT_R * 7/8   
#define GRASS_POSITION_BOTTOM_R HEIGHT_R * 1/8

#define ROWW_R 5
#define COLUMNN_R 8

#define SIZE_OF_SQUARE_R fmin((GRASS_POSITION_RIGHT_R - GRASS_POSITION_LEFT_R) / COLUMNN_R, (GRASS_POSITION_TOP_R - GRASS_POSITION_BOTTOM_R) / ROWW_R)

#define GRASS_ORIGIN_POSITION_X_R (GRASS_POSITION_RIGHT_R + GRASS_POSITION_LEFT_R) / 2 - COLUMNN_R * SIZE_OF_SQUARE_R / 2 + Director::getInstance()->getVisibleOrigin().x
#define GRASS_ORIGIN_POSITION_Y_R (GRASS_POSITION_TOP_R + GRASS_POSITION_BOTTOM_R) / 2 - ROWW_R * SIZE_OF_SQUARE_R / 2 + Director::getInstance()->getVisibleOrigin().y

#define CELL_WIDTH SIZE_OF_SQUARE_R
#define POS_X_ORIGIN GRASS_ORIGIN_POSITION_X_R + CELL_WIDTH / 2.0f
#define POS_Y_ORIGIN GRASS_ORIGIN_POSITION_Y_R + CELL_WIDTH / 2.0f

#define OBJECT_SCALE CELL_WIDTH / 98.0f

#define SHADOW_FILENAME "sprites/objects/shadow.png"

#endif // !__UI_OBJECTS_DEFINITIONS_H__