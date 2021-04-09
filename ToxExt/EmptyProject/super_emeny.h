#pragma once
#include "enemy.h"
#include "global.h"

class SuperEnemy
{
public:

	SuperEnemy();
	virtual ~SuperEnemy();

	LPDIRECT3DTEXTURE9* enemyTex;
	LPD3DXSPRITE spr;

	int posX;
	int posY;

	int dirX;
	int dirY;
	int dirXCount;
	int dirYCount;

	int speed;
	int size = 20;
	bool isDead;

	int visitingX;
	int visitingY;
	bool isVisiting = false;
	int moveCount = 0;
	int maXMove;

	int temp1Count;
	int temp2Count;
	int virtualMap[FLOOR_PIXEL];

	bool isFound;

	int randIndex;
	int myLand;
	int MaxLand;
	float persent;

	void Update();
	void Render();
	int getPosX() { return posX; }
	int getPosY() { return posY; }
	void Move();
	int getSpeed() { return speed; }
	void changeDirX() { dirX *= -1; }
	void changeDirY() { dirY *= -1; }
	int getSize() { return size; }
	void IsDead() { isDead = true; }
	bool Crush(int x, int y)
	{
		if (x >= posX && x <= posX + size
			&& y >= posY && y <= posY + size)
		{
			return true;
		}
		return false;
	}


	void GetLand();
	void FloodFill();
	void Bordering();
	void calcDir();
	void MoveFail();
	void MoveFllowKey();
	void GetPersent();
	float returnPersent() { return persent; }
};