#include "stdafx.h"
#include "D3DImage.h"

D3DImage::D3DImage()
{
	m_Imagetexture = NULL;
	m_Imagesprite = NULL;

	sz_image_h = sz_image_w = 0;

	sz_AnimationIndex = 0;
	sz_Ammount = 0;
	sz_once = false;
}


D3DImage::~D3DImage()
{
}

void D3DImage::InitImage(LPDIRECT3DDEVICE9 pDevice, BYTE* image, int size)
{
	if (m_Imagetexture == NULL)
		D3DXCreateTextureFromFileInMemory(pDevice, image, size, &m_Imagetexture);

	if (m_Imagesprite == NULL)
		D3DXCreateSprite(pDevice, &m_Imagesprite);
}

void D3DImage::InitImageS(LPDIRECT3DDEVICE9 pDevice, BYTE* image, int size, int w, int h)
{
	if (m_Imagetexture == NULL)
		D3DXCreateTextureFromFileInMemoryEx(pDevice, image, size, w, h, D3DX_DEFAULT, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &m_Imagetexture);

	if (m_Imagesprite == NULL)
		D3DXCreateSprite(pDevice, &m_Imagesprite);

	sz_image_w = w;
	sz_image_h = h;
}

void D3DImage::InitImageFromFile(LPDIRECT3DDEVICE9 pDevice, LPSTR filename)
{
	if (m_Imagetexture == NULL)
		D3DXCreateTextureFromFile(pDevice, filename, &m_Imagetexture);

	if (m_Imagesprite == NULL)
		D3DXCreateSprite(pDevice, &m_Imagesprite);
}

void D3DImage::InitImageFromFileS(LPDIRECT3DDEVICE9 pDevice, LPSTR filename, int w, int h)
{
	if (m_Imagetexture == NULL)
		D3DXCreateTextureFromFileEx(pDevice, filename, w, h, D3DX_DEFAULT, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &m_Imagetexture);

	if (m_Imagesprite == NULL)
		D3DXCreateSprite(pDevice, &m_Imagesprite);

	sz_image_w = w;
	sz_image_h = h;
}

void D3DImage::DrawImage(int x, int y)
{
	m_Imagepos.x = x;
	m_Imagepos.y = y;


	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, NULL, NULL, &m_Imagepos, 0xFFFFFFFF);
	m_Imagesprite->End();
}

void D3DImage::DrawImageA(int x, int y, int alpha)
{
	m_Imagepos.x = x;
	m_Imagepos.y = y;


	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, NULL, NULL, &m_Imagepos, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	m_Imagesprite->End();
}

void D3DImage::DrawImageAsCrosshair(D3DVIEWPORT9 port)
{
	int		sz_w = sz_image_w / 2;
	int		sz_h = sz_image_h / 2;

	DrawImage(port.Width / 2 - sz_w, port.Height / 2 - sz_h);
}

void D3DImage::DrawImageAsCrosshairA(int alpha, D3DVIEWPORT9 port)
{
	int		sz_w = sz_image_w / 2;
	int		sz_h = sz_image_h / 2;

	DrawImageA(port.Width / 2 - sz_w, port.Height / 2 - sz_h, alpha);
}

void D3DImage::DrawImageR(int x, int y, int angle)
{
	if (sz_image_h == 0 || sz_image_w == 0)
		return;


	m_Imagecenter.x = sz_image_w / 2;
	m_Imagecenter.y = sz_image_h / 2;

	D3DXVECTOR2 temp_Image2DPos(x, y);

	D3DXMatrixTransformation2D(&m_Imagerotation, NULL, NULL, NULL, &m_Imagecenter, angle * D3DX_PI / 180, &temp_Image2DPos);
	m_Imagesprite->SetTransform(&m_Imagerotation);

	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, NULL, NULL, &m_Imagepos, 0xFFFFFFFF);
	m_Imagesprite->End();
}

void D3DImage::DrawImageAR(int x, int y, int angle, int alpha)
{
	if (sz_image_h == 0 || sz_image_w == 0)
		return;


	m_Imagecenter.x = sz_image_w / 2;
	m_Imagecenter.y = sz_image_h / 2;

	D3DXVECTOR2 temp_Image2DPos(x, y);

	D3DXMatrixTransformation2D(&m_Imagerotation, NULL, NULL, NULL, &m_Imagecenter, angle * D3DX_PI / 180, &temp_Image2DPos);
	m_Imagesprite->SetTransform(&m_Imagerotation);

	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, NULL, NULL, &m_Imagepos, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	m_Imagesprite->End();
}

void D3DImage::AnimateImage(int x, int y, int original_w, int original_h, int idle)
{

	if (!sz_once)
	{
		sz_Ammount = sz_image_h / original_h;
		dTimer = new TimeManager(idle);

		for (int i = 0; i < sz_Ammount; i++)
		{
			RECT temp;
			temp.left = 0;					//x top left corner
			temp.top = i * original_h;			//y top left corner
			temp.right = temp.left + original_w;	//x bottom right corner
			temp.bottom = temp.top + original_h;	//y bottom right corner


			sz_AnimationRegions.push_back(temp);
		}
		sz_once = true;
	}

	m_Imagepos.x = x;
	m_Imagepos.y = y;

	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, &sz_AnimationRegions.at(sz_AnimationIndex), NULL, &m_Imagepos, 0xFFFFFFFF);
	m_Imagesprite->End();

	if (dTimer->IsIdleOver())
	{
		sz_AnimationIndex++;

		if (sz_AnimationIndex > sz_Ammount - 1)
			sz_AnimationIndex = 0;

		dTimer->SetIdleHere();
	}
}

void D3DImage::AnimateImageA(int x, int y, int original_w, int original_h, int idle, int alpha)
{

	if (!sz_once)
	{
		sz_Ammount = sz_image_h / original_h;
		dTimer = new TimeManager(idle);

		for (int i = 0; i < sz_Ammount; i++)
		{
			RECT temp;
			temp.left = 0;					//x top left corner
			temp.top = i * original_h;			//y top left corner
			temp.right = temp.left + original_w;	//x bottom right corner
			temp.bottom = temp.top + original_h;	//y bottom right corner


			sz_AnimationRegions.push_back(temp);
		}
		sz_once = true;
	}

	m_Imagepos.x = x;
	m_Imagepos.y = y;

	m_Imagesprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Imagesprite->Draw(m_Imagetexture, &sz_AnimationRegions.at(sz_AnimationIndex), NULL, &m_Imagepos, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	m_Imagesprite->End();

	if (dTimer->IsIdleOver())
	{
		sz_AnimationIndex++;

		if (sz_AnimationIndex > sz_Ammount - 1)
			sz_AnimationIndex = 0;

		dTimer->SetIdleTime(idle);
		dTimer->SetIdleHere();
	}
}

