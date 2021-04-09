#include "DXUT.h"
#include "size_enemy.h"
#include "global.h"
#include <random>

SizeEnemy::SizeEnemy(D3DXVECTOR2 pos)
{
	classType = SIZE_ENEMY;
	srand(timeGetTime());
	posX = pos.x;
	posY = pos.y;
	dirX = (calcManager.getRand(posX) % 2) == 0 ? 1 : -1;;
	dirY = (calcManager.getRand(posX) % 2) == 0 ? 1 : -1;;
	speed = 1;
	size = 60;
	isDead = false;
	enemyTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/sizeEnemy.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, enemyTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}


SizeEnemy::~SizeEnemy()
{
	if ((*enemyTex) != nullptr && spr != nullptr)
	{
		(*enemyTex)->Release();
		spr->Release();
	}
}

void SizeEnemy::Update()
{
	if (!isDead)
	{
		if (posX <= 0)
		{
			posX = 1;
		}
		if (posX + size >= FLOOR_WIDTH - 1)
		{
			posX = FLOOR_WIDTH - 2 - size;
		}
		if (posY <= 0)
		{
			posY = 1;
		}
		if (posY + size >= FLOOR_HEIGHT - 1)
		{
			posY = FLOOR_HEIGHT - 2 - size;
		}
	}
}


void SizeEnemy::Render()
{
	if (!isDead) {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 cen;


		spr->Begin(D3DXSPRITE_ALPHABLEND);

		pos = { (float)GAME_X + posX, (float)GAME_Y + posY, 0 };
		spr->Draw(*enemyTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		spr->End();
	}
}

