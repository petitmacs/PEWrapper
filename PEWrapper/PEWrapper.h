#pragma once
#define RETURN_CODE_OK                                0
#define RETURN_CODE_ERROR_ABSENT_INI_FILE             1
#define RETURN_CODE_ERROR_SHORTAGE_COMMAND_LINE_ARGS  2


// TODO: プログラムに必要な追加ヘッダーをここで参照してください
#include <string>
#include <windows.h>
#include "misc.h"

struct PsqlParam
{
	String program = L"psqledit.exe";
	String user;
	String password;
	String dbName;
	String host;
	String port;
	String option = L"";

	int findIndex = 0;
};

typedef struct PsqlParam PsqlParam;

BOOL CALLBACK EnumWndProcText(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnumWndProcButton(HWND hWnd, LPARAM lParam);
HWND FindLoginWindow(TCHAR* a, TCHAR* b);


int main0(int argc, TCHAR* argv[]);
