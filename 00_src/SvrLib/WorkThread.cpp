#include "stdafx.h"
#include "WorkThread.h"
#include "SvrIOCP.h"
#include "User.h"
#include "LogError.h"

void WorkThread::Run()
{
	while (1)
	{
		int iRet = 0;
		DWORD Bytes;
		PULONG_PTR Key = 0;
		LPOVERLAPPED_EX ovex;
		LPOVERLAPPED ov;
		iRet = ::GetQueuedCompletionStatus(I_IOCP.m_hIOCP, &Bytes, Key, &ov, WSA_INFINITE);
		if (iRet == TRUE)
		{
			ovex = (LPOVERLAPPED_EX)ov;
			User * pUser = (User*)Key;
			if (pUser == NULL)
			{
				I_LOG.T_ERROR();
				continue;
			}
			if (Bytes != 0 && ovex != NULL)
			{
				pUser->Dispatch(Bytes, ovex);
			}
			else
			{
				// 1���� �������� ���Ŵ������ ���¿���
				// send �����͸� ������ �Ǹ�
				// recv ������� ���� ���
				if (ERROR_OPERATION_ABORTED != GetLastError()
					&& Bytes == 0)
				{
					I_User.DelUser(pUser->m_Sock);
				}
			}
		}
		else
		{
			I_LOG.T_ERROR();
		}
	}
}

WorkThread::WorkThread()
{}
WorkThread::~WorkThread()
{}