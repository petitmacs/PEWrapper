#include "pch.h"
#include "misc.h"

String getParentPath(const String path) {
	String nextPath = String(path);
	size_t pos = nextPath.find_last_of(L"\\");
	String returnPath = String(nextPath.substr(0, pos + 1));
	return returnPath;
}

String getFileName(const String path) {
	String nextPath = String(path);
	size_t pos = nextPath.find_last_of(L"\\");
	size_t len = nextPath.length();
	String returnPath = String(nextPath.substr(pos + 1, len));
	return returnPath;
}

String resolveIniFileName(const String exeFileName) {
	size_t pos = exeFileName.find_last_of(L".");
	return exeFileName.substr(0, pos + 1) + L"ini";
}

String resolveIniFilePath(const String exeFilePath) {
	String dirPath = getParentPath(exeFilePath);
	String exeFileName = getFileName(exeFilePath);
	String iniFileName = resolveIniFileName(exeFileName);
	String iniFilePath = dirPath + iniFileName;
	return iniFilePath;
}


String convert(char argv[]) {
	std::string s = std::string(argv);
	size_t length = s.length() * MB_LEN_MAX;
	setlocale(LC_CTYPE, "");
	wchar_t *buffer = new wchar_t[length + 1];
	size_t ret;
	mbstowcs_s(&ret, buffer, (length + 1) + 1, argv, _TRUNCATE);
	String string = String(buffer);
	//delete buffer;
	return string;
}

TCHAR* convert1(char argv[]) {
	std::string s = std::string(argv);
	size_t length = s.length() * MB_LEN_MAX;
	//setlocale(LC_CTYPE, "");
	TCHAR *buffer = new wchar_t[length + 1];
	size_t ret;
	mbstowcs_s(&ret, buffer, (length + 1) + 1, argv, _TRUNCATE);
	String string = String(buffer);
	//delete buffer;
	return buffer;
}

String convert(const char* argv) {
	std::string s = std::string(argv);
	size_t length = s.length() * MB_LEN_MAX;
	//setlocale(LC_CTYPE, "");
	wchar_t *buffer = new wchar_t[length + 1];
	size_t ret;
	mbstowcs_s(&ret, buffer, (length + 1) + 1, argv, _TRUNCATE);
	String string = String(buffer);
	//delete buffer;
	return string;
}


std::string convert(String wstring) {
	size_t length = wstring.length();
	char *buffer = new char[length + 1];
	size_t ret;
	wcstombs_s(&ret, buffer, length + 2, wstring.c_str(), _TRUNCATE);
	std::string string = std::string(buffer);
	return string;
}