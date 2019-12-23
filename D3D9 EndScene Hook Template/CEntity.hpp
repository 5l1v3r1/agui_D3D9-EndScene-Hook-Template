#pragma once
#include <Windows.h>
#include "Vector.hpp"

class CEntity
{
private:
	int m_iId;

public:
	CEntity();
	~CEntity();

	void setId(int i);
	int  getId();

	DWORD*	getEntityBase();
	Vector* getPosition();
	Vector  getBonePosition(int bone);

	int getHealth();
	int getTeam();
	bool isAlive();

};