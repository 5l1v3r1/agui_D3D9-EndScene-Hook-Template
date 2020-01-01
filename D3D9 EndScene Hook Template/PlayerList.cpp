#include "stdafx.h"
#include "PlayerList.hpp"
#include "Engine.hpp"
#include "CLocalPlayer.hpp"

PlayerList::PlayerList()
{
}

PlayerList::~PlayerList()
{
}

void PlayerList::clear()
{
	all.clear();
	ally.clear();
	enemy.clear();
}

void PlayerList::fill()
{
	CClientState* cs = CClientState::getClientState();
	if (!cs->isIngame())
		return;

	CLocalPlayer* localPlayer = CLocalPlayer::getLocalPlayer();
	if (!localPlayer)
		return;

	if (!(*(uint32_t*)localPlayer))
		return;

	for (int i = 1; i < cs->getMaxPlayer(); i++)
	{
		CEntity* entity = CEntity::getEntity(i);
		if (!entity)
			continue;

		if (!(*(uint32_t*)entity))
			continue;

		if ((uintptr_t*)entity == (uintptr_t*)localPlayer)
			continue;

		if (entity->isDead())
			continue;

		if (entity->isDormant())
			continue;

		all.push_back(entity);

		if (entity->getTeam() == localPlayer->getTeam())
			ally.push_back(entity);

		if (entity->getTeam() != localPlayer->getTeam())
			enemy.push_back(entity);
	}
}

std::unique_ptr<PlayerList> gPlayerList = std::make_unique<PlayerList>();