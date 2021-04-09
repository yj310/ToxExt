#include "DXUT.h"
#include "item.h"
#include "global.h"

Item::Item(int itemType, int posX, int posY)
{
	itemMaxCount = 200;
	itemCount = itemMaxCount;

	this->posX = posX;
	this->posY = posY;
	CalcPos();
	this->itemType = itemType;
	itemTex = new LPDIRECT3DTEXTURE9();
	switch (itemType)
	{
	case 1:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);

		break;
	case 2:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);
		break;
	case 3:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);
		break;
	case 4:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);
		break;
	case 5:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);
		break;
	case 6:
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device()
			, "resource/image/item1.png"
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 0, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0, nullptr, nullptr
			, itemTex);
		break;
	}
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}

Item::~Item()
{
	(*itemTex)->Release();
	spr->Release();
}


void Item::CalcPos()
{
	int i = 1;
	while (true)
	{  
		i++;
		/*if (posY + (10 * 1) < FLOOR_HEIGHT && map[(posY + (10 * 1)) * FLOOR_WIDTH + posX] == MAP_EMPTY)
		{
			posY += 10 * i;
			return;
		}
		if (posY - (10 * i) >= 0 && map[(posY - (10 * i)) * FLOOR_WIDTH + posX] == MAP_EMPTY)
		{
			posY -= (10 * i);
			return;
		}
		if (posX + (10 * 1) < FLOOR_WIDTH && map[posY * FLOOR_WIDTH + posX + (10 * 1)] == MAP_EMPTY)
		{
			posX += 10 * i;
			return;
		}
		if (posX - (10 * i) >= 0 && map[(posY + 10) * FLOOR_WIDTH + posX] == MAP_EMPTY)
		{
			posX -= (10 * i);
			return;
		}*/
		int x = posX + (calcManager.getRand(DXUTGetTime() + i) % 50) - 25;
		int y = posY + (calcManager.getRand(DXUTGetTime() + i + 1000) % 50) - 25;

		if (x >= 0 && x < FLOOR_WIDTH && y >= 0 && y < FLOOR_HEIGHT)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_EMPTY)
			{
				posX = x;
				posY = y;
				return;  
			}
		}
	}
}

void Item::Update()
{
	itemCount--;
}

void Item::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;


	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { (float)GAME_X + posX, (float)GAME_Y + posY, 0 };

	
	spr->Draw(*itemTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();
}
