#pragma once
#include "page.h"

class IntroPage : public Page
{
public:

	IntroPage();
	virtual ~IntroPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* lineTex;
	LPD3DXSPRITE spr;
	ID3DXFont* titleFont; 
	ID3DXFont* textFont;
	ID3DXFont* menuFont;
	ID3DXFont* menuBoldFont;

	int backButtonState;

	char fullText[1000];
	char text[1000];
	int count;

	void Update() override;
	void Render() override;

};
