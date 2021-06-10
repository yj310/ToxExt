#include "DXUT.h"
#include "intro_page.h"
#include "global.h"
#include <atlconv.h>

IntroPage::IntroPage()
{
	
	strcpy_s<1000>(text, "                                ");
	strcpy_s<1000>(fullText, "멀지 않은 미래, 인간에게 치명적인 '슈퍼 바이러스'가 전 세계적으로 유행하게 된다. \n높은 치사량으로 많은 사람들이 사망하였고, 감염경로가 밝혀지지 않아 순식간에 인구의 \n절반 이상이 감염되었다. 하지만 최근, 기적적으로 '슈퍼 바이러스'를 치료할 수 있는 백신이 \n개발되었다. 나노머신을 조종하여 슈퍼 바이러스를 박멸시키고 평화로웠던 지구를 되찾자!");
	count = 0;

	backButtonState = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	lineTex = new LPDIRECT3DTEXTURE9();
	mCreateTexture("resource/image/basicBackground.png", backgroundTex);
	mCreateTexture("resource/image/line.png", lineTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


	mCreateFont(&titleFont, 60, FW_LIGHT);
	mCreateFont(&textFont, 30, FW_LIGHT);
	mCreateFont(&menuFont, 35, FW_LIGHT);
	mCreateFont(&menuBoldFont, 35, FW_BOLD);
}

IntroPage::~IntroPage()
{
	(*backgroundTex)->Release();
	(*lineTex)->Release();
	spr->Release();

	titleFont->Release();
	textFont->Release();
	menuFont->Release();
	menuBoldFont->Release();

}

void IntroPage::Update()
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

	if (count < 500)
	{
		text[count] = fullText[count];
		count++;
	}

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		if (backButtonState == 1)
		{
			pageManager.CreateTitlePage();
		}

	}

	
}

void IntroPage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	USES_CONVERSION;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc;



	// background
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();
	

	// title
	sprintf_s(cvalue, "Intro");
	wvalue = A2W(cvalue);
	rc = { 50, 40, WINDOW_WIDTH, WINDOW_HEIGHT };
	titleFont->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// line
	rc = { 0, 0, WINDOW_WIDTH - 60, 1 };
	pos = { 30, 100, 0 };
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
	wvalue = A2W(text);
	rc = { 50, 200, WINDOW_WIDTH - 50, WINDOW_HEIGHT };
	textFont->DrawText(NULL, wvalue, -1, &rc, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));




	

}

