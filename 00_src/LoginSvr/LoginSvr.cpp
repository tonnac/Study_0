#include "stdafx.h"
#include "LoginSvr.h"
#include "Synchronize.h"


void LoginSvr::Run()
{
	while (1)
	{
		Synchronize ep(this);
	}
}

int main()
{
	Accept svr;
	svr.Set(12345);

	return 0;
}