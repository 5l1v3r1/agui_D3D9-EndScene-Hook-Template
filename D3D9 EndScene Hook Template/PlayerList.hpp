#pragma once
#include <vector>
#include <memory>
#include "CEntity.hpp"

class PlayerList
{
public:
	PlayerList();
	~PlayerList();

	void clear();
	void fill();

	std::vector<CEntity*> all;
	std::vector<CEntity*> enemy;
	std::vector<CEntity*> ally;

};

extern std::unique_ptr<PlayerList> gPlayerList;