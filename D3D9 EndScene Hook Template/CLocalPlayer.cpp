#include "stdafx.h"
#include "CLocalPlayer.hpp"
#include "Offsets.hpp"

CLocalPlayer::CLocalPlayer()
{
}

CLocalPlayer::~CLocalPlayer()
{
}

DWORD* CLocalPlayer::getPlayerBase()
{
	return (DWORD*)(gOffsets->dwLocalPlayer);
}

Vector* CLocalPlayer::getViewAngle()
{
	return (Vector*)(gOffsets->dwClientState + gOffsets->dwClientState_ViewAngles);
}

Vector* CLocalPlayer::getPosition()
{
	return (Vector*)(*getPlayerBase() + gOffsets->m_vecOrigin);
}

int CLocalPlayer::getTeam()
{
	return (int)(*getPlayerBase() + gOffsets->m_iTeamNum);
}

int CLocalPlayer::getHealth()
{
	return (int)(*getPlayerBase() + gOffsets->m_iHealth);
}

bool CLocalPlayer::isAlive()
{
	return getHealth() > 0 ? true : false;
}
