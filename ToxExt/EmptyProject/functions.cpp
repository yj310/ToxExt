#include "DXUT.h"
#include "functions.h"

void mCreateFont(ID3DXFont** font, int fontSize, int style)
{
	D3DXCreateFont(DXUTGetD3D9Device(), fontSize, 0, style, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Cafe24 Oneprettynight", font);
}

void mCreateTexture(char* imageSrc,	LPDIRECT3DTEXTURE9* texture)
{
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, imageSrc
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, texture);
}