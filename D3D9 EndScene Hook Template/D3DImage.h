#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#include <vector>
#include "TimeManager.h"

class D3DImage
{
public:
	D3DImage();
	~D3DImage();


	LPDIRECT3DTEXTURE9		m_Imagetexture;
	LPD3DXSPRITE			m_Imagesprite;
	D3DXVECTOR3				m_Imagepos;

	D3DXVECTOR2				m_Imagecenter;
	D3DXMATRIX				m_Imagerotation;

	int sz_image_w, sz_image_h;

	void InitImage(LPDIRECT3DDEVICE9 pDevice, BYTE* image, int size);
	void InitImageS(LPDIRECT3DDEVICE9 pDevice, BYTE* image, int size, int w, int h);

	void InitImageFromFile(LPDIRECT3DDEVICE9 pDevice, LPSTR filename);
	void InitImageFromFileS(LPDIRECT3DDEVICE9 pDevice, LPSTR filename, int w, int h);

	void DrawImage(int x, int y);
	void DrawImageA(int x, int y, int alpha);
	void DrawImageAsCrosshair(D3DVIEWPORT9 port);
	void DrawImageAsCrosshairA(int alpha, D3DVIEWPORT9 port);

	void DrawImageR(int x, int y, int angle);
	void DrawImageAR(int x, int y, int angle, int alpha);

	void AnimateImage(int x, int y, int original_w, int original_h, int idle);
	void AnimateImageA(int x, int y, int original_w, int original_h, int idle, int alpha);

private:
	int sz_AnimationIndex;
	int sz_Ammount;
	std::vector<RECT> sz_AnimationRegions;
	TimeManager* dTimer;
	bool sz_once;
};

