#pragma once
#include <memory>
#include "Vector.hpp"

enum STATE : int
{
	LOBBY,
	LOADING,
	CONNECTING,
	CONNECTED = 5,
	INGAME
};

class CClientState
{
private:
	CClientState();
	~CClientState();

public:
	static CClientState* getClientState();

	STATE getState();
	int getMaxPlayer();
	Vector3 getViewAngle();
	void setViewAngle(Vector3& des);


	bool isIngame();
};

class CEngine
{
public:
	CEngine();
	~CEngine();

	//CClientState* ClientState = nullptr;
	
};

extern std::unique_ptr<CEngine> gEngine;