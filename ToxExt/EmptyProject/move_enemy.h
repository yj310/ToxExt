#pragma once
#include "enemy.h"

class MoveEnemy : public Enemy
{
public:

	MoveEnemy(D3DXVECTOR2 pos);
	virtual ~MoveEnemy();

	LPDIRECT3DTEXTURE9* enemyTex;
	LPD3DXSPRITE spr;

	int posX;
	int posY;

	int dirX;
	int dirY;

	int speed;
	int size = 14;
	bool isDead;

	int count;

	void Update() override;
	void Render() override;
	int getPosX() override { return posX; }
	int getPosY() override { return posY; }
	void Move() override { posX += dirX; posY += dirY; }
	int getSpeed() override { return speed; }
	void changeDirX() override { dirX *= -1; }
	void changeDirY() override { dirY *= -1; }
	int getSize() override { return size; }
	bool IsDead() { return isDead; }
	void Dead() { isDead = true; }
	int getClassType() override { return classType; }
	bool Crush(int x, int y) override
	{
		if (x >= posX && x <= posX + size
			&& y >= posY && y <= posY + size)
		{
			return true;
		}
		return false;
	}
	void deleteTextures() override
	{
		if ((*enemyTex) != nullptr && spr != nullptr)
		{
			(*enemyTex)->Release();
			spr->Release();
		}
		
	}

};