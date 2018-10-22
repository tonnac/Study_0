#include "SvrObject.h"


SvrObject::SvrObject()
{
	InitializeCriticalSection(&m_cs);
}
SvrObject::~SvrObject()
{
	DeleteCriticalSection(&m_cs);
}