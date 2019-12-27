#include "stdafx.h"
#include "CLocalPlayer.hpp"
#include "CEntity.hpp"
#include "Aimbot.hpp"

Aimbot::Aimbot()
{
}

Aimbot::~Aimbot()
{
}

void Aimbot::Run()
{
	CLocalPlayer lPlayer;
	auto i = lPlayer.getHealth();
}

Vector Aimbot::normalize(Vector src)
{
	return Vector();
}

Vector Aimbot::smoothIt(Vector src, Vector des)
{
	return Vector();
}


std::unique_ptr<Aimbot> g_aimbot = std::make_unique<Aimbot>();