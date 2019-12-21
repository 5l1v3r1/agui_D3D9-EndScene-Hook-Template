#pragma once
#include <string>
#include "fake_ntdll.h"


char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanModIn(char* pattern, char* mask, std::string modName);
char* ScanModIn(char* combopattern, std::string modName);
char* ScanModIn(char* combopattern, int offset, std::string modName);

void Parse(char* combo, char* pattern, char* mask);
char* TO_CHAR(wchar_t* string);


PEB* GetPEB();
LDR_DATA_TABLE_ENTRY* GetLDREntry(std::string name);