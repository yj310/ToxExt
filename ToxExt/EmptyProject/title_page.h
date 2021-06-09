#pragma once
#include "page.h"

class TitlePage : public Page
{
public:

	TitlePage();
	virtual ~TitlePage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* startButtonTex1;
	LPDIRECT3DTEXTURE9* startButtonTex2;
	LPDIRECT3DTEXTURE9* introButtonTex1;
	LPDIRECT3DTEXTURE9* introButtonTex2;
	LPDIRECT3DTEXTURE9* manualButtonTex1;
	LPDIRECT3DTEXTURE9* manualButtonTex2;
	LPDIRECT3DTEXTURE9* rankingButtonTex1;
	LPDIRECT3DTEXTURE9* rankingButtonTex2;
	LPDIRECT3DTEXTURE9* exitButtonTex1;
	LPDIRECT3DTEXTURE9* exitButtonTex2;
	LPD3DXSPRITE spr;
	ID3DXFont* titleFont;
	ID3DXFont* menuFont; 
	ID3DXFont* menuBoldFont;

	int startButtonState;
	int introButtonState;
	int manualButtonState;
	int rankingButtonState;
	int exitButtonState;
	

	void Update() override;
	void Render() override;

};