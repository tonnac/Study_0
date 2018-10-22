#pragma once
#include "Thread.h"
#include "Syncc.h"

class LoginSvr : public Thread
{
public:
	Synchronize sync;
public:
	void Run() override;
};