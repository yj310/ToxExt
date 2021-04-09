#include "DXUT.h"
#include "input_page.h"
#include "global.h"
#include <atlconv.h>

InputPage::InputPage()
{

	inputCount = 0;
	nameCount = 0;
	returnCount = 50;
	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/inputBackground.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

	D3DXCreateFont(DXUTGetD3D9Device(), 60, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"³ª´®¹Ù¸¥°íµñ", &font);

}

InputPage::~InputPage()
{
	(*backgroundTex)->Release();
	spr->Release();
	font->Release();
}

void InputPage::Update()
{

	if (inputCount > 0)
		inputCount--;
	returnCount--;
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if ((GetAsyncKeyState(i) & 0x8000) != 0 && inputCount == 0 && nameCount < 5)
		{
			name.push_back(i);
			inputCount = 10;
			nameCount++;
		}
	}
	if ((GetAsyncKeyState(VK_BACK) & 0x8000) != 0 && inputCount == 0)
	{
		if (name.size() > 0)
		{
			name.pop_back();
			inputCount = 20;
			if (nameCount > 0)
				nameCount--;
		}
	}
	if (((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0) && returnCount <= 0)
	{
		string strName(name.begin(), name.end());
		strcpy_s(cname, strName.c_str());
		fileManager.Load();
		fileManager.Save(cname);
		pageManager.CreateRankingPage();
	}
}

void InputPage::Render()
{

	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;


	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	spr->End();



	USES_CONVERSION;
	int ivalue; int ivalue2;
	float fvalue;
	char cvalue[256];
	WCHAR* wvalue;
	RECT rc;


	
	sprintf_s(cvalue, "%d", score);
	wvalue = A2W(cvalue);
	rc = { 300, 280, WINDOW_WIDTH, WINDOW_HEIGHT };
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	string strName(name.begin(), name.end());
	strcpy_s(cname, strName.c_str());
	wvalue = A2W(cname);
	rc = { 300, 500, WINDOW_WIDTH, WINDOW_HEIGHT };
	font->DrawText(NULL, wvalue, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


}
