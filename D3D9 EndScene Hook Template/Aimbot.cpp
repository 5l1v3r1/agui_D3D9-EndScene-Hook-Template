#include "stdafx.h"
#include "CLocalPlayer.hpp"
#include "CEntity.hpp"
#include "Engine.hpp"
#include "Aimbot.hpp"
#include "Print.hpp"
#include "PlayerList.hpp"


Vector3 Aimbot::calcAngle(Vector3 src, Vector3 dst)
{
	Vector3 angles;

	Vector3 delta = src - dst;
	float hyp = delta.GetLengthXYZ();
	angles.x = atanf(delta.z / hyp) * 180.0f / 3.141592f;
	angles.y = atanf(delta.y / delta.x) * 180.0f / 3.141592f;
	angles.z = 0.0f;

	if (delta.x >= 0.0f)
		angles.y += 180.0f;

	return angles;
}


Vector3 Aimbot::normalize(Vector3 src)
{
	while (src.y > 180)
		src.y -= 360;

	while (src.y < -180)
		src.y += 360;

	if (src.x > 89.0f)
		src.x = 89.0f;

	if (src.x < -89.0f)
		src.x = -89.0f;

	return src;
}

Vector3 Aimbot::smoothIt(Vector3 src, Vector3 dst)
{
	
	src = normalize(src);
	dst = normalize(dst);

	Vector3 dif = dst - src;

	dif = normalize(dif);//!!!!!!!!!!!!!!!!!!!!!


	dst.x = src.x + dif.x / 32;
	if (dif.y < 180.0f)
		dst.y = src.y + (dif.y / 64);
	else
		dst.y = src.y - (dif.y / 64);

	return dst;
}

Aimbot::Aimbot()
{
}

Aimbot::~Aimbot()
{
}

void Aimbot::Run()
{
	if (GetAsyncKeyState(VK_MENU) & 0x8000)
	{



	CEntity* bestTarget = nullptr;
	Vector3  bestTargetBone;
	QAngle   bestTargetAngle;
	float	 bestTargetAngleDif = 90.0f;
	
	if (gPlayerList->enemy.empty())
		return;

	Vector3 localPos	= CLocalPlayer::getLocalPlayer()->getPosition();
	Vector3 localEyePos	= localPos + CLocalPlayer::getLocalPlayer()->getViewOffset();
	QAngle  localView	= CClientState::getClientState()->getViewAngle();

	for (auto e : gPlayerList->enemy)
	{
		Vector3 entityBonePos		= e->getBonePosition(8);
		QAngle angleToBone			= calcAngle(localEyePos, entityBonePos);
		QAngle angleToBoneNorm		= normalize(angleToBone);
		QAngle angleDif				= localView - angleToBoneNorm;
		float  angleDifDistance		= angleDif.GetLength3D();

		if (angleDifDistance < bestTargetAngleDif)
		{
			bestTarget			= e;
			bestTargetBone		= entityBonePos;
			bestTargetAngle		= angleToBoneNorm;
			bestTargetAngleDif  = angleDifDistance;
		}
	}
	if (bestTarget)
	{
		WATCH(4, "%0.2f", bestTargetAngleDif);
		Vector3 angleSmooth = smoothIt(localView, bestTargetAngle);
		CClientState::getClientState()->setViewAngle(angleSmooth);
	}
	}
}

std::unique_ptr<Aimbot> g_aimbot = std::make_unique<Aimbot>();