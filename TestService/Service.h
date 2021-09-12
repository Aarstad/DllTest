#pragma once

#include "../DllTestings/IService.h"
#include <iostream>

class Service : public IService
{
	int count = 0;
public:
	~Service()
	{
		std::cout << "Service destructor called\n";
	}
	void Shutdown() override
	{
		std::cout << "Service shutting down!\n";
	};
	void Startup() override
	{
		std::cout << "Service starting up!\n";
	};
	bool Process() override
	{
		if (count % 100 == 1)
			std::cout << "Hello from TestService DLL!\n";
		count++;
		return count != 1000;
	}
};

