#include "DXUT.h"
#include "global.h"
#include "first_game_page.h"
#include "speed_enemy.h"
#include "size_enemy.h"
#include "move_enemy.h"
#include "super_emeny.h"
#include <stack>
#include <atlconv.h>
using namespace std;

FirstGamePage::FirstGamePage()
{
	keyCount = 0;
	player = new Player();
	superEnemy = new SuperEnemy();
	isCtrl = false;
	isVisiting = false;
	isFinish = false;
	isClear = false;
	visitingX = 0;
	visitingY = 0;

	temp1Count = 0;
	temp2Count = 0;
	myLand = 0;
	MaxLand = 0;
	persent = 0;
	timeCount = 0;
	stayCount = 0;
	itemCount = 0;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;

	startCount = (dwTimeCur - dwTimeStart) / 1000.0f;
	moveCount = 0;

	randIndex = 0;


	Load();
	for (int i = 0; i < 4; i++)
	{
		enemys.push_back(new SpeedEnemy(GetEnemyPos()));
	}

	enemys.push_back(new MoveEnemy(GetEnemyPos()));
	enemys.push_back(new SizeEnemy(GetEnemyPos()));



}

FirstGamePage::~FirstGamePage()
{

	(*backgroundTex)->Release();
	(*floorTex)->Release();
	(*basicMaskTex)->Release();
	(*badMaskTex)->Release();
	(*finishTex)->Release();
	(*clearTex)->Release();
	spr->Release();
	font->Release();
	timerFont->Release();

	for (int i = 0; i < enemys.size(); i++)
	{
		delete enemys[i];
	}
	enemys.clear();
	
	delete player;
	delete superEnemy;
}

D3DXVECTOR2 FirstGamePage::GetEnemyPos()
{
	int x;
	int y;
	while (true)
	{
		x = calcManager.getRand(++randIndex) % FLOOR_WIDTH;
		y = calcManager.getRand(++randIndex) % FLOOR_HEIGHT;
		if (map[y * FLOOR_WIDTH + x] == MAP_EMPTY)
		{
			break;
		}
	}
	return { (float)x, (float)y };
}

void FirstGamePage::Load()
{

	D3DXCreateFont(DXUTGetD3D9Device(), 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"³ª´®¹Ù¸¥°íµñ", &font);
	D3DXCreateFont(DXUTGetD3D9Device(), 45, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"³ª´®¹Ù¸¥°íµñ", &timerFont);



	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/firstGameBackground.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);

	floorTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/floor.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, floorTex);

	basicMaskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/mask1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, basicMaskTex);

	badMaskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/mask3.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, badMaskTex);

	finishTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/isDead.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, finishTex);

	clearTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/isClear.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, clearTex);


	D3DLOCKED_RECT lr;
	RECT rc = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(floorP, p, FLOOR_PIXEL * sizeof(DWORD));
		(*floorTex)->UnlockRect(0);
	}

	if (SUCCEEDED((*basicMaskTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(basicMaskP, p, FLOOR_PIXEL * sizeof(DWORD));
		(*basicMaskTex)->UnlockRect(0);
	}

	if (SUCCEEDED((*badMaskTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(badMaskP, p, FLOOR_PIXEL * sizeof(DWORD));
		(*badMaskTex)->UnlockRect(0);
	}

	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		map[i] = MAP_EMPTY;
	}

	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		map[y * FLOOR_WIDTH + 0] = MAP_EDGE;
		map[y * FLOOR_WIDTH + FLOOR_WIDTH - 1] = MAP_EDGE;
	}

	for (int x = 0; x < FLOOR_WIDTH; ++x)
	{
		map[0 * FLOOR_WIDTH + x] = MAP_EDGE;
		map[(FLOOR_HEIGHT - 1) * FLOOR_WIDTH + x] = MAP_EDGE;
	}

	MapUpdate();


	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}

void FirstGamePage::MapUpdate()
{
	D3DLOCKED_RECT lr;
	RECT rc = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rc, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;


		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (map[i] == MAP_EMPTY)
			{
				p[i] = basicMaskP[i];
			}
			else if (map[i] == MAP_EDGE)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
			else if (map[i] == MAP_VISITED)
			{
				p[i] = floorP[i];
			}
			else if (map[i] == MAP_VISITING)
			{// green
				p[i] = D3DCOLOR_ARGB(255, 0, 255, 0);
			}
			else if (map[i] == MAP_TEMP1)
			{// red
				p[i] = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
			else if (map[i] == MAP_TEMP2)
			{// blue
				p[i] = D3DCOLOR_ARGB(255, 0, 0, 255);
			}
			else if (map[i] == MAP_ENEMY_VISITED)
			{
				p[i] = badMaskP[i];
				//p[i] = D3DCOLOR_ARGB(50, 255, 255, 255);
			}
			else if (map[i] == MAP_ENEMY_VISITING)
			{//majenta
				p[i] = D3DCOLOR_ARGB(255, 255, 0, 255);;
			}
			else if (map[i] == MAP_ENEMY_EDGE)
			{
				p[i] = D3DCOLOR_ARGB(255, 0, 255, 255);;
			}
		}


		(*floorTex)->UnlockRect(0);
	}

}


