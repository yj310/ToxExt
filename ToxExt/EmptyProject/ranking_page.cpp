
#include "DXUT.h"
#include "ranking_page.h"
#include "global.h"
#include <atlconv.h>

RankingPage::RankingPage()
{
	backButtonState = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/rankingBackground.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);

	backButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/backButtonTex1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backButtonTex1);

	backButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/backButtonTex2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backButtonTex2);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr); 
	
	D3DXCreateFont(DXUTGetD3D9Device(), 60, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"³ª´®¹Ù¸¥°íµñ", &font);


	fileManager.Load();




}

RankingPage::~RankingPage()
{
	(*backgroundTex)->Release();
	(*backButtonTex1)->Release();
	(*backButtonTex2)->Release();
	spr->Release();
	font->Release();
}

void RankingPage::Update()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	if (pt.x > BACK_BUTTON_X
		&& pt.x < BACK_BUTTON_X + BUTTON_WIDTH)
	{
		if (pt.y > BACK_BUTTON_Y
			&& pt.y < BACK_BUTTON_Y + BUTTON_HEIGHT)
		{
			backButtonState = 1;
		}
		else
		{
			backButtonState = 0;
		}

	}
	else
	{
		backButtonState = 0;
	}

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		if (backButtonState == 1)
		{
			pageManager.CreateTitlePage();
		}

	}
}

void RankingPage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;


	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pos = { BACK_BUTTON_X, BACK_BUTTON_Y, 0 };
	if (backButtonState == 0)
		spr->Draw(*backButtonTex1, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
		spr->Draw(*backButtonTex2, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();


	USES_CONVERSION;
	int ivalue; int ivalue2;
	float fvalue;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc;


	rc = { 300, 280, WINDOW_WIDTH, WINDOW_HEIGHT };


	rc.top = 150;
	rc.left = 200;
	sprintf_s(cvalue, "¼øÀ§");
	wvalue = A2W(cvalue);
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.left = 470;
	sprintf_s(cvalue, "score");
	wvalue = A2W(cvalue);
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



	rc.left = 920;
	sprintf_s(cvalue, "name");
	wvalue = A2W(cvalue);
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	for (int i = 0; i < 5; i++)
	{
		rc.top = 250 + (70 * i);
		rc.left = 220;
		sprintf_s(cvalue, "%d", i+1);
		wvalue = A2W(cvalue);
		font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


		rc.left = 410;
		sprintf_s(cvalue, "%010d", playerInfo[i].score);
		wvalue = A2W(cvalue);
		font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



		rc.left = 900;
		wvalue = A2W(playerInfo[i].name);
		font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	
}

