#pragma once
#include "Accept.h"

class LoginSvr : public Thread
{
public:
	void Run() override;
};