#include "stdafx.h"
#include "Render.hpp"
#include "Vector.hpp"
#include <d3dtypes.h>

Render::Render() : pDevice(nullptr), pLine(nullptr), pFontSmall(nullptr), pFontBig(nullptr),
	m_status(S_OK), m_initDrawing(false), m_cleanedUp(false)
{
	
}

Render::~Render()
{
}

struct textured_vertex {
	float x, y, z, rhw;  // The transformed(screen space) position for the vertex.

	float tu, tv;         // Texture coordinates

};

const DWORD tri_fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;

void Render::Init(IDirect3DDevice9Ex* _pDevice)
{
	if (m_initDrawing == true)
		return;

	pDevice = _pDevice;
	if (pDevice == nullptr)
	{
		return;
	}

	m_status = D3DXCreateFont(pDevice, 25, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &pFontSmall);
	if (m_status != S_OK)
	{
		pDevice = nullptr;
		return;
	}

	m_status = D3DXCreateFont(pDevice, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &pFontBig);
	if (m_status != S_OK)
	{
		pDevice = nullptr;
		pFontSmall->Release();
		return;
	}

	m_status = D3DXCreateLine(pDevice, &pLine);
	if (m_status != S_OK)
	{
		pDevice = nullptr;
		pFontSmall->Release();
		pFontBig->Release();
		return;
	}

	pLine->SetWidth(1.0f);
	pLine->SetPattern(0xFFFFFFFF);
	pLine->SetAntialias(false);

	m_initDrawing = true;
}

void Render::CleanUp()
{
	if (m_initDrawing == false)
		return;

	if (m_cleanedUp == true)
		return;

	if (pLine)
		pLine->Release();

	if (pFontSmall)
		pFontSmall->Release();

	if (pFontBig)
		pFontBig->Release();

	pLine		= nullptr;
	pFontSmall	= nullptr;
	pFontBig	= nullptr;
	pDevice		= nullptr;
	m_cleanedUp = true;
}

void Render::String(int x, int y, Color color, bool bigFont, const char* fmt, ...)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	char Buffer[4048];
	va_list vaList;
	va_start(vaList, fmt);
	vsprintf_s(Buffer, fmt, vaList);
	RECT rect_pos = { x, y, x + 500, y + 100 };
	ID3DXFont* pFont = bigFont ? pFontBig : pFontSmall;
	pFont->DrawTextA(NULL, (LPCSTR)Buffer, -1, &rect_pos, DT_TOP, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()));
	va_end(vaList);
}
void Render::StringOutlined(int x, int y, Color color, bool bigFont, const char* fmt, ...)
{
	char Buffer[4048];
	va_list vaList;
	va_start(vaList, fmt);
	vsprintf_s(Buffer, fmt, vaList);
	this->String(x - 1, y, Color(0, 0, 0), bigFont, Buffer);
	this->String(x, y - 1, Color(0, 0, 0), bigFont, Buffer);
	this->String(x + 1, y, Color(0, 0, 0), bigFont, Buffer);
	this->String(x, y + 1, Color(0, 0, 0), bigFont, Buffer);
	this->String(x, y, color, bigFont, Buffer);
	va_end(vaList);
}

void Render::Rect(int x, int y, int w, int h, Color color)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()), 0, 0);
}

void Render::BorderBox(int x, int y, int w, int h, int thickness, Color color)
{
	this->Rect(x, y                , w, thickness, color); // UP
	this->Rect(x, y + h - thickness, w, thickness, color); // DOWN
	this->Rect(x, y                , thickness, h, color); // LEFT
	this->Rect(x + w - thickness, y, thickness, h, color); // RIGHT

}

void Render::BorderBoxOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined)
{
	this->BorderBox(x, y, w, h, thickness, color); // Background
	this->BorderBox(x, y, w, h, 2, outlined); // OUT
	this->BorderBox(x + thickness, y + thickness, w - 2* thickness, h - 2 * thickness, 2, outlined); // IN
}

