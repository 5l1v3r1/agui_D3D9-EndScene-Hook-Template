#include "stdafx.h"
#include "CLocalPlayer.hpp"
#include "Signature.hpp"
#include "Engine.hpp"


CLocalPlayer::CLocalPlayer()
{
}

CLocalPlayer::~CLocalPlayer()
{
}

CLocalPlayer* CLocalPlayer::getLocalPlayer()
{
	return (CLocalPlayer*)(gSignature->dwLocalPlayer);
}

Vector3 CLocalPlayer::getViewAngle()
{
	return CClientState::getClientState()->getViewAngle();
}

Vector3 CLocalPlayer::getPosition()
{
	return *(Vector3*)(*(uintptr_t*)this + gSignature->m_vecOrigin);
}

Vector3 CLocalPlayer::getViewOffset()
{
	return *(Vector3*)(*(uintptr_t*)this + gSignature->m_vecViewOffset);
}

void CLocalPlayer::setViewAngle(Vector3& des)
{
	CClientState::getClientState()->setViewAngle(des);
}

int CLocalPlayer::getTeam()
{
	return *(int*)(*(uintptr_t*)this + gSignature->m_iTeamNum);
}

int CLocalPlayer::getHealth()
{
	return *(int*)(*(uintptr_t*)this + gSignature->m_iHealth);
}

bool CLocalPlayer::isAlive()
{
	return getHealth() > 0 ? true : false;
}
