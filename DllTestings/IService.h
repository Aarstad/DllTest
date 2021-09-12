#pragma once

class IService
{
public:
	virtual ~IService() {};
	virtual void Startup() = 0;
	virtual void Shutdown() = 0;
	virtual bool Process() = 0;
};