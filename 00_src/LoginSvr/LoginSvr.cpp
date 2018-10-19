#include "stdafx.h"
#include "Accept.h"
#include "Synchronize.h"

class LoginSvr : public Thread
{
public:
	void Run() override;
	void Frame()
	{
		while (1)
		{
		}
	}
};

void LoginSvr::Run()
{
	while (1)
	{
		Synchronize sync(this);
	}
	int kkk = 0;
}

int main()
{
	LoginSvr Svr;

	Svr.Frame();

	return 0;
}