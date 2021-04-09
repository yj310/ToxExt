#pragma once
#include "page.h"

class IntroPage : public Page
{
public:

	IntroPage();
	virtual ~IntroPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* backButtonTex1;
	LPDIRECT3DTEXTURE9* backButtonTex2;
	LPD3DXSPRITE spr;
	ID3DXFont* font;

	int backButtonState;

	char fullText[1000];
	char text[1000];
	int count;

	void Update() override;
	void Render() override;

};
