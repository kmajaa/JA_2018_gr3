// JAApp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <string>
#include "..\JADll_C\header.h"

extern "C" int _stdcall MyProc1(DWORD x, DWORD y);
//extern "C" void _stdcall greetUser(DWORD x, DWORD y);


int _tmain(int argc, _TCHAR* argv[])
{
	// statically link JADll.dll
	int x = 3, y = 4, z = 0, w = 0;

	// call assembly procedure found in library
	greetUser();
	z = MyProc1(x, y);

	system("pause");

	return 0;
}