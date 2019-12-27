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

bool bInit = false;
TrampHook thEndScene;
tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
void* d3d9Device[119];

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (bInit == false)
	{
		pD3DDevice = pDevice;
		bInit = true;
		adrawing::gDraw->initDrawing((IDirect3DDevice9Ex*)pDevice);
		amenu::gMenu->initSettings();
		amenu::gMenu->initMenu();
		aconsole::gConsole->initSettings();
		aconsole::gConsole->initConsole();
	}

	//draw stuff here like so:
	//DrawFilledRect(200, 200, 200, 200, D3DCOLOR_ARGB(255, 255, 0, 0), pDevice);

	amenu::gMenu->drawMenu();
	aconsole::gConsole->drawConsole();

	static int counter = 0;

	WATCH(0, "%s", "I'm in a Loop");
	WATCH(1, "%p, %i", &counter, counter++);

	if (counter < 20)
		INGAME("I'm the counter 0x%p, %i", &counter, counter);

	return oEndScene(pDevice);
}

DWORD WINAPI Init(HMODULE hModule)
{

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		oEndScene = (tEndScene)thEndScene.trampHook((char*)d3d9Device[42], (char*)hkEndScene);
	}

	
	gSignature->initSignatures();
	gSignature->initNetvars();


	while (!(GetAsyncKeyState(VK_XBUTTON1) & 0x8000))
	{
		g_aimbot->Run();
		Sleep(1);
	}

	adrawing::gDraw->cleanUp();
	amenu::gMenu->cleanUpMenu();
	aconsole::gConsole->cleanUpConsole();
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