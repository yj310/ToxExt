#include "DXUT.h"
#include "super_emeny.h"
#include "global.h"
#include <stack>

using namespace std;

SuperEnemy::SuperEnemy()
{
	randIndex = 100;
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
	//posX = 600; posY = 350;
	dirX = 1;
	dirY = 0;
	dirXCount = 0;
	dirYCount = 0;
	maXMove = 200;
	persent = 0.0;
	myLand = 0;
	MaxLand = 0;

	speed = 2;
	isDead = false;
	enemyTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/superEnemy.png"
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

SuperEnemy::~SuperEnemy()
{
	(*enemyTex)->Release();
	spr->Release();
}

void SuperEnemy::GetLand()
{
	temp1Count = 0;
	temp2Count = 0;
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_EMPTY)
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
				map[i] = MAP_EMPTY;
			else if (virtualMap[i] == MAP_TEMP2)
				map[i] = MAP_ENEMY_EDGE;
			else if (virtualMap[i] == MAP_ENEMY_VISITING)
				map[i] = MAP_ENEMY_EDGE;
			else
				map[i] = virtualMap[i];

		}
	}
	else
	{
		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (virtualMap[i] == MAP_TEMP2)
				map[i] = MAP_EMPTY;
			else if (virtualMap[i] == MAP_TEMP1)
				map[i] = MAP_ENEMY_EDGE;
			else if (virtualMap[i] == MAP_ENEMY_VISITING)
				map[i] = MAP_ENEMY_EDGE;
			else
				map[i] = virtualMap[i];

		}
	}

	Bordering();


}


void SuperEnemy::FloodFill()
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

void SuperEnemy::GetPersent()
{
	MaxLand = 0;
	myLand = 0;
	for (int y = 1; y < FLOOR_HEIGHT - 1; y++)
	{
		for (int x = 1; x < FLOOR_WIDTH - 1; x++)
		{
			MaxLand++;
			if (map[y * FLOOR_WIDTH + x] == MAP_ENEMY_EDGE
				|| map[y * FLOOR_WIDTH + x] == MAP_ENEMY_VISITED)
			{
				myLand++;
			}
		}
	}

	persent = (float)myLand / (float)MaxLand * 100;


}

void SuperEnemy::Bordering()
{
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		for (int x = 0; x < FLOOR_WIDTH; ++x)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_ENEMY_EDGE)
			{
				int top_left = map[(y - 1) * FLOOR_WIDTH + x - 1];
				int top = map[(y - 1) * FLOOR_WIDTH + x];
				int top_right = map[(y - 1) * FLOOR_WIDTH + x + 1];

				int left = map[y * FLOOR_WIDTH + x - 1];
				int right = map[y * FLOOR_WIDTH + x + 1];

				int botton_left = map[(y + 1) * FLOOR_WIDTH + x - 1];
				int botton = map[(y + 1) * FLOOR_WIDTH + x];
				int botton_right = map[(y + 1) * FLOOR_WIDTH + x + 1];

				if (y - 1 > 0)
				{
					if (x - 1 > 0)
					{
						if (top_left == MAP_EMPTY)
						{
							continue;
						}
					}
					if (top == MAP_EMPTY)
					{
						continue;
					}
					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (top_right == MAP_EMPTY)
						{
							continue;
						}
					}
				}


				if (x - 1 > 0)
				{
					if (left == MAP_EMPTY)
					{
						continue;
					}
				}

				if (x + 1 < FLOOR_WIDTH - 1)
				{
					if (right == MAP_EMPTY)
					{
						continue;
					}
				}

				if (y + 1 < FLOOR_HEIGHT - 1)
				{
					if (x - 1 > 0)
					{
						if (botton_left == MAP_EMPTY)
						{
							continue;
						}
					}

					if (botton == MAP_EMPTY)
					{
						continue;
					}

					if (x + 1 < FLOOR_WIDTH - 1)
					{
						if (botton_right == MAP_EMPTY)
						{
							continue;
						}
					}
				}
				map[y * FLOOR_WIDTH + x] = MAP_ENEMY_VISITED;


			}
		}
	}
}

