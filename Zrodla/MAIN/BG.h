#pragma once
#include <thread>
#include <iostream>

#define CHUNK_SIZE 16

class BackgroundTask
{
	char* buffer;
public:
	BackgroundTask()
	{

	}
	BackgroundTask(char* buf)
	{
		buffer = buf;
	}

	void operator ()() const
	{
		//std::cout << "Hello from a thread" << std::endl;
		std::cout << buffer;
	}

	void setBuffer(char* buf)
	{
		buffer = buf;
	}

};