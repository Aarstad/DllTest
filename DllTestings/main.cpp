// DllTestings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "App.h"


int main()
{
	App app;

	app.Name = "[object Object]";
	app.AppendService(L"TestService.dll");

	while(true)
	{
		app.Loop();
	}
}
