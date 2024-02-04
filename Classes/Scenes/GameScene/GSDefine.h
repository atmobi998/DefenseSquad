#ifndef __GSDEFINE_H__
#define __GSDEFINE_H__
#include <cmath>
/*
        
           
        +---------------------720-----------------------+
        |												|
        |-----+---------------630-----------------------|    
        |      |       +----------600--------------+    |
        |      |       |                           |    |
        |    160	  360      GRASSPOSITION     1200 1280
        |      |       |                           |    |
        |      |       |                           |    |
        |      |       +----------110--------------+    |
        |      +----------------90----------------------|
        |      |                                        |    
        +-----+-----------------0-----------------------+
           |
        CARDBAR
*/
#define HEIGHT cocos2d::Director::getInstance()->getVisibleSize().height
#define WIDTH cocos2d::Director::getInstance()->getVisibleSize().width

#define VISIBLE_ORIGIN_X cocos2d::Director::getInstance()->getVisibleOrigin().x
#define VISIBLE_ORIGIN_Y cocos2d::Director::getInstance()->getVisibleOrigin().y

#define TOP HEIGHT * 7/8

#define GRASS_POSITION_LEFT WIDTH * 3/16
#define GRASS_POSITION_RIGHT WIDTH * 15/16
#define GRASS_POSITION_TOP HEIGHT * 7/8   
#define GRASS_POSITION_BOTTOM HEIGHT * 1/8

#define ROWW 5
#define COLUMNN	8

#define SIZE_OF_SQUARE std::fmin((GRASS_POSITION_RIGHT - GRASS_POSITION_LEFT) / COLUMNN, (GRASS_POSITION_TOP - GRASS_POSITION_BOTTOM) / ROWW)

#define GRASS_ORIGIN_POSITION_X (GRASS_POSITION_RIGHT + GRASS_POSITION_LEFT) / 2 - COLUMNN * SIZE_OF_SQUARE / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().x
#define GRASS_ORIGIN_POSITION_Y (GRASS_POSITION_TOP + GRASS_POSITION_BOTTOM) / 2 - ROWW * SIZE_OF_SQUARE / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().y

#define ROW_COLUMN_TO_POSITION(__ROW_COLUMN__) Vec2(GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * __ROW_COLUMN__.x + SIZE_OF_SQUARE/2, GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE * __ROW_COLUMN__.y + SIZE_OF_SQUARE/2)
#define POSITION_TO_ROW_COLUMN(__POSITION__) Vec2((-GRASS_ORIGIN_POSITION_X + __POSITION__.x - SIZE_OF_SQUARE/2) / SIZE_OF_SQUARE, (-GRASS_ORIGIN_POSITION_Y + __POSITION__.y - SIZE_OF_SQUARE/2) / SIZE_OF_SQUARE)
#define CELL_POSITION 1
#define CELL_CANT_POSITION 2
#define	LIMIT_TOP GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE * ROWW
#define LIMIT_RIGHT GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * COLUMNN


#define GRASS_INSIDE(__POSITION__,__X__,__Y__) (__POSITION__.x >= GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * __Y__ && __POSITION__.x <= GRASS_ORIGIN_POSITION_X + SIZE_OF_SQUARE * (__Y__ + 1) && __POSITION__.y >= GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE * __X__ && __POSITION__.y <= GRASS_ORIGIN_POSITION_Y + SIZE_OF_SQUARE * (__X__ + 1))
#define GRASS_OUTSIDE(__POSITION__) (__POSITION__.x < GRASS_ORIGIN_POSITION_X || __POSITION__.x > LIMIT_RIGHT || __POSITION__.y < GRASS_ORIGIN_POSITION_Y || __POSITION__.y > LIMIT_TOP)
//SIZE
#define ICON_SIZE HEIGHT / 24
#define NUMBER_SIZE ICON_SIZE*2/3
#define NUMBER_HEIGHT TOP + (HEIGHT - TOP - ICON_SIZE)/2 + ICON_SIZE/6
#define DISEA_WAY 3
//POSITION
#define ENERGY_POSITION Vec2((WIDTH/160),(TOP + (HEIGHT - TOP - ICON_SIZE)/2))

#define GOLD_POSITION Vec2((WIDTH/160 + WIDTH/5),(TOP + (HEIGHT - TOP - ICON_SIZE)/2))
#define DIAMOND_POSITION Vec2((WIDTH/160 + WIDTH*2/5),(TOP + (HEIGHT - TOP - ICON_SIZE)/2))







#endif // __GSDEFINE_H__