void FirstGamePage::GetKeyInput()
{
	// space
	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
	{
		isCtrl = true;
	}
	else
	{
		isCtrl = false;
		if (isVisiting)
		{
			PlayerMoveFail();
		}
	}




	// left
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = {-1, 0};
		PlayerMove(dir);
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = {1, 0};
		PlayerMove(dir);
	}
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = {0, -1};
		PlayerMove(dir);
	}
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = {0, 1};
		PlayerMove(dir);
	}
}


void FirstGamePage::PlayerMove(D3DXVECTOR2 dir)
{
	for (int i = 0; i < player->getSpeed(); ++i)
	{
		int x = player->getPosX();
		int y = player->getPosY();
		int nextX = x + dir.x;
		int nextY = y + dir.y;

		if (nextX >= 0 && nextX < FLOOR_WIDTH
			&& nextY >= 0 && nextY < FLOOR_HEIGHT)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_VISITED
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_VISITED)
			{
				player->Move(dir.x, dir.y);
				stayCount = 0;
			}
			else if ((map[y * FLOOR_WIDTH + x] == MAP_EDGE || map[y * FLOOR_WIDTH + x] == MAP_VISITED)
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
			{
				player->Move(dir.x, dir.y);
				stayCount = 0;
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_EDGE
				&& isEmpty(map[nextY * FLOOR_WIDTH + nextX])
				&& isCtrl)
			{
				moveCount = 0;
				visitingX = x;
				visitingY = y;
				isVisiting = true;
				map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING; 
				moveCount++;
				player->Move(dir.x, dir.y);
				stayCount = 0;
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_VISITING
				&& isEmpty(map[nextY * FLOOR_WIDTH + nextX])
				&& isCtrl)
			{
				if (!(moveCount > player->getMaxMove()))
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					moveCount++;
					player->Move(dir.x, dir.y);
					stayCount = 0;
				}
				
			}
			else if (map[y * FLOOR_WIDTH + x] == MAP_VISITING
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
				&& isCtrl)
			{
				isVisiting = false;
				player->Move(dir.x, dir.y);
				stayCount = 0;
				moveCount = 0;
				GetLand();
			}
			
		}
		else
		{
			break;
		}
	}
}


void FirstGamePage::GetLand()
{
	for (int i = 0; i < FLOOR_PIXEL; i++)
	{
		prevMap[i] = map[i];
	}
	temp1Count = 0;
	temp2Count = 0;
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (isEmpty(map[i]))
		{
			virtualMap[i] = MAP_TEMP1; 
			temp1Count++;
		}
		else
			virtualMap[i] = map[i];
	}

	FloodFill();
	if (temp1Count > temp2Count)
	{
		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (virtualMap[i] == MAP_TEMP1)
				map[i] = prevMap[i];
			else if (virtualMap[i] == MAP_TEMP2)
				map[i] = MAP_VISITED;
			else if (virtualMap[i] == MAP_VISITING)
				map[i] = MAP_EDGE;
			else
				map[i] = prevMap[i];

		}
	}
	else 
	{
		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (virtualMap[i] == MAP_TEMP2)
				map[i] = prevMap[i];
			else if (virtualMap[i] == MAP_TEMP1)
				map[i] = MAP_VISITED;
			else if (virtualMap[i] == MAP_VISITING)
				map[i] = MAP_EDGE;
			else
				map[i] = prevMap[i];

		}
	}

	Bordering();

	KillEnemy();
	//itemCount++;

}


