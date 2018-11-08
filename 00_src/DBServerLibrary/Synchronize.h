#pragma once
#include "ServerObj.h"

class Synchronize
{
public:
	Synchronize(ServerObj* serverObj);
	~Synchronize();
private:
	ServerObj * mServerObj;
};