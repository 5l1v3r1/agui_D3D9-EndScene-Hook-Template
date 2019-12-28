#pragma once
#include <Windows.h>
#include "Vector.hpp"


class CEntity
{
private:
	CEntity();
	~CEntity();

public:
	static CEntity* getEntity(int index);

	Vector3  getPosition();
	Vector3  getBonePosition(int bone);

	int getHealth();
	int getTeam();
	bool isAlive();
	bool isDead();
	bool isDormant();

};