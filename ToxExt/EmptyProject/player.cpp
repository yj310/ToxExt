#include "DXUT.h"
#include "player.h"
#include "global.h"

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20

Player::Player()
{
	isNotDamage = false;
	randIndex = 200;
	int a = calcManager.getRand(++randIndex) % 2;
	int b = calcManager.getRand(++randIndex) % 2;
	if (a == 0)
	{
		posX = calcManager.getRand(++randIndex) % FLOOR_WIDTH;
		if (b == 0)
		{
			posY = 0;
		}
		else
		{
			posY = FLOOR_HEIGHT - 1;
		}
	}
	else
	{
		posY = calcManager.getRand(++randIndex) % FLOOR_HEIGHT;
		if (b == 0)
		{
			posX = 0;
		}
		else
		{
			posX = FLOOR_WIDTH - 1;
		}
	}

	speed = 2;
	hp = 5;
	maxMove = 200;
	maxHP = 5;
	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/player1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, playerTex);
	hpTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/hp.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, hpTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}


Player::~Player()
{
	(*playerTex)->Release();
	(*hpTex)->Release();
	spr->Release();
}


void Player::Update()
{
	if (posX < 0)
		posX = 0;
	if (posX >= FLOOR_WIDTH)
		posX = FLOOR_WIDTH - 1;
	if (posY < 0)
		posY = 0;
	if (posY >= FLOOR_HEIGHT)
		posY = FLOOR_HEIGHT - 1;

	
}


void Player::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { (float)GAME_X + posX - (PLAYER_WIDTH / 2), (float)GAME_Y + posY - (PLAYER_HEIGHT / 2), 0 };
	spr->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	for (int i = 0; i < hp; i++)
	{
		pos = {1180, (float)200 + (25 * i), 0 };
		if(isNotDamage)
			spr->Draw(*hpTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
		else
			spr->Draw(*hpTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	spr->End();
}
