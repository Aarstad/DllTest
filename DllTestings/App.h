#pragma once
#include <Windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <map>

#include "ServiceData.h"
#include "IService.h"

class App
{
	std::vector<std::unique_ptr<ServiceData>> services;

	void Idle()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	void ProcessServices()
	{
		for (auto it = services.begin(); it != services.end();)
		{
			bool should_continue = (*it)->service->Process();
			if (should_continue)
			{
				++it;
			}
			else
			{
				it = services.erase(it);
			}
		}
	}
	
public:
	std::string Name;
	bool ShouldExit = false;
	void exit()
	{
		ShouldExit = true;
	}
	void AppendService(std::wstring lib_name)
	{
		std::wcout << "Loading library " << lib_name << "\n";
		auto h = LoadLibrary(lib_name.c_str());
		if (!h)
		{
			std::wcout << "Failed to load library " << lib_name << std::endl;
			return;
		}
		
		auto create_service = GetProcAddress(h, "CreateModule");
		if (!create_service)
		{
			std::wcout << "Failed to load CreateModule\n";
			return;
		}

		auto service = reinterpret_cast<IService*>(create_service());
		services.emplace_back(new ServiceData{lib_name, service, h});
		service->Startup();
	}
	
	void Loop()
	{
		// add a small sleep in case there's no work to do.
		if (services.size() == 0)
		{
			Idle();
		}
		else
		{
			ProcessServices();
		}
	}
};
