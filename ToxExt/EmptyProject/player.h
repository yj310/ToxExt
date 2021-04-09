#pragma once

class Player
{
public:
	
	Player();
	~Player();

	int posX;
	int posY;
	int speed;
	int hp;
	int maxMove;
	int maxHP;
	bool isNotDamage;

	int randIndex;

	LPDIRECT3DTEXTURE9* playerTex;
	LPDIRECT3DTEXTURE9* hpTex;
	LPD3DXSPRITE spr;


	void Move(int x, int y) { posX += x; posY += y; }
	D3DXVECTOR2 getPos() { return { (float)posX, (float)posY }; }
	int getPosX() { return posX; }
	int getPosY() { return posY; }
	void setPos(int x, int y) { posX = x; posY = y; }
	int getSpeed() { return speed; }
	void setSpeed(int speed) { speed = speed; }
	int getMaxMove() { return maxMove; }
	void Damage(int damage) { if(!isNotDamage)hp -= damage; }
	int getHP() { return hp; }
	int getMapHP() { return maxHP; }
	void setHP(int hp) { this->hp = hp; }
	void addMoveGage() { maxMove += 20; }
	void setMoveGage(int gage) { maxMove = gage; }
	void SetIsNotDamage(bool is) { isNotDamage = is; }
	bool IsNotDamage() { return isNotDamage; }



	void Update();
	void Render();

};