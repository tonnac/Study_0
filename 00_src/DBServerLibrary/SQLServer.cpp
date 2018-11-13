#include "SQLServer.h"
#include <tchar.h>
#include <iostream>

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

	SQLExp(SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt));

	return true;
}

bool SQLServer::SearchUser(const std::string& UserID)
{
	return true;
}

bool SQLServer::AddUser(const std::string& UserID, const std::string& UserPW)
{
	wchar_t ID[256] = { 0, };
	wchar_t Password[256] = { 0, };
	SQLTCHAR szSQL[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));
	MultiByteToWideChar(CP_ACP, 0, UserPW.c_str(), -1, Password, sizeof(Password));

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Add('%s', '%s')"), ID, Password);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::DelUser(const std::string& UserID)
{
	wchar_t ID[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));

	SQLTCHAR szSQL[256] = { 0, };

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Del('%s')"), ID);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::EditUser(const std::string& befUserID, const std::string& afUserID)
{
	wchar_t wbefID[256] = { 0, };
	wchar_t waftID[256] = { 0, };
	
	MultiByteToWideChar(CP_ACP, 0, befUserID.c_str(), -1, wbefID, sizeof(wbefID));
	MultiByteToWideChar(CP_ACP, 0, afUserID.c_str(), -1, waftID, sizeof(waftID));

	SQLTCHAR szSQL[256] = { 0, };

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_EditID('%s', '%s')"), wbefID, waftID);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::EditPassword(const std::string& UserID, const std::string& Password)
{
	wchar_t wID[256] = { 0, };
	wchar_t wPassword[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, wID, sizeof(wID));
	MultiByteToWideChar(CP_ACP, 0, Password.c_str(), -1, wPassword, sizeof(wPassword));

	SQLTCHAR szSQL[256] = { 0, };

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_EditID('%s', '%s')"), wID, wPassword);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::LoginUser(const std::string& UserID, const std::string& UserPW)
{
	return true;
}

void SQLServer::ShowDatabase()
{
	SQLCHAR ID[20] = { 0, };
	SQLCHAR Password[20] = { 0, };
	SQLCHAR IP[20] = { 0, };

	TIMESTAMP_STRUCT CreateTime;
	TIMESTAMP_STRUCT Login;
	TIMESTAMP_STRUCT Logout;

	SQLLEN lID, lPassword, lLogin, lLogout, lIP, lCr;
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), &lID);
	SQLBindCol(m_hStmt, 2, SQL_C_CHAR, Password, sizeof(Password), &lPassword);
	SQLBindCol(m_hStmt, 3, SQL_C_CHAR, IP, sizeof(IP), &lIP);
	SQLBindCol(m_hStmt, 4, SQL_C_TYPE_TIMESTAMP, &CreateTime, sizeof(CreateTime), &lCr);
	SQLBindCol(m_hStmt, 5, SQL_C_TYPE_TIMESTAMP, &Login, sizeof(Login), &lLogin);
	SQLBindCol(m_hStmt, 6, SQL_C_TYPE_TIMESTAMP, &Logout, sizeof(Logout), &lLogout);

	SQLExecDirect(m_hStmt, (SQLTCHAR*)_T("SELECT * FROM dbo.USERLIST"), SQL_NTS);

	system("cls");
	_tprintf(_T("================================================================\n"));
	_tprintf(_T("ID\tPassword\tCreated IP\tCreate Time\tLogin Date\tLogout Date\n"));
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{

//		sprintf_s(buf, sizeof(buf), "%s%s%s%d½Ã%dºÐ", ID, Password, IP, CreateTime.hour, CreateTime.minute);
//		printf(buf);
	}
	_tprintf(_T("================================================================"));
	SQLCloseCursor(m_hStmt);
}

void SQLServer::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}