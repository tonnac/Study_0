#include "stdafx.h"
#include "Synchronize.h"

Synchronize::Synchronize(SvrObject * pSerObj)
{
	m_pSerObj = pSerObj;
	if (m_pSerObj != NULL)
	{
		EnterCriticalSection(&m_pSerObj->m_cs);
	}
}
Synchronize::~Synchronize()
{
	if (m_pSerObj != NULL)
	{
		LeaveCriticalSection(&m_pSerObj->m_cs);
	}
}