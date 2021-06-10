#pragma once
#include "page.h"
#include "global.h"
#include "player.h"
#include "enemy.h"
#include "super_emeny.h"
#include "item.h"
#include <vector>
using namespace std;

class FirstGamePage : public Page
{
public:

	FirstGamePage();
	virtual ~FirstGamePage();

	Player* player;
	vector<Enemy*> enemys;
	SuperEnemy* superEnemy;
	//vector<Item*> items;
	bool isCtrl;
	bool isVisiting;
	bool isFinish;
	bool isFound;
	bool isClear;

	int visitingX;
	int visitingY;
	
	int temp1Count;
	int temp2Count;
	int myLand;
	int MaxLand;
	float persent;
	int timeCount;
	int startCount;
	int moveCount;
	int stayCount;

	int itemCount;
	int speedECount;
	int sizeECount;
	int moveECount;

	int randIndex;

	int timer = 3 * 60;

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* basicTex;
	LPDIRECT3DTEXTURE9* floorTex;
	LPDIRECT3DTEXTURE9* basicMaskTex;
	LPDIRECT3DTEXTURE9* badMaskTex;
	LPDIRECT3DTEXTURE9* finishTex;
	LPDIRECT3DTEXTURE9* clearTex;
	LPDIRECT3DTEXTURE9* timerFrameTex;
	LPDIRECT3DTEXTURE9* timerFillTex;
	LPD3DXSPRITE spr;


	DWORD floorP[FLOOR_PIXEL];
	DWORD basicMaskP[FLOOR_PIXEL];
	DWORD badMaskP[FLOOR_PIXEL];

	int virtualMap[FLOOR_PIXEL];
	int prevMap[FLOOR_PIXEL];

	ID3DXFont* font; 
	ID3DXFont* timerFont;
	ID3DXFont* titleFont;
	ID3DXFont* persentFont;
	ID3DXFont* scoreFont;

	void Load();

	void MapUpdate();
	void GetKeyInput();
	void PlayerMove(D3DXVECTOR2 dir);
	void GetLand();
	void FloodFill();
	void Bordering();
	void GetPersent();
	void PlayerMoveFail();
	void EnemyMove();
	void KillEnemy();
	bool isEmpty(int i);
	void Cheat();

	int keyCount;
	void crush();

	D3DXVECTOR2 GetEnemyPos();





	void Update() override;
	void Render() override;



}; 
