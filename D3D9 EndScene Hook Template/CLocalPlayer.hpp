#pragma once
#include <Windows.h>
#include "Vector.hpp"


class CLocalPlayer
{
	CLocalPlayer();
	~CLocalPlayer();

public:
	static CLocalPlayer* getLocalPlayer();


	Vector3 getViewAngle();
	Vector3 getPosition();
	Vector3 getViewOffset();

	void setViewAngle(Vector3& des);

	int getTeam();
	int getHealth();
	bool isAlive();


};
