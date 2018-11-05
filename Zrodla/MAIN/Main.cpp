/*
* vigenere.c
* by Maja Kurcius
*
* Enciphers the plaintext given by the user according
* to the set of keys in keyword given by the user as a command-line argument.
*
* Usage: ./vigenere text_file key
*
*/

//
#include "stdafx.h"
#include <windows.h>	// dynamic loading of DLLs
#include <iostream>		// std::cin, std::cout, ...
#include <fstream>		// input & output files
#include <string>		// string
#include "Header.h"		// my functions, e.g. isAlphaOnly(std::string)
#include <thread>		// multithreading
#include "BG.h"			// BackgroundTask class
#include <vector>		// vector container

#define CHUNK_SIZE 16	// number of characters read to buffer/register at once

int main(int argc, char* argv[])
{
	// detect & display number of cores
	SYSTEM_INFO sisysinfo;
	GetSystemInfo(&sisysinfo);
	int procnum = sisysinfo.dwNumberOfProcessors;
	std::cout << "No. processors: " << procnum << std::endl;

	// check number of parameters
	// if no file & key given, exit
	if (argc != 3)
	{
		std::cout << "Invalid number of arguments!" << std::endl;
		system("pause");
		return 1;
	}

	// if key is not letters-only, exit
	char* kword = argv[2];
	if (!isAlphaOnly(kword))
	{
		std::cout << "Invalid key!" << std::endl;
		system("pause");
		return 1;
	}
	const int klen = strlen(kword);

	// open input file; if not possible, exit
	std::ifstream iFile;
	char* iFName = argv[1];
	iFile.open(iFName);
	if (!iFile.is_open())
	{
		std::cout << "Could not open file!" << std::endl;
		system("pause");
		return 1;
	}

	// prompt user for number of threads; default set to 1
	int no_threads = 1;
	std::cout << "How many threads? " << std::endl;
	try 
	{
		std::cin >> no_threads;
	}
	catch (const std::exception& e) 
	{
		std::cout << "Invalid input! Defaulting to 1 thread..." << std::endl;
	};

	// set up chosen no. of threads and tasks to forward to threads
	std::vector<std::thread> threads;
	std::vector<BackgroundTask> tasks;
	for (int j = 0; j < no_threads; j++)
	{
		// get a 16-char chunk of text
		char buffer[CHUNK_SIZE + 1] = { '\0' };
		if (iFile.is_open())
		{
			for (int i = 0; i < CHUNK_SIZE && !iFile.eof(); i++)
				iFile.get(buffer[i]);
			//std::cout << "Buffer: " << buffer << std::endl;
		}
		else std::cout << "Unable to open file";

		// create a task processing the buffer and forward it to a new thread
		tasks.push_back(BackgroundTask(buffer));
		threads.push_back(std::thread(tasks[j]));
		threads[j].join();
	}

	std::cout << std::endl;

	// dynamically load assembly lg DLL
	typedef char*(_fastcall *Vigenere)(char*, char*, int, char*, int);
	HINSTANCE dllAHandle = NULL;
	dllAHandle = LoadLibrary(L"JADll.dll");
	Vigenere vigA = (Vigenere)GetProcAddress(dllAHandle, "Vigenere");

	// dynamically load Cpp DLL
	typedef void(_fastcall *VigenereC)(char*, char*, int, char*, int);
	HINSTANCE dllCHandle = NULL;
	dllCHandle = LoadLibrary(L"JADll_C.dll");
	VigenereC vigC = (VigenereC)GetProcAddress(dllCHandle, "VigenereC");

	
	char* retVal = "Bober1";
	char dest[10] = {0};
	int len = strlen(retVal);
	char* tmp = vigA(retVal, dest, len, kword, klen);


	std::cout << "RDX: " << dest << std::endl;
	//std::cout << "RAX: " << tmp << std::endl;

	// close input file
	if (iFile.is_open())
		iFile.close();

	system("pause");
	
	return 0;
}


