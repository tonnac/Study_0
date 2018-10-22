#include "stdafx.h"
#include "Synchronize.h"
#include "SvrObject.h"

Synchronize::Synchronize(SvrObject * pSvrObj) : m_pSvrObj(pSvrObj)
{
	if (m_pSvrObj != NULL)
	{
		EnterCriticalSection(&m_pSvrObj->m_cs);
	}
}
Synchronize::~Synchronize()
{
	if (m_pSvrObj != NULL)
	{
		LeaveCriticalSection(&m_pSvrObj->m_cs);
	}
}