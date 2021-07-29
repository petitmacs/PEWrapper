// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include "PEWrapper.h"
#include "misc.h"



int main(const int argc, char* argv[]) {

	TCHAR buffer[1024];
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	String thisFilePath = String(buffer);
	String initFilePath = resolveIniFileName(thisFilePath);

	TCHAR psql[1024];
	TCHAR sharp[1024];
	TCHAR version[1024];


	//
	TCHAR user[1024];
	TCHAR pass[1024];
	TCHAR host[1024];
	TCHAR port[1024];
	TCHAR database[1024];

	GetPrivateProfileString(TEXT("psqledit"), TEXT("exe_path"), TEXT("***"), psql, sizeof(psql), initFilePath.c_str());
	GetPrivateProfileString(TEXT("psqledit"), TEXT("sharp"), TEXT("#32770"), sharp, sizeof(sharp), initFilePath.c_str());
	GetPrivateProfileString(TEXT("psqledit"), TEXT("version"), TEXT("PSqlEdit Ver.5.2.0.1 Login"), version, sizeof(version), initFilePath.c_str());

	bool absentIniFile = String(psql)._Equal(L"***");
	if (absentIniFile) {
		return RETURN_CODE_ERROR_ABSENT_INI_FILE;
	}

	bool presentInputFile = false;
	if (argc > 1) {
		String inputFilePath = convert(argv[1]);
		GetPrivateProfileString(TEXT("connection"), TEXT("user"), TEXT("***"), user, sizeof(user), inputFilePath.c_str());
		GetPrivateProfileString(TEXT("connection"), TEXT("password"), TEXT(""), pass, sizeof(pass), inputFilePath.c_str());
		GetPrivateProfileString(TEXT("connection"), TEXT("host"), TEXT("***"), host, sizeof(host), inputFilePath.c_str());
		GetPrivateProfileString(TEXT("connection"), TEXT("port"), TEXT("5432"), port, sizeof(port), inputFilePath.c_str());
		GetPrivateProfileString(TEXT("connection"), TEXT("database"), TEXT("***"), database, sizeof(database), inputFilePath.c_str());
		presentInputFile = !String(user)._Equal(L"***");
	}

	if (argc < 2) {
		MessageBox(NULL, L"arguments are ... \r\n connection file path \r\n or \r\n1 user\r\n2 password\r\n3 database name\r\n4 host or ip\r\n5 port (nesessary even if 5432)", L"Message", MB_OK);
		return RETURN_CODE_ERROR_SHORTAGE_COMMAND_LINE_ARGS;
	}

	if (presentInputFile) {
		TCHAR argv0[] = L"opener";
		TCHAR* argv1 = user;
		TCHAR* argv2 = pass;
		TCHAR* argv3 = database;
		TCHAR* argv4 = host;
		TCHAR* argv5 = port;
		TCHAR argv9[] = L"";
		TCHAR* argArray[] = { argv0,argv1,argv2,argv3,argv4,argv5,psql,sharp,version,argv9 };
		return main0(10, argArray);
	}
	
	if (argc > 6) {
		TCHAR* argv0 = convert1(argv[0]);
		TCHAR* argv1 = convert1(argv[1]);
		TCHAR* argv2 = convert1(argv[2]);
		TCHAR* argv3 = convert1(argv[3]);
		TCHAR* argv4 = convert1(argv[4]);
		TCHAR* argv5 = convert1(argv[5]);
		TCHAR* argv6 = convert1(argv[6]);
		TCHAR* argv7 = convert1(argv[7]);
		TCHAR* argv8 = convert1(argv[8]);
		TCHAR argv9[] = L"";
		TCHAR* argArray[] = { argv0,argv1,argv2,argv3,argv4,argv5,argv6,argv7,argv8,argv9 };
		return main0(10, argArray);
	}
	else {
		TCHAR* argv0 = convert1(argv[0]);
		TCHAR* argv1 = convert1(argv[1]);
		TCHAR* argv2 = convert1(argv[2]);
		TCHAR* argv3 = convert1(argv[3]);
		TCHAR* argv4 = convert1(argv[4]);
		//
		TCHAR argv9[] = L"";
		TCHAR* argArray[] = { argv0,argv1,argv2,argv3,argv4,psql,sharp,version,argv9 };
		return main0(10, argArray);
	}
		
	return RETURN_CODE_OK;
}

int main0(const int argc, TCHAR* argv[])
{
	PsqlParam p;
	p.user = argv[1];
	p.password = argv[2];
	p.dbName = argv[3];
	p.host = argv[4];
	p.port = argv[5];

	if (argc > 6)
	{
		p.program = argv[6];
	}

	WinExec(convert(p.program).c_str(), SW_SHOW);
	Sleep(100);
	HWND hWnd = FindLoginWindow(argv[7], argv[8]);
	if (hWnd == 0)
	{
		Sleep(100);
		hWnd = FindLoginWindow(argv[7], argv[8]);
		if (hWnd == 0)
		{
			printf("エラー psql.exeが見つからない\n");
			return 0;
		}
	}
	EnumChildWindows(hWnd, ::EnumWndProcText, (LPARAM)&p);
	if (false == p.password.empty()) {
		EnumChildWindows(hWnd, ::EnumWndProcButton, (LPARAM)&p);
	}

	return (int)hWnd;
}

BOOL CALLBACK EnumWndProcText(HWND hWnd, LPARAM lParam)
{
	TCHAR buff[256] = L"";
	TCHAR buff2[256] = L"";

	PsqlParam* param = reinterpret_cast<PsqlParam*>(lParam);
	RealGetWindowClass(hWnd, buff, sizeof(buff));
	GetWindowText(hWnd, buff2, sizeof(buff2));
	if (wcscmp(buff, L"Edit") == 0)
	{
		switch (param->findIndex)
		{
		case 0:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->user.c_str());
			printf("set USER %ls\n", param->user.c_str());
			break;
		case 1:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->password.c_str());
			printf("SET PASSWORD %ls\n", param->password.c_str());
			break;
		case 2:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->dbName.c_str());
			printf("SET DB NAME %ls\n", param->dbName.c_str());
			break;
		case 3:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->host.c_str());
			printf("SET HOST %ls\n", param->host.c_str());
			break;
		case 4:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->port.c_str());
			printf("SET PORT %ls\n", param->port.c_str());
			break;
		case 5:
			SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)param->option.c_str());
			printf("SET OPTION %ls\n", param->option.c_str());
			break;
		}
		param->findIndex++;
	}
	return true;
}

BOOL CALLBACK EnumWndProcButton(HWND hWnd, LPARAM lParam)
{
	TCHAR buff[256] = L"";
	TCHAR buff2[256] = L"";

	RealGetWindowClass(hWnd, buff, sizeof(buff));
	GetWindowText(hWnd, buff2, sizeof(buff2));
	if (wcscmp(buff, L"Button") == 0 && wcscmp(buff2, L"OK") == 0) {
		SendMessage(hWnd, BM_CLICK, 0, 0);
	}
	return true;
}

HWND FindLoginWindow(TCHAR* a, TCHAR* b)
{
	HWND hWnd = FindWindow(a, b);
	return hWnd;
}

