#pragma once
#include "stdafx.h"
#include "Offsets.hpp"
#include "Patternscan.hpp"
#include "Netvars.hpp"

Offsets::Offsets()
{

}

Offsets::~Offsets()
{

}

void Offsets::initSignatures()
{

	dwLocalPlayer = *(DWORD*)ScanModIn("8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF", 0x3, "client_panorama.dll") + 4;
	dwEntityList = *(DWORD*)ScanModIn("BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", 0x1, "client_panorama.dll") + 4;
	dwForceJump = *(DWORD*)ScanModIn("8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", 0x2, "client_panorama.dll");
	dwForceAttack = *(DWORD*)ScanModIn("89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", 0x2, "client_panorama.dll");
	dwGlowObjectManager = *(DWORD*)ScanModIn("A1 ? ? ? ? A8 01 75 4B", 0x1, "client_panorama.dll");
	dwViewMatrix = *(DWORD*)ScanModIn("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9", 0x3, "client_panorama.dll") + 176;
	dwGetAllClasses = *(DWORD*)ScanModIn("A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", 0x1, "client_panorama.dll");
	dwGetAllClasses = *(DWORD*)dwGetAllClasses;
	m_bDormant = *(DWORD*)ScanModIn("8A 81 ? ? ? ? C3 32 C0", 0x2, "client_panorama.dll") + 8;

	model_ambient_min = *(DWORD*)ScanModIn("F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C", 0x4, "engine.dll");
	dwClientState = *(DWORD*)ScanModIn("A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", 0x1, "engine.dll");
	dwClientState_ViewAngles = *(DWORD*)ScanModIn("F3 0F 11 80 ? ? ? ? D9 46 04 D9 05", 0x4, "engine.dll");

}

void Offsets::initNetvars()
{
	m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", (ClientClass*)dwGetAllClasses);
	m_bSpotted = GetNetVarOffset("DT_BaseEntity", "m_bSpotted", (ClientClass*)dwGetAllClasses);
	m_fFlags = GetNetVarOffset("DT_CSPlayer", "m_fFlags", (ClientClass*)dwGetAllClasses);
	m_flFlashDuration = GetNetVarOffset("DT_CSPlayer", "m_flFlashDuration", (ClientClass*)dwGetAllClasses);
	m_iTeamNum = GetNetVarOffset("DT_BasePlayer", "m_iTeamNum", (ClientClass*)dwGetAllClasses);
	m_iCrosshairId = GetNetVarOffset("DT_CSPlayer", "m_bHasDefuser", (ClientClass*)dwGetAllClasses) + 92;
	m_iGlowIndex = GetNetVarOffset("DT_CSPlayer", "m_flFlashDuration", (ClientClass*)dwGetAllClasses) + 24;
	m_bIsDefusing = GetNetVarOffset("DT_CSPlayer", "m_bIsDefusing", (ClientClass*)dwGetAllClasses);
	m_clrRender = GetNetVarOffset("DT_BaseEntity", "m_clrRender", (ClientClass*)dwGetAllClasses);
	m_aimPunchAngle = GetNetVarOffset("DT_BasePlayer", "m_aimPunchAngle", (ClientClass*)dwGetAllClasses);
	m_iShotsFired = GetNetVarOffset("DT_CSPlayer", "m_iShotsFired", (ClientClass*)dwGetAllClasses);
	m_lifeState = GetNetVarOffset("DT_CSPlayer", "m_lifeState", (ClientClass*)dwGetAllClasses);
	m_vecOrigin = GetNetVarOffset("DT_BasePlayer", "m_vecOrigin", (ClientClass*)dwGetAllClasses);
	m_dwBoneMatrix = GetNetVarOffset("DT_BaseAnimating", "m_nForceBone", (ClientClass*)dwGetAllClasses) + 28;
}
std::unique_ptr<Offsets> gOffsets = std::make_unique<Offsets>();