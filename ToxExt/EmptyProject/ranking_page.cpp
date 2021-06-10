
#include "DXUT.h"
#include "ranking_page.h"
#include "global.h"
#include <atlconv.h>

RankingPage::RankingPage()
{
	backButtonState = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	lineTex = new LPDIRECT3DTEXTURE9();
	mCreateTexture("resource/image/basicBackground.png", backgroundTex);
	mCreateTexture("resource/image/line.png", lineTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr); 


	mCreateFont(&titleFont, 60, FW_LIGHT);
	mCreateFont(&textFont, 30, FW_LIGHT);
	mCreateFont(&textLineFont, 30, FW_LIGHT);
	mCreateFont(&menuFont, 35, FW_LIGHT);
	mCreateFont(&menuBoldFont, 35, FW_BOLD);


	fileManager.Load();




}

RankingPage::~RankingPage()
{
	(*backgroundTex)->Release();
	(*lineTex)->Release();
	spr->Release();

	titleFont->Release();
	textFont->Release();
	textLineFont->Release();
	menuFont->Release();
	menuBoldFont->Release();
}

void RankingPage::Update()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	if (pt.x > BACK_BUTTON_X
		&& pt.x < BACK_BUTTON_X + BUTTON_WIDTH)
	{
		if (pt.y > BACK_BUTTON_Y - BUTTON_PADDING
			&& pt.y < BACK_BUTTON_Y + BUTTON_HEIGHT - BUTTON_PADDING)
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

#define LINE_HEIGHT 60

void RankingPage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	USES_CONVERSION;
	int ivalue; int ivalue2;
	float fvalue;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc;

	// background
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();

	// title
	sprintf_s(cvalue, "Ranking");
	wvalue = A2W(cvalue);
	rc = { 50, 40, WINDOW_WIDTH, WINDOW_HEIGHT };
	titleFont->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// line
	rc = { 0, 0, WINDOW_WIDTH - 60, 1 };
	pos = { 30, 105, 0 };
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*lineTex, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();

	// backbutton
	rc = { BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_X + BUTTON_WIDTH, BACK_BUTTON_Y + BUTTON_HEIGHT };
	sprintf_s(cvalue, "메인메뉴");
	wvalue = A2W(cvalue);
	if (backButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



	// text
	rc = { 300, 150, WINDOW_WIDTH, 150 + 100 };


	rc.left = 300;
	rc.right = rc.left + 100;
	sprintf_s(cvalue, "순위");
	wvalue = A2W(cvalue);
	textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.left = 470;
	rc.right = WINDOW_WIDTH - rc.left;
	sprintf_s(cvalue, "score");
	wvalue = A2W(cvalue);
	textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.right = WINDOW_WIDTH - 300;
	rc.left = rc.right - 100;
	sprintf_s(cvalue, "name");
	wvalue = A2W(cvalue);
	textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	for (int i = 0; i < 5; i++)
	{
		rc = { 300
			, 250 + (LINE_HEIGHT * i)
			, 300 + 100
			, 250 + (LINE_HEIGHT * i) + 100
		};
		sprintf_s(cvalue, "%d", i+1);
		wvalue = A2W(cvalue);
		textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


		rc = { 470
			, 250 + (LINE_HEIGHT * i)
			, WINDOW_WIDTH - 470
			, 250 + (LINE_HEIGHT * i) + 100
		};
		sprintf_s(cvalue, "%010d", playerInfo[i].score);
		wvalue = A2W(cvalue);
		textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



		rc = { WINDOW_WIDTH - 300 - 100
			, 250 + (LINE_HEIGHT * i)
			, WINDOW_WIDTH - 300
			, 250 + (LINE_HEIGHT * i) + 100
		};
		wvalue = A2W(playerInfo[i].name);
		textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	
}

