#pragma once

class Item
{
public:
	Item(int itemType, int posX, int posY);
	~Item();
	int itemType;

	int itemCount;
	int itemMaxCount;
	int posX;
	int posY;
	int size;


	LPDIRECT3DTEXTURE9* itemTex;
	LPD3DXSPRITE spr;

	void Update();
	void Render();


	void CalcPos();




};