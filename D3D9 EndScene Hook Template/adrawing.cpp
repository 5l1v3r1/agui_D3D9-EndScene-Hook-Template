#include "stdafx.h"
#include "adrawing.hpp"

namespace adrawing
{
	MY_D3DCOLOR BrightBlack(MY_D3DCOLOR_ARGB(255, 26, 26, 26));
	MY_D3DCOLOR DarkGrey(MY_D3DCOLOR_ARGB(255, 33, 33, 33));
	MY_D3DCOLOR BrightGrey(MY_D3DCOLOR_ARGB(255, 50, 50, 50));
	MY_D3DCOLOR White(MY_D3DCOLOR_ARGB(255, 241, 241, 241));

	std::unique_ptr<draw>gDraw = std::make_unique<draw>();
	
	draw::draw() : device(nullptr), smallFont(nullptr), middleFont(nullptr),
		m_initDrawing(false), m_cleanedUp(false)
	{

	}

	draw::~draw()
	{

	}

	void draw::initDrawing(IDirect3DDevice9Ex* pDevice)
	{
		if (m_initDrawing == true)
			return;

		device = pDevice;
		if (device == nullptr)
			return;

		D3DXCreateFont(device, 13, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &smallFont);
		if (smallFont == nullptr)
			return;

		D3DXCreateFont(device, 22, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &middleFont);
		if (middleFont == nullptr)
		{
			smallFont->Release();
			return;
		}

		m_initDrawing = true;
	}

	void draw::cleanUp()
	{
		if (m_initDrawing == false)
			return;

		if (m_cleanedUp == true)
			return;

		if (smallFont)
			smallFont->Release();

		if (middleFont)
			middleFont->Release();

		smallFont  = nullptr;
		middleFont = nullptr;
		device     = nullptr;
		m_cleanedUp = true;
	}

	void draw::DrawStringCenter(char* str, _D3DRECT rect, D3DCOLOR color, bool bigFont)
	{
		if (m_initDrawing == false)
			return;

		if (m_cleanedUp == true)
			return;

		RECT pos = { rect.x1, rect.y1, rect.x2, rect.y2 };

		if (bigFont)
			gDraw->middleFont->DrawText(0, str, strlen(str), &pos, DT_NOCLIP | DT_CENTER | DT_VCENTER, color);
		else
			gDraw->smallFont->DrawText(0, str, strlen(str), &pos, DT_NOCLIP | DT_CENTER | DT_VCENTER, color);
	}

	void draw::DrawStringLeft(char* str, _D3DRECT rect, D3DCOLOR color, bool bigFont) 
	{
		if (m_initDrawing == false)
			return;

		if (m_cleanedUp == true)
			return;

		RECT pos = { rect.x1, rect.y1, rect.x2, rect.y2 };

		if(bigFont)
			gDraw->middleFont->DrawText(0, str, strlen(str), &pos, DT_NOCLIP | DT_VCENTER, color);
		else
			gDraw->smallFont->DrawText(0, str, strlen(str), &pos, DT_NOCLIP | DT_VCENTER, color);
	}

	void draw::DrawFilledRectangle(_D3DRECT rect, D3DCOLOR color)
	{
		if (m_initDrawing == false)
			return;

		if (m_cleanedUp == true)
			return;

		D3DRECT drawRect = rect;
		gDraw->device->Clear(1, &drawRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
	}
}