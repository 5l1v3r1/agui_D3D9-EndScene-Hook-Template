#pragma once
#include <string>


char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
char* TO_CHAR(wchar_t* string);
char* ScanModIn(char* pattern, char* mask, std::string modName);