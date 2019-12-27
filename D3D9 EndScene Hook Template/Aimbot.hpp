#pragma once
#include <memory>
#include "Vector.hpp"

class Aimbot
{
public:
	Aimbot();
	~Aimbot();

	void Run();

	Vector normalize(Vector src);
	Vector smoothIt(Vector src, Vector des);

};

extern std::unique_ptr<Aimbot> g_aimbot;