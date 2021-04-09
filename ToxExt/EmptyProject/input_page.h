#pragma once
#include "page.h"
#include <vector>

using namespace std;

class InputPage : public Page
{
public:

	InputPage();
	virtual ~InputPage();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE spr;
	ID3DXFont* font;

	char cname[128];
	vector<char> name;

	int key[27];
	int prevKey[27];

	int inputCount;
	int returnCount;
	int nameCount;


	int backButtonState;

	void Update() override;
	void Render() override;

};
