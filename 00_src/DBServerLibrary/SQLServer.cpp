#include "SQLServer.h"
#include <tchar.h>

bool SQLServer::Initialize()
{
	SQLExp(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv));
	SQLExp(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER));
	SQLExp(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc));

	SQLTCHAR szInCon[256];
	SQLSMALLINT cbOutCon;
	_stprintf_s(szInCon, 256, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=192.168.0.51,1433;Network=dbmssocn;Database=DBBegin;Uid=sa;Pwd=kgca!@34;"));
	SQLTCHAR szOutCon[256] = { 0, };

	SQLExp(SQLDriverConnect(
		m_hDbc,
		NULL,
		(SQLTCHAR*)szInCon,
		_countof(szInCon),
		szOutCon,
		_countof(szOutCon),
		&cbOutCon,
		SQL_DRIVER_NOPROMPT));

	SQLExp(SQLAllocHandle(SQL_HANDLE_STMT, m_hEnv, &m_hDbc));

	return true;
}

bool SQLServer::SearchUser(const std::string& UserID)
{
	return true;
}

void SQLServer::AddUser(const std::string& UserID, const std::string& UserPW)
{

}

void SQLServer::DelUser(const std::string& UserID)
{

}

void SQLServer::EditUser(const std::string& befUserID, const std::string& afUserID)
{

}

void SQLServer::EditPassword(const std::string& UserID, const std::string& Password)
{

}

bool SQLServer::LoginUser(const std::string& UserID, const std::string& UserPW)
{
	return true;
}

void SQLServer::ShowDatabase()
{

}

void SQLServer::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}