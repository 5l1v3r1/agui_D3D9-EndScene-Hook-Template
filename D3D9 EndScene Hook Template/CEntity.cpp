#include "stdafx.h"
#include "Signature.hpp"
#include "CEntity.hpp"


CEntity::CEntity()
{
}

CEntity::~CEntity()
{
}

CEntity* CEntity::getEntity(int index)
{
	uintptr_t entityList = (uintptr_t)(gSignature->dwEntityList);
	return (CEntity*)(entityList + index * 0x10);
}


Vector3 CEntity::getPosition()
{
	return *(Vector3*)(*(uintptr_t*)this + gSignature->m_vecOrigin);
}

Vector3 CEntity::getBonePosition(int bone)
{
	uintptr_t boneMatrix = *(uintptr_t*)(*(uintptr_t*)this + gSignature->m_dwBoneMatrix);
	Vector3 dst;
	dst.x = *(float*)(boneMatrix + 0x30 * bone + 0x0C);
	dst.y = *(float*)(boneMatrix + 0x30 * bone + 0x1C);
	dst.z = *(float*)(boneMatrix + 0x30 * bone + 0x2C);
	return dst;
}

int CEntity::getHealth()
{
	return *(int*)(*(uintptr_t*)this + gSignature->m_iHealth);
}

int CEntity::getTeam()
{
	return *(int*)(*(uintptr_t*)this + gSignature->m_iTeamNum);
}

bool CEntity::isAlive()
{
	return getHealth() > 0 ? true : false;
}

bool CEntity::isDead()
{
	return !isAlive();
}

bool CEntity::isDormant()
{
	return *(bool*)(*(uintptr_t*)this + gSignature->m_bDormant);
}
