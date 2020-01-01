#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "CEntity.hpp"
#include "Vector.hpp"

class Aimbot
{
	//void getBestTarget(std::vector<CEntity*>& enemyList);
	Vector3 calcAngle(Vector3 src, Vector3 des);
	Vector3 normalize(Vector3 src);
	Vector3 smoothIt(Vector3 src, Vector3 dst);



public:
	Aimbot();
	~Aimbot();

	void Run();


};

extern std::unique_ptr<Aimbot> g_aimbot;