#include "stdafx.h"
#include "Signature.hpp"
#include "Engine.hpp"



CClientState::CClientState()
{
}

CClientState::~CClientState()
{
}

CClientState* CClientState::getClientState()
{
	return (CClientState*)(gSignature->dwClientState);
}

STATE CClientState::getState()
{
	return *(STATE*)(*(uintptr_t*)this + gSignature->dwClientState_State);
}

int CClientState::getMaxPlayer()
{
	return *(int*)(*(uintptr_t*)this + gSignature->dwClientState_MaxPlayer);
}

Vector3 CClientState::getViewAngle()
{
	return *(Vector3*)(*(uintptr_t*)this + gSignature->dwClientState_ViewAngles);
}

void CClientState::setViewAngle(Vector3& des)
{
	Vector3* view = (Vector3*)(*(uintptr_t*)this + gSignature->dwClientState_ViewAngles);
	view->Init(des);
}

bool CClientState::isIngame()
{
	if (getState() == STATE::INGAME)
		return true;
	return false;
}

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}


std::unique_ptr<CEngine> gEngine = std::make_unique<CEngine>();