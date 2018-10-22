#pragma once
#include "Thread.h"
#define WORKER_THREAD_COUNT 4

class WorkThread : public Thread
{
public:
	void Run() override;
public:
	WorkThread();
	~WorkThread();
};