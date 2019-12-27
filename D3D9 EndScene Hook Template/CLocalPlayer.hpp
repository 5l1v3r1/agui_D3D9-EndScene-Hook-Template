#pragma once
#include <Windows.h>
#include "Vector.hpp"


class CLocalPlayer
{
public:
	CLocalPlayer();
	~CLocalPlayer();

	DWORD*	getPlayerBase();
	Vector* getViewAngle();
	Vector* getPosition();

	int getTeam();
	int getHealth();

	bool isAlive();

	//int* health = (int*) gOffsets->m_iHealth;

};
/*
class newPlayer
{
public:
	//int CLocalPlayer::* ptrHealth = &CLocalPlayer::health;
	//int CLocalPlayer::* ptrHealth;
};

//typedef int(CLocalPlayer::* ptrHealth);

void func()
{

	//newPlayer p;
	//p.ptrHealth = (CLocalPlayer::health)(gOffsets->dwLocalPlayer + gOffsets->m_iHealth);

	//int CLocalPlayer::* pmd = &CLocalPlayer::health;
	int CLocalPlayer::* pmd = &CLocalPlayer::health;

	//ptrHealth p = &CLocalPlayer::health;
	ptrHealth p = (&CLocalPlayer::health)(0x100);

	int* px = (int*)0x100;

	CLocalPlayer l;
	l.*pmd = 3;
	
	
	l.*p = 3;
	
}
*/