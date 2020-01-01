#include "stdafx.h"
#include <windows.h>
#include "Hook.hpp"
#include "gh_d3d9.h"
#include "adrawing.hpp"
#include "amenu.hpp"
#include "aconsole.hpp"
#include "Print.hpp"
#include "Signature.hpp"
#include "Aimbot.hpp"
#include "Render.hpp"
#include "PlayerList.hpp"
#include "ESP.hpp"

#include "D3DImage.h"
#include "Halo.h"
D3DImage* __img_arrHalo;

enum STATE
{
	INIT,
	DRAW,
	CLEAN,
	FINISH
};

STATE bState = STATE::INIT;
TrampHook thEndScene;
tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
void* d3d9Device[119];

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (bState == STATE::INIT)
	{
		pD3DDevice = pDevice;
		adrawing::gDraw->initDrawing((IDirect3DDevice9Ex*)pDevice);
		amenu::gMenu->initSettings();
		amenu::gMenu->initMenu();
		aconsole::gConsole->initSettings();
		aconsole::gConsole->initConsole();
		gRender->Init((IDirect3DDevice9Ex*)pDevice);
		__img_arrHalo = new D3DImage();
		__img_arrHalo->InitImage(pDevice, arrHalo, 10055);

		gSignature->initSignatures();
		gSignature->initNetvars();
		bState = STATE::DRAW;
	}

	if (bState == STATE::DRAW)
	{
		amenu::gMenu->drawMenu();
		aconsole::gConsole->drawConsole();

		static int counter = 0;
		if (counter < 4)
			INGAME("I'm the counter 0x%p, %i", &counter, counter);

		WATCH(0, "%s", "I'm in a Loop");
		WATCH(1, "%p, %i", &counter, counter++);
		WATCH(2, "%i", gRender->getWidth());
		WATCH(3, "%i", gRender->getHeight());

		//gRender->String(200, 400, WHITE, false, "Small");
		//gRender->String(300, 400, WHITE, true, "Big");
		//gRender->StringOutlined(400, 400, WHITE, false, "OUT1");
		//gRender->StringOutlined(500, 400, WHITE, true, "OUT2");
		//gRender->Rect(200, 500, 40, 40, WHITE);
		//gRender->BorderBox(300, 500, 40, 40, 4, WHITE);
		//gRender->BorderBoxOutlined(400, 500, 40, 40, 4, WHITE, BLACK);
		//gRender->RectOutlined(500, 500, 40, 40, WHITE, BLACK, 4);
		//gRender->Line(200, 600, 240, 640, WHITE, 5.0f);
		//gRender->Cross(300, 600, 40, 40, WHITE, 5.0f);
		//gRender->Crosshair(420, 620, 20, WHITE, 2.0f);
		//gRender->DrawCircleFilled(200, 720, 20, WHITE);
		//gRender->DrawCircle(300, 720, 20, 1, WHITE);
		//gRender->GardientRect(400, 700, 40, 40, 2, 1, BLACK, WHITE, WHITE);
		//gRender->Texture(100, 100, nullptr, nullptr);

		__img_arrHalo->DrawImage(200, 200);

		gPlayerList->clear();
		gPlayerList->fill();

		g_aimbot->Run();
		gESP->Run();
	}

	if (bState == STATE::CLEAN)
	{
		adrawing::gDraw->cleanUp();
		amenu::gMenu->cleanUpMenu();
		aconsole::gConsole->cleanUpConsole();
		gRender->CleanUp();
		bState = STATE::FINISH;
	}

	//draw stuff here like so:
	//DrawFilledRect(200, 200, 200, 200, D3DCOLOR_ARGB(255, 255, 0, 0), pDevice);

	return oEndScene(pDevice);
}

DWORD WINAPI Init(HMODULE hModule)
{

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		oEndScene = (tEndScene)thEndScene.trampHook((char*)d3d9Device[42], (char*)hkEndScene);
	}


	while (!(GetAsyncKeyState(VK_XBUTTON1) & 0x8000))
	{		
		Sleep(1);
	}

	bState = STATE::CLEAN;
	while (bState != STATE::FINISH)
		Sleep(1);

	thEndScene.trampUnhook();
	Sleep(200);
	FreeLibraryAndExitThread(hModule, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		HANDLE hThread = nullptr;
		hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, nullptr);
		if (hThread)
			CloseHandle(hThread);
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}