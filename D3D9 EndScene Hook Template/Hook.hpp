#pragma once

class Hook
{
	char  orignal[100];
	int   length;
	char* address;

public:
	Hook() : orignal{ 0 }, length(0), address(nullptr) { };

	bool hook(char* src, char* dst, int len);
	bool unhook();
};

class TrampHook
{
	char* gateway;
	int   length;
	Hook  h;

public:
	TrampHook() : gateway(nullptr), length(0) { };

	char* trampHook(char* src, char* dst, unsigned int len);
	char* trampHook(char* src, char* dst);
	int   getTrampHookLength(char* src);
	bool  trampUnhook();
};