void Render::RectOutlined(int x, int y, int w, int h, Color rectcolor, Color outlinedcolor, int thickness)
{
	Rect(x, y, w, h, rectcolor);
	BorderBox(x, y, w, h, thickness, outlinedcolor);
}

void Render::Line(int x, int y, int x2, int y2, Color color, float thickness)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	pLine->SetWidth(thickness);
	D3DXVECTOR2 points[2];
	points[0].x = x;
	points[1].x = x2;
	points[0].y = y;
	points[1].y = y2;
	pLine->Draw(points, 2, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()));
}

void Render::Cross(int x, int y, int w, int h, Color color, float thickness)
{
	this->Line(x, y, x + w, y + h, color, thickness);
	this->Line(x, y + h, x + w, y, color, thickness);
}

void Render::Crosshair(int x, int y, int w, Color color, float thickness)
{
	this->Rect(x - w, y - thickness, w * 2, thickness * 2, color);
	this->Rect(x - thickness, y - w, thickness * 2, w * 2, color);
}

void Render::Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE Sprite)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	Sprite->Draw(dTexture, NULL, NULL, &D3DXVECTOR3((float)x, (float)y, 0.0f), 0xFFFFFFFF);
}

void Render::GardientRect(int x, int y, int w, int h, int thickness, bool outlined, Color from, Color to, Color Outlined)
{
	float a = ((float)to.a() - (float)from.a()) / h;
	float r = ((float)to.r() - (float)from.r()) / h;
	float g = ((float)to.g() - (float)from.g()) / h;
	float b = ((float)to.b() - (float)from.b()) / h;

	for (int i = 0; i < h; i++)
	{
		int A = from.a() + a * i;
		int R = from.r() + r * i;
		int G = from.g() + g * i;
		int B = from.b() + b * i;
		this->Rect(x, y + i, w, 1, Color(A, R, G, B));
	}
	if (outlined)
	{
		this->BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, Outlined);
	}
}


static const int CIRCLE_RESOLUTION = 64;
struct VERTEX_2D_DIF { // transformed colorized
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};


void Render::DrawCircleFilled(float x, float y, float r, Color color)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	VERTEX_2D_DIF verts[CIRCLE_RESOLUTION + 1];

	for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++)
	{
		verts[i].x = x + r * cos(D3DX_PI * (i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].y = y + r * sin(D3DX_PI * (i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].z = 0;
		verts[i].rhw = 1;
		verts[i].color = D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b());
	}

	pDevice->SetFVF(VERTEX_2D_DIF::FVF);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION - 1, &verts, sizeof(VERTEX_2D_DIF));
}

int Render::getWidth()
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return 0;

	IDirect3DSurface9* pSurface;
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	D3DSURFACE_DESC SurfaceDesc;
	pSurface->GetDesc(&SurfaceDesc);
	UINT Width = SurfaceDesc.Width;
	UINT Height = SurfaceDesc.Height;
	pSurface->Release();

	return Width;
}

int Render::getHeight()
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return 0;

	IDirect3DSurface9* pSurface;
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	D3DSURFACE_DESC SurfaceDesc;
	pSurface->GetDesc(&SurfaceDesc);
	UINT Width = SurfaceDesc.Width;
	UINT Height = SurfaceDesc.Height;
	pSurface->Release();

	return Height;
}

D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v =
	{
		X,
		Y,
		Z,
		RHW,
		color,
		U,
		V
	};
	return v;
}

void Render::DrawCircle(float x, float y, float r, bool center, Color color)
{
	if ((m_initDrawing == false) || (m_cleanedUp == true)) return;

	const int NUMPOINTS = 34;
	const float PI = 3.14f;
	if (!center)
	{
		x -= r;
		y -= r;
	}

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;
	WedgeAngle = (float)((2 * PI) / NUMPOINTS);
	for (i = 0; i <= NUMPOINTS; i++)
	{
		Theta = i * WedgeAngle;
		X = (float)(x + r * cos(Theta));
		Y = (float)(y - r * sin(Theta));
		Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()), 0.0f, 0.0f);
	}
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
}

std::unique_ptr<Render> gRender = std::make_unique < Render>();
