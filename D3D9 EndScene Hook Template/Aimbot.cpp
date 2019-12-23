#include "stdafx.h"
#include "Aimbot.hpp"
#include "CLocalPlayer.hpp"
#include "CEntity.hpp"

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


std::unique_ptr<Aimbot> g_aimbot = std::make_unique<Aimbot>();