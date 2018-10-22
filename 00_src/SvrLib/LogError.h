#pragma once
#include "SvrStd.h"
#include "SvrObject.h"

class LogError : public Singleton<LogError>, public SvrObject
{
	friend class Singleton<LogError>;
public:
	void T_ERROR();
private:
	LogError();
public:
	virtual ~LogError();
};

#define I_LOG LogError::getInst()
