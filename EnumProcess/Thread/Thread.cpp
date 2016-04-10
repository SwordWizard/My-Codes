// Thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

DWORD WINAPI printThread(LPVOID lpParameter);

class TestThread
{
public:
	TestThread(int a){ this->a = a; };
	~TestThread(){};
	int add(int i){ return i + a;};
	void startThread();
protected:
private:
	int a;
};

void TestThread::startThread()
{
	HANDLE hThread = CreateThread(0, 0, printThread, (LPVOID)this, 0, 0);
}

DWORD WINAPI printThread(LPVOID lpParameter)
{
	TestThread *ptt = (TestThread*)lpParameter;
	for (int i = 0; i < 100; i++)
	{
		printf("print thread - %d\n", ptt->add(i));
		Sleep(250);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//HANDLE hThread = CreateThread(0, 0, printThread, 0, 0, 0);
	TestThread * ptt = new TestThread(38);
	ptt->startThread();
	for (int i = 0; i < 100; i++)
	{
		printf("main thread -- %d\n", i + 1);
		Sleep(500);
	}
	system("pause");
	return 0;
}

