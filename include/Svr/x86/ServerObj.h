#pragma once
#include "SrvUtil.h"

class ServerObj
{
public:
	ServerObj();
	virtual ~ServerObj();
public:
	CRITICAL_SECTION& getCS();
protected:
	CRITICAL_SECTION mCs;
};
