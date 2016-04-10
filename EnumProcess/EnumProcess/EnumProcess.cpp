// EnumProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#pragma  comment(lib,"psapi.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	//第一中方式 CreateToolhelp32snapshot
	//HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//if (hSnap == INVALID_HANDLE_VALUE)
	//{
	//	return -1;
	//}

	//PROCESSENTRY32 pe32;
	//pe32.dwSize = sizeof(PROCESSENTRY32);
	//
	//if (!Process32First(hSnap,&pe32))
	//{
	//	printf(" Process32first failed!\n");
	//	return -1;
	//}

	//do 
	//{
	//	//printf("Process name:%s\n", pe32.szExeFile); 
	//	wprintf(L"Process name:%s\n", pe32.szExeFile);	//因为是宽字节版本，所以要用wprintf
	//} while ( Process32Next(hSnap,&pe32));
	//CloseHandle(hSnap);

	//第二种方式 EnumProcesses
	DWORD dwPID[500] = { 0 };
	DWORD dwCBNeed;
	EnumProcesses(dwPID, sizeof(dwPID), &dwCBNeed);
	for (DWORD i = 0; i < dwCBNeed / 4; i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID[i]);
		printf("process_id:%d\n", dwPID[i]);
		char path[256];
		RtlZeroMemory(path, 256);
		GetProcessImageFileNameA(hProcess, path, 256);
		printf("process file :%s\n...........................\n", path);
		if (strstr(path,"Calculator.exe")!=0)
		{
			printf("Terminate calc...\n");
			TerminateProcess(hProcess, 0);
		}
	}
	system("pause");
	return 0;
}

