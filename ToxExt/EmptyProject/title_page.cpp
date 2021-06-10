#include "DXUT.h"
#include "title_page.h"
#include "global.h"
#include <atlconv.h>

#define MENUY 400

TitlePage::TitlePage()
{
	startButtonState = 0;
	introButtonState = 0;
	manualButtonState = 0;
	rankingButtonState = 0;
	exitButtonState = 0;
	score = 0;



	backgroundTex = new LPDIRECT3DTEXTURE9();
	mCreateTexture("resource/image/basicBackground.png", backgroundTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


	mCreateFont(&titleFont, 80, FW_LIGHT);
	mCreateFont(&menuFont, 35, FW_LIGHT);
	mCreateFont(&menuBoldFont, 35, FW_BOLD);


}

TitlePage::~TitlePage()
{
	(*backgroundTex)->Release();
	spr->Release();

	titleFont->Release();
	menuFont->Release();
	menuBoldFont->Release();
}

void TitlePage::Update()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	if (pt.x > (WINDOW_WIDTH - BUTTON_WIDTH) / 2
		&& pt.x < (WINDOW_WIDTH + BUTTON_WIDTH) / 2)
	{
		// GameStart button
		if (pt.y > MENUY + BUTTON_HEIGHT * 0 - BUTTON_PADDING
			&& pt.y < MENUY + BUTTON_HEIGHT * 1 - BUTTON_PADDING)
		{
			startButtonState = 1;
		}
		else
		{
			startButtonState = 0;
		}

		// GameIntro button
		if (pt.y > MENUY + BUTTON_HEIGHT * 1 - BUTTON_PADDING
			&& pt.y < MENUY + BUTTON_HEIGHT * 2 - BUTTON_PADDING)
		{
			introButtonState = 1;
		}
		else
		{
			introButtonState = 0;
		}

		// GameManual button
		if (pt.y > MENUY + BUTTON_HEIGHT * 2 - BUTTON_PADDING
			&& pt.y < MENUY + BUTTON_HEIGHT * 3 - BUTTON_PADDING)
		{
			manualButtonState = 1;
		}
		else
		{
			manualButtonState = 0;
		}

		// Ranking button
		if (pt.y > MENUY + BUTTON_HEIGHT * 3 - BUTTON_PADDING
			&& pt.y < MENUY + BUTTON_HEIGHT * 4 - BUTTON_PADDING)
		{
			rankingButtonState = 1;
		}
		else
		{
			rankingButtonState = 0;
		}

		// Exit button
		if (pt.y > MENUY + BUTTON_HEIGHT * 4 - BUTTON_PADDING
			&& pt.y < MENUY + BUTTON_HEIGHT * 5 - BUTTON_PADDING)
		{
			exitButtonState = 1;
		}
		else
		{
			exitButtonState = 0;
		}
	}
	else
	{
		startButtonState = 0;
		introButtonState = 0;
		manualButtonState = 0;
		rankingButtonState = 0;
		exitButtonState = 0;
	}


	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		if (startButtonState == 1)
		{
			//pageManager.CreateSecondGamePage();
			pageManager.CreateFirstGamePage();
		}
		else if (introButtonState == 1)
		{
			pageManager.CreateIntroPage();
		}
		else if (manualButtonState == 1)
		{
			pageManager.CreateManualPage();
		}
		else if (rankingButtonState == 1)
		{
			pageManager.CreateRankingPage();
		}
		else if (exitButtonState == 1)
		{
			// Exit
			PostQuitMessage(0);
		}
	}

}

void TitlePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	USES_CONVERSION;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };



	// background
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();



	// title
	rc.top = 120;
	sprintf_s(cvalue, "ToxExt");
	wvalue = A2W(cvalue);
	titleFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	// menu
	rc.top = MENUY + BUTTON_HEIGHT * 0;
	sprintf_s(cvalue, "게임시작");
	wvalue = A2W(cvalue);
	if (startButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.top = MENUY + BUTTON_HEIGHT * 1;
	sprintf_s(cvalue, "게임설명");
	wvalue = A2W(cvalue);
	if (introButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.top = MENUY + BUTTON_HEIGHT * 2;
	sprintf_s(cvalue, "게임방법");
	wvalue = A2W(cvalue);
	if (manualButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.top = MENUY + BUTTON_HEIGHT * 3;
	sprintf_s(cvalue, "랭킹");
	wvalue = A2W(cvalue);
	if (rankingButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	rc.top = MENUY + BUTTON_HEIGHT * 4;
	sprintf_s(cvalue, "종료");
	wvalue = A2W(cvalue);
	if (exitButtonState == 0)
		menuFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	else
		menuBoldFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));




}

