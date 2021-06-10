#pragma once
#include "page.h"

class RankingPage : public Page
{
public:

	RankingPage();
	virtual ~RankingPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* lineTex;
	LPD3DXSPRITE spr;
	ID3DXFont* titleFont;
	ID3DXFont* textFont;
	ID3DXFont* textLineFont;
	ID3DXFont* menuFont; 
	ID3DXFont* menuBoldFont;


	int backButtonState;

	void Update() override;
	void Render() override;

};
