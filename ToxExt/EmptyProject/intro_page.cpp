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

	D3DXCreateFont(DXUTGetD3D9Device(), 40, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"나눔바른고딕", &font);

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/introBackground.png"
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
}

IntroPage::~IntroPage()
{
	(*backgroundTex)->Release();
	(*backButtonTex1)->Release();
	(*backButtonTex2)->Release();
	spr->Release();
	font->Release();

}

void IntroPage::Update()
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


	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	pos = { BACK_BUTTON_X, BACK_BUTTON_Y, 0 };
	if (backButtonState == 0)
		spr->Draw(*backButtonTex1, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
		spr->Draw(*backButtonTex2, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();



	WCHAR* wvalue;
	RECT rc;


	USES_CONVERSION;
	wvalue = A2W(text);
	rc = { 50, 150, WINDOW_WIDTH - 50, WINDOW_HEIGHT };
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	

}

