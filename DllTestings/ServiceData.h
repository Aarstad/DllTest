#pragma once
#include "IService.h"
#include <Windows.h>
#include <iostream>

struct ServiceData
{
	std::wstring dll_name;
	IService* service;
	HMODULE lib_handle;
	~ServiceData()
	{
		std::wcout << "buh bye " << dll_name << "\n";
		service->Shutdown();
		delete service;
		FreeLibrary(lib_handle);
	};
};