void SuperEnemy::calcDir()
{
	if (dirX != 0)
	{
		if (dirXCount == 0)
		{
			dirX = 0;
			dirY = calcManager.getRand(DXUTGetTime()) % 2 == 0 ? 1 : -1;
			if (map[(posY + dirY) * FLOOR_WIDTH + posX] != MAP_EMPTY)
				dirY *= -1;
			dirYCount = calcManager.getRand(DXUTGetTime()) % 30 + 5;
		}
		else
		{
			Move();
			dirXCount--;
			
		}
	}
	else if (dirY != 0)
	{
		if (dirYCount == 0)
		{
			dirY = 0;
			dirX = calcManager.getRand(DXUTGetTime()) % 2 == 0 ? 1 : -1; 
			if (map[posY * FLOOR_WIDTH + posX + dirX] != MAP_EMPTY)
				dirX *= -1;
			dirXCount = calcManager.getRand(DXUTGetTime()) % 30 + 5;
		}
		else
		{
			Move();
			dirYCount--;
		
		}
	}
	
}

void SuperEnemy::Move()
{
	for (int i = 0; i < speed; ++i)
	{
		int prevX = posX;
		int prevY = posY;
		int nextX = posX + dirX;
		int nextY = posY + dirY;

		if (nextX >= 0 && nextX < FLOOR_WIDTH
			&& nextY >= 0 && nextY < FLOOR_HEIGHT)
		{
			if ((map[posY * FLOOR_WIDTH + posX] == MAP_EDGE || map[posY * FLOOR_WIDTH + posX] == MAP_ENEMY_EDGE || map[posY * FLOOR_WIDTH + posX] == MAP_ENEMY_VISITED)
				&& (map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE || map[nextY * FLOOR_WIDTH + nextX] == MAP_ENEMY_EDGE))
			{
				posX += dirX;
				posY += dirY;
			}
			else if ((map[posY * FLOOR_WIDTH + posX] == MAP_EDGE || map[posY * FLOOR_WIDTH + posX] == MAP_ENEMY_EDGE)
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY)
			{
				moveCount = 0;
				visitingX = posX;
				visitingY = posY;
				isVisiting = true;
				map[nextY * FLOOR_WIDTH + nextX] = MAP_ENEMY_VISITING;
				moveCount++;
				posX += dirX;
				posY += dirY;
			}
			else if (map[posY * FLOOR_WIDTH + posX] == MAP_ENEMY_VISITING
				&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY)
			{
				if (!(moveCount > maXMove))
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_ENEMY_VISITING;
					moveCount++;
					posX += dirX;
					posY += dirY;
				}
				else
				{
					MoveFail();
				}

			}
			else if (map[posY * FLOOR_WIDTH + posX] == MAP_ENEMY_VISITING
				&& (map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE || map[nextY * FLOOR_WIDTH + nextX] == MAP_ENEMY_EDGE))
			{
				isVisiting = false;
				posX += dirX;
				posY += dirY;
				moveCount = 0;
				GetLand();
			}

		}
		else
		{
			break;
		}

		if (isVisiting)
		{
			if (prevX == posX && prevY == posY)
				MoveFail();
		}
	}
}

void SuperEnemy::MoveFail()
{
	posX = visitingX;
	posY = visitingY;
	isVisiting = false;
	moveCount = 0;

	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_ENEMY_VISITING)
		{
			map[i] = MAP_EMPTY;
		}
	}
}

void SuperEnemy::MoveFllowKey()
{
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = { -1, 0 };
		dirX = dir.x;
		dirY = dir.y;
		Move();
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = { 1, 0 };
		dirX = dir.x;
		dirY = dir.y;
		Move();
	}
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = { 0, -1 };
		dirX = dir.x;
		dirY = dir.y;
		Move();
	}
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	{
		D3DXVECTOR2 dir = { 0, 1 };
		dirX = dir.x;
		dirY = dir.y;
		Move();
	}
}

void SuperEnemy::Update()
{
	if (!isDead)
	{
		calcDir();
		//MoveFllowKey();
		GetPersent();
	}
}

void SuperEnemy::Render()
{
	if (!isDead) {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 cen;


		spr->Begin(D3DXSPRITE_ALPHABLEND);

		pos = { (float)GAME_X + posX - (size / 2), (float)GAME_Y + posY - (size / 2), 0 };
		spr->Draw(*enemyTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		spr->End();
	}
	
}