void FirstGamePage::FloodFill()
{
	stack<Point> points;
	isFound = false;
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		if (isFound)
			break;
		for (int x = 0; x < FLOOR_WIDTH; ++x)
		{
			if (virtualMap[y * FLOOR_WIDTH + x] == MAP_TEMP1)
			{
				points.push(Point(x, y));
				isFound = true;
				break;
			}
		}
	}
	

	//points.push(Point(superEnemy->getPosX(), superEnemy->getPosY()));

	while (!points.empty())
	{
		Point p = points.top();
		points.pop();

		if (p.x < 0 || p.x >= FLOOR_WIDTH
			|| p.y < 0 || p.y >= FLOOR_HEIGHT)
			continue;

		if (virtualMap[p.y * FLOOR_WIDTH + p.x] == MAP_TEMP1)
		{
			virtualMap[p.y * FLOOR_WIDTH + p.x] = MAP_TEMP2;
			temp1Count--;
			temp2Count++;
		}
		else
			continue;

		

		points.push(Point(p.x - 1, p.y));
		points.push(Point(p.x + 1, p.y));
		points.push(Point(p.x, p.y - 1));
		points.push(Point(p.x, p.y + 1));
	}
	
}

bool FirstGamePage::isEmpty(int i)
{
	if (i == MAP_EMPTY || i == MAP_ENEMY_EDGE || i == MAP_ENEMY_VISITING || i == MAP_ENEMY_VISITED)
	{
		return true;
	}
	return false;
}

void FirstGamePage::Bordering()
{
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		for (int x = 0; x < FLOOR_WIDTH; ++x)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_EDGE)
			{
				int top_left = map[(y - 1) * FLOOR_WIDTH + x - 1];
				int top = map[(y - 1) * FLOOR_WIDTH + x];
				int top_right = map[(y - 1) * FLOOR_WIDTH + x + 1];

				int left = map[y * FLOOR_WIDTH + x - 1];
				int right = map[y * FLOOR_WIDTH + x + 1];

				int botton_left = map[(y + 1) * FLOOR_WIDTH + x - 1];
				int botton = map[(y + 1) * FLOOR_WIDTH + x];
				int botton_right = map[(y + 1) * FLOOR_WIDTH + x + 1];

				/*
				if (y - 1 > 0)
				{
					if (x - 1 > 0)
					{
						if (top_left == MAP_EMPTY)
							continue;
					}
					if (top == MAP_EMPTY)
						continue;
					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (top_right == MAP_EMPTY)
							continue;
					}
				}


				if (x - 1 > 0)
				{
					if (left == MAP_EMPTY )
						continue;
				}

				if (x + 1 < FLOOR_WIDTH - 1)
				{
					if (right == MAP_EMPTY)
						continue;
				}

				if (y + 1 < FLOOR_HEIGHT - 1)
				{
					if (x - 1 > 0)
					{
						if (botton_left == MAP_EMPTY )
							continue;
					}

					if (botton == MAP_EMPTY )
						continue;

					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (botton_right == MAP_EMPTY)
							continue;
					}
				}
				*/


				if (y - 1 > 0)
				{
					if (x - 1 > 0)
					{
						if (isEmpty(top_left))
							continue;
					}
					if (isEmpty(top))
						continue;
					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (isEmpty(top_right))
							continue;
					}
				}


				if (x - 1 > 0)
				{
					if (isEmpty(left))
						continue;
				}

				if (x + 1 < FLOOR_WIDTH - 1)
				{
					if (isEmpty(right))
						continue;
				}

				if (y + 1 < FLOOR_HEIGHT - 1)
				{
					if (x - 1 > 0)
					{
						if (isEmpty(botton_left))
							continue;
					}

					if (isEmpty(botton))
						continue;

					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (isEmpty(botton_right))
							continue;
					}
				}

				map[y * FLOOR_WIDTH + x] = MAP_VISITED;
			}
		}
	}
}


void FirstGamePage::GetPersent()
{
	MaxLand = 0;
	myLand = 0;
	for (int y = 1; y < FLOOR_HEIGHT - 1; y++)
	{
		for (int x = 1; x < FLOOR_WIDTH - 1; x++)
		{
			MaxLand++;
			if (map[y * FLOOR_WIDTH + x] == MAP_VISITED
				|| map[y * FLOOR_WIDTH + x] == MAP_EDGE)
			{
				myLand++;
			}
		}
	}

	persent = (float)myLand / (float)MaxLand * 100;


}

