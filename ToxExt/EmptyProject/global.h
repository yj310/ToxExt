#pragma once
#include "page_manager.h"
#include "calculate_manager.h"
#include "file_manager.h"
#include "functions.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FLOOR_WIDTH 922
#define FLOOR_HEIGHT 648
#define FLOOR_PIXEL FLOOR_WIDTH * FLOOR_HEIGHT

#define GAME_X (WINDOW_WIDTH - FLOOR_WIDTH) / 2
#define GAME_Y WINDOW_HEIGHT - FLOOR_HEIGHT


#define BUTTON_WIDTH 160
#define BUTTON_HEIGHT 50
#define BUTTON_PADDING 10

#define BACK_BUTTON_X WINDOW_WIDTH - 180
#define BACK_BUTTON_Y WINDOW_HEIGHT - 60


#define MAP_EMPTY 0
#define MAP_EDGE 1
#define MAP_VISITED	2
#define MAP_VISITING 3
#define MAP_TEMP1 4
#define MAP_TEMP2 5
#define MAP_ENEMY_VISITED 6
#define MAP_ENEMY_EDGE 7
#define MAP_ENEMY_VISITING 8

#define SIZE_ENEMY 0
#define SPEED_ENEMY 1
#define MOVE_ENEMY 2


#define ITEM_SPEED 0
#define ITEM_KING 1
#define ITEM_HP 2
#define ITEM_SHOOT_1 3
#define ITEM_SHOOT_2 4
#define ITEM_SHOOT_3 5
#define ITEM_SHOOT_4 6


extern PageManager pageManager;
extern CalcManager calcManager;
extern FileManager fileManager;
extern int map[FLOOR_PIXEL];
extern int score;




struct Point
{
	int x;
	int y;
	Point(int x, int y)
		: x(x), y(y) {}
};

struct PlayerInfo
{
	int score;
	char name[128];
};

extern PlayerInfo playerInfo[6];