#pragma once
#include <memory>
#include "Vector.hpp"

class ESP
{
public:
	ESP();
	~ESP();

	bool WorldToScreen(Vector3 pos, Vector3& screen);
	void Run();
};

extern std::unique_ptr<ESP> gESP;