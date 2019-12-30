#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager(DWORD IdleTime)
{
	_timeFactor = IdleTime;
	_idleTime = 0;
}


TimeManager::~TimeManager()
{
}

void TimeManager::SetIdleHere()
{
	_idleTime = GetTickCount();
	_idleTime = _idleTime + _timeFactor;
}

bool TimeManager::IsIdleOver()
{
	DWORD temp = GetTickCount();

	if (temp >= _idleTime)
		return true;

	return false;
}

DWORD TimeManager::ReturnIdleTime()
{
	return _timeFactor;
}

void TimeManager::SetIdleTime(DWORD IdleTime)
{
	_timeFactor = IdleTime;
}

