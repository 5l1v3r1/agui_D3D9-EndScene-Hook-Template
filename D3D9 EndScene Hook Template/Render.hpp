#pragma once
#include <memory>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#include "Color.hpp"


class Render
{
	IDirect3DDevice9Ex* pDevice;
	ID3DXLine*			pLine;
	ID3DXFont*			pFontSmall;
	ID3DXFont*			pFontBig;

	HRESULT		m_status;
	bool		m_initDrawing;
	bool		m_cleanedUp;

public:
	Render();
	~Render();

	void	Init(IDirect3DDevice9Ex* _pDevice);
	void    CleanUp();

	void	String(int x, int y, Color color, bool bigFont, const char* fmt, ...);
	void	StringOutlined(int x, int y, Color color, bool bigFont, const char* fmt, ...);

	void	Rect(int x, int y, int w, int h, Color color);
	void	BorderBox(int x, int y, int w, int h, int thickness, Color color);
	void	BorderBoxOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
	void	RectOutlined(int x, int y, int w, int h, Color rectcolor, Color outlinedcolor, int thickness);
	
	void	Line(int x, int y, int x2, int y2, Color color, float thickness = 1);
	void    Cross(int x, int y, int w, int h, Color color, float thickness = 1);
	void    Crosshair(int x, int y, int w, Color color, float thickness = 1);

	void	Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE Sprite);
	void	GardientRect(int x, int y, int w, int h, int thickness, bool outlined, Color from, Color to, Color Outlined);

	void	DrawCircle(float x, float y, float rad, bool center, Color color);
	void	DrawCircleFilled(float x, float y, float r, Color color);

	int     getWidth();
	int		getHeight();
};

extern std::unique_ptr<Render> gRender;