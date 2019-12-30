#pragma once
#include <Windows.h>
#include <time.h>

class TimeManager
{
public:
	TimeManager(DWORD IdleTime);
	~TimeManager();

private:
	DWORD _timeFactor;
	DWORD _idleTime;

public:
	void SetIdleHere();
	bool IsIdleOver();

	DWORD ReturnIdleTime();
	void SetIdleTime(DWORD IdleTime);
};

