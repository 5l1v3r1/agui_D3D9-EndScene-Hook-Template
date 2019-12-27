#include "stdafx.h"
#include "CLocalPlayer.hpp"
#include "Signature.hpp"


CLocalPlayer::CLocalPlayer()
{
}

CLocalPlayer::~CLocalPlayer()
{
}

DWORD* CLocalPlayer::getPlayerBase()
{
	return (DWORD*)(gSignature->dwLocalPlayer);
}

Vector* CLocalPlayer::getViewAngle()
{
	return (Vector*)(gSignature->dwClientState + gSignature->dwClientState_ViewAngles);
}

Vector* CLocalPlayer::getPosition()
{
	return (Vector*)(*getPlayerBase() + gSignature->m_vecOrigin);
}

int CLocalPlayer::getTeam()
{
	return (int)(*getPlayerBase() + gSignature->m_iTeamNum);
}

int CLocalPlayer::getHealth()
{
	return (int)(*getPlayerBase() + gSignature->m_iHealth);
}

bool CLocalPlayer::isAlive()
{
	return getHealth() > 0 ? true : false;
}
