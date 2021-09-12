// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Service.h"
#include "../DllTestings/IService.h"

extern "C"
__declspec (dllexport)  IService* CreateModule()
{
	// call the constructor of the actual implementation
	IService* service = new Service();
	// return the created function
	return service;
}