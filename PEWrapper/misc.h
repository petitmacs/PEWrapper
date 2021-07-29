#pragma once
#include "pch.h"

typedef std::wstring String;

String convert(char argv[]);
TCHAR* convert1(char argv[]);
String convert(const char* argv);
std::string convert(String wstring);
String resolveIniFileName(const String exeFileName);