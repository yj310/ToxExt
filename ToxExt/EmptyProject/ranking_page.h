#pragma once
#include "page.h"

class RankingPage : public Page
{
public:

	RankingPage();
	virtual ~RankingPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* backButtonTex1;
	LPDIRECT3DTEXTURE9* backButtonTex2;
	LPD3DXSPRITE spr;
	ID3DXFont* font;


	int backButtonState;

	void Update() override;
	void Render() override;

};
