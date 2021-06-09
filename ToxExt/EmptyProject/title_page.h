#pragma once
#include "page.h"

class TitlePage : public Page
{
public:

	TitlePage();
	virtual ~TitlePage();

	LPDIRECT3DTEXTURE9* backgroundTex;
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