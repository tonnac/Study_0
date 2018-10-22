#pragma once

#ifndef ExptSocketError
#define ExptSocketError(x)			\
{									\
	int iRet = (x);					\
	if (iRet == SOCKET_ERROR)		\
	{								\
		return false;				\
	}								\
}
#endif

template <typename X>
class Singleton
{
protected:
	Singleton();
public:
	static X& getInst()
	{
		static X inst;
		return inst;
	}
};