void FirstGamePage::PlayerMoveFail()
{
	moveCount = 0;
	player->setPos(visitingX, visitingY);
	isVisiting = false;
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_VISITING)
		{
			map[i] = MAP_EMPTY;
		}
	}
}

void FirstGamePage::crush()
{
	for (int i = 0; i < FLOOR_PIXEL; i++)
	{
		if (map[i] == MAP_VISITING)
		{
			for (int j = 0; j < enemys.size(); j++)
			{
				if (calcManager.pointBySqare(i % FLOOR_WIDTH, i / FLOOR_WIDTH, enemys[j]->getPosX(), enemys[j]->getPosY(), enemys[j]->getSize()))
				{
					player->Damage(1);
					PlayerMoveFail();

				}
			}
		}
	}
	
}


void FirstGamePage::EnemyMove()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		
		for (int j = 0; j < enemys[i]->getSpeed(); j++)
			{
				enemys[i]->Move();
				for (int y = 0; y < FLOOR_HEIGHT; y++)
				{
					for (int x = 0; x < FLOOR_WIDTH; x++)
					{
						if (map[y * FLOOR_WIDTH + x] == MAP_EDGE)
						{
							if (enemys[i]->Crush(x, y))
							{
								if (x - 1 >= 0 && map[y * FLOOR_WIDTH + x - 1] == MAP_EMPTY
									|| x - 1 < 0)
								{
									enemys[i]->changeDirX();
								}
								else if (x + 1 < FLOOR_WIDTH && map[y * FLOOR_WIDTH + x + 1] == MAP_EMPTY
									|| x + 1 >= FLOOR_WIDTH)
								{
									enemys[i]->changeDirX();
								}
								if (y - 1 >= 0 && map[(y - 1) * FLOOR_WIDTH + x] == MAP_EMPTY
									|| y - 1 < 0)
								{
									enemys[i]->changeDirY();
								}
								else if (y + 1 < FLOOR_HEIGHT && map[(y + 1) * FLOOR_WIDTH + x] == MAP_EMPTY
									|| y + 1 >= FLOOR_HEIGHT)
								{
									enemys[i]->changeDirY();
								}
							}
						}

					}
				}
			}
		
		
	}
}

void FirstGamePage::KillEnemy()
{
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		for (int x = 0; x < FLOOR_WIDTH; ++x)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_VISITED)
			{
				for (auto iter = enemys.begin(); iter != enemys.end(); ++iter)
				{
					if (calcManager.pointBySqare(x, y, (*iter)->getPosX(), (*iter)->getPosY(), (*iter)->getSize()))
					{
						(*iter)->deleteTextures();
						enemys.erase(iter);
						player->addMoveGage();
						int a = calcManager.getRand(DXUTGetTime()) % 5;
						if (a == 0)
						{
							enemys.push_back(new SizeEnemy(GetEnemyPos()));
						}
						else if (a == 1)
						{
							enemys.push_back(new MoveEnemy(GetEnemyPos()));
						}
						else
						{
							enemys.push_back(new SpeedEnemy(GetEnemyPos()));
						}
						score += 2000;
						if (enemys.size() <= 2)
						{
							for (int i = 0; i < 4; i++)
							{
								enemys.push_back(new SpeedEnemy(GetEnemyPos()));
							}

							enemys.push_back(new MoveEnemy(GetEnemyPos()));
							enemys.push_back(new SizeEnemy(GetEnemyPos()));
						}

						player->setSpeed(player->getSpeed() + 1);
						player->setHP(player->getHP() + 1);
					}

				}
				if (calcManager.pointBySqare(x, y, superEnemy->getPosX(), superEnemy->getPosY(), superEnemy->getSize()))
				{

					score += 20000;
					isClear = true;
				}

				
			}
		}
	}
}

