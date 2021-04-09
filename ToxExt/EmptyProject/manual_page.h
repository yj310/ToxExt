#pragma once
#include "page.h"

class ManualPage : public Page
{
public:

	ManualPage();
	virtual ~ManualPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* backButtonTex1;
	LPDIRECT3DTEXTURE9* backButtonTex2;
	LPD3DXSPRITE spr;

	int backButtonState;

	void Update() override;
	void Render() override;

};
