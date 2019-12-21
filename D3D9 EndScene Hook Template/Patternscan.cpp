#include "stdafx.h"
#include "Patternscan.hpp"

//#include <Windows.h>


char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
{
	intptr_t patternLen = strlen(mask);

	for (int i = 0; i < size; i++)
	{
		bool found = true;
		for (int j = 0; j < patternLen; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (begin + i);
		}
	}
	return nullptr;
}

char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size)
{
	char* match{ nullptr };
	MEMORY_BASIC_INFORMATION mbi{};

	for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
	{
		if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

		match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

		if (match != nullptr)
		{
			break;
		}
	}
	return match;
}

char* ScanModIn(char* pattern, char* mask, std::string modName)
{
	LDR_DATA_TABLE_ENTRY* ldr = GetLDREntry(modName);

	char* match = ScanInternal(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);

	return match;
}

char* ScanModIn(char* combopattern, std::string modName)
{
	LDR_DATA_TABLE_ENTRY* ldr = GetLDREntry(modName);

	char pattern[100]{};
	char mask[100]{};
	Parse(combopattern, pattern, mask);

	char* match = ScanInternal(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);

	return match;
}

char* ScanModIn(char* combopattern, int offset, std::string modName)
{
	return ScanModIn(combopattern, modName) + offset;
}


PEB* GetPEB()
{
	//PEB* peb;
#ifdef _WIN64
	PEB* peb = (PEB*)__readgsword(0x60);

#else
	PEB* peb = (PEB*)__readfsdword(0x30);
#endif

	return peb;
}

LDR_DATA_TABLE_ENTRY* GetLDREntry(std::string name)
{
	LDR_DATA_TABLE_ENTRY* ldr = nullptr;

	PEB* peb = GetPEB();

	LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

	LIST_ENTRY curr = head;

	while (curr.Flink != head.Blink)
	{
		LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (mod->FullDllName.Buffer)
		{
			char* cName = TO_CHAR(mod->BaseDllName.Buffer);

			if (_stricmp(cName, name.c_str()) == 0)
			{
				ldr = mod;
				break;
			}
			delete[] cName;
		}
		curr = *curr.Flink;
	}
	return ldr;
}



void Parse(char* combo, char* pattern, char* mask)
{
	char lastChar = ' ';
	int j = 0;

	for (unsigned int i = 0; i < strlen(combo); i++)
	{
		if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
		{
			pattern[j] = mask[j] = '?';
			j++;
		}

		else if (isspace(lastChar))
		{
			pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
			mask[j] = 'x';
			j++;
		}
		lastChar = combo[i];
	}
	pattern[j] = mask[j] = '\0';
}

char* TO_CHAR(wchar_t* string)
{
	size_t len = wcslen(string) + 1;
	char* c_string = new char[len];
	size_t numCharsRead;
	wcstombs_s(&numCharsRead, c_string, len, string, _TRUNCATE);
	return c_string;
}