void FirstGamePage::Cheat()
{
	if (keyCount > 0)
		keyCount--;
	if (keyCount <= 0)
	{
		if ((GetAsyncKeyState(VK_F1) & 0x8000) != 0)
		{
			if (player->IsNotDamage())
			{
				player->SetIsNotDamage(false);
			}
			else if (!player->IsNotDamage())
			{
				player->SetIsNotDamage(true);
			}
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F3) & 0x8000) != 0)
		{
			player->setHP(player->getHP() + 1);
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F4) & 0x8000) != 0)
		{
			player->Damage(1);
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F5) & 0x8000) != 0)
		{
			player->addMoveGage();
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F6) & 0x8000) != 0)
		{
			player->setMoveGage(player->getMaxMove() - 20);
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F9) & 0x8000) != 0)
		{
			isClear = true;
			keyCount = 20;
		}
		if ((GetAsyncKeyState(VK_F10) & 0x8000) != 0)
		{
			keyCount = 20;
			pageManager.CreateTitlePage();
			
		}
	}
	
}
void FirstGamePage::Update()
{
	if (!isFinish && !isClear)
	{
		if (persent >= 80.0)
		{
			isClear = true;
			/*for (int i = 0; i < FLOOR_PIXEL; i++)
			{
				map[i] = MAP_VISITED;
			}*/
		}

		if (itemCount > 5)
		{
			//items.push_back(new Item(calcManager.getRand(DXUTGetTime()), player->getPosX(), player->getPosY()));
		}
		int prevX = player->getPosX();
		int prevY = player->getPosY();

		if (player->getHP() <= 0
			|| timeCount >= 180)
		{
			isFinish = true;
		}
		/*for (int i = 0; i < items.size(); i++)
		{
			items[i]->Update();
		}*/
		for (int i = 0; i < enemys.size(); i++)
		{
			enemys[i]->Update();
		}
		superEnemy->Update();
		player->Update();
		EnemyMove();
		crush();
		

		GetKeyInput();
		MapUpdate();

		GetPersent();
		if (prevX == player->getPosX() && prevY == player->getPosY())
		{
			stayCount++;
		}
		if (stayCount >= 100)
		{
			player->Damage(1);
			stayCount = 0;
		}
		if (player->getHP() > player->getMapHP())
		{
			score += (player->getHP() - player->getMapHP()) * 2000;
			player->setHP(player->getMapHP());
		}

		

		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;

		timeCount = (dwTimeCur - dwTimeStart) / 1000.0f;
		timeCount -= startCount;


		Cheat();
	}
	else if (isFinish)
	{
		if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0)
		{
			pageManager.CreateTitlePage();
		}
	} 
	else if (isClear)
	{
		if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0)
		{
			score += myLand;
			pageManager.CreateSecondGamePage();
		}
	}
}

void FirstGamePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;


	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	pos = { GAME_X, GAME_Y, 0 };
	spr->Draw(*floorTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();


	/*for (int i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}*/
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Render();
	}
	superEnemy->Render();
	player->Render();




	USES_CONVERSION;
	int ivalue; int ivalue2;
	float fvalue;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc;



	
	/*iscore = MaxLand;
	sprintf(cscore, "%d", iscore);
	wscore = A2W(cscore);
	rc = { 0, 50, 200, 200 };
	font->DrawText(NULL, wscore, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/

	ivalue = score + myLand;
	sprintf_s(cvalue, "%d", ivalue);
	wvalue = A2W(cvalue);
	rc = { 10, 150, WINDOW_WIDTH, WINDOW_HEIGHT };
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



	fvalue = persent;
	sprintf_s(cvalue, "%.1f%%", fvalue);
	wvalue = A2W(cvalue);
	rc = { 0, 500, WINDOW_WIDTH - 10, WINDOW_HEIGHT };
	timerFont->DrawText(NULL, wvalue, -1, &rc, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	fvalue = superEnemy->returnPersent();
	sprintf_s(cvalue, "%.1f%%", fvalue);
	wvalue = A2W(cvalue);
	rc = { 0, 600, WINDOW_WIDTH - 10, WINDOW_HEIGHT };
	timerFont->DrawText(NULL, wvalue, -1, &rc, DT_RIGHT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	
	ivalue = (timer - timeCount) / 60;
	ivalue2 = (timer - timeCount) % 60;
	sprintf_s(cvalue, "%d:%02d", ivalue, ivalue2);
	wvalue = A2W(cvalue);
	rc = { 1175, 20, WINDOW_WIDTH, WINDOW_HEIGHT };
	timerFont->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	


	ivalue = moveCount;
	sprintf_s(cvalue, "%d/%d", ivalue, player->getMaxMove());
	wvalue = A2W(cvalue);
	rc = { 0, 500, WINDOW_WIDTH, WINDOW_HEIGHT };
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	if (isFinish)
	{
		spr->Begin(D3DXSPRITE_ALPHABLEND);
		spr->Draw(*finishTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		spr->End();
	}
	if (isClear)
	{
		spr->Begin(D3DXSPRITE_ALPHABLEND);
		spr->Draw(*clearTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		spr->End();
	}


}