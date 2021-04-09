#pragma once

class Enemy
{
public:

	int posX;
	int posY;
	int dirX;
	int dirY;
	int speed;
	int size;
	bool isDead;
	int classType;

	virtual ~Enemy() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0; 
	virtual void Move() = 0;
	virtual int getSpeed() = 0;
	virtual void changeDirX() = 0;
	virtual void changeDirY() = 0;
	virtual int getSize() = 0;
	virtual bool Crush(int x, int y) = 0;
	virtual bool IsDead() = 0;
	virtual void Dead() = 0;
	virtual int getClassType() = 0;
	virtual void deleteTextures() = 0;
};