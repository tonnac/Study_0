#include "SQLServer.h"
#include <tchar.h>
#include <iostream>
#include <iomanip>

using namespace std;


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
	wchar_t ID[256] = { 0, };
	SQLTCHAR szSQL[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));

	SQLLEN lBytes;
	SWORD sReturn;
	SQLLEN cbRetParam = SQL_NTS;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, ID, 0, nullptr);

	_stprintf_s(szSQL, sizeof(szSQL), _T("{?=CALL usp_Search(?)}"));

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLRETURN sRet;
	while ((sRet = SQLMoreResults(m_hStmt)) != SQL_NO_DATA_FOUND);

	if (sRet == 0)
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	SQLCloseCursor(m_hStmt);
	return true;
}

bool SQLServer::AddUser(const std::string& UserID, const std::string& UserPW)
{
	wchar_t ID[256] = { 0, };
	wchar_t Password[256] = { 0, };
	SQLTCHAR szSQL[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));
	MultiByteToWideChar(CP_ACP, 0, UserPW.c_str(), -1, Password, sizeof(Password));

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, ID, 0, nullptr);
	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, Password, 0, nullptr);

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Add(?,?)}"));

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::DelUser(const std::string& UserID)
{
	wchar_t ID[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));

	SQLTCHAR szSQL[256] = { 0, };

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Del(?)}"));

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, ID, 0, nullptr);

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

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, wbefID, 0, nullptr);
	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, waftID, 0, nullptr);

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_EditID(?,?)}"));

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

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, wID, 0, nullptr);
	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, wPassword, 0, nullptr);

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Editpass(?,?)}"));

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);

	return true;
}

bool SQLServer::LoginUser(const std::string& UserID, const std::string& UserPW)
{
	wchar_t ID[256] = { 0, };
	wchar_t Password[256] = { 0, };
	SQLTCHAR szSQL[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));
	MultiByteToWideChar(CP_ACP, 0, UserPW.c_str(), -1, Password, sizeof(Password));

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SWORD sReturn;
	SQLLEN cbRetParam = SQL_NTS;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, ID, 0, nullptr);
	SQLBindParameter(m_hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, Password, 0, nullptr);

	_stprintf_s(szSQL, sizeof(szSQL), _T("{?=CALL usp_Login(?,?)}"));

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLRETURN sRet;
	while ((sRet = SQLMoreResults(m_hStmt)) != SQL_NO_DATA_FOUND);

	if (sReturn == 0)
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	_stprintf_s(szSQL, sizeof(szSQL), _T("Update USERLIST set LOGIN=getdata() where name='%s'"), ID);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);
	return true;
}

void SQLServer::Logout(const std::string& UserID)
{
	wchar_t ID[256] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));

	SQLTCHAR szSQL[256] = { 0, };

	_stprintf_s(szSQL, sizeof(szSQL), _T("{CALL usp_Logout(?)}"));

	SQLLEN lBytes;
	lBytes = (SDWORD)12000;
	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, lBytes, 0, ID, 0, nullptr);

	SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

	SQLCloseCursor(m_hStmt);
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
	SQLBindCol(m_hStmt, 3, SQL_C_TYPE_TIMESTAMP, &CreateTime, sizeof(CreateTime), &lCr);
	SQLBindCol(m_hStmt, 4, SQL_C_TYPE_TIMESTAMP, &Login, sizeof(Login), &lLogin);
	SQLBindCol(m_hStmt, 5, SQL_C_TYPE_TIMESTAMP, &Logout, sizeof(Logout), &lLogout);

	SQLExecDirect(m_hStmt, (SQLTCHAR*)_T("SELECT * FROM dbo.USERLIST"), SQL_NTS);

	system("cls");
	cout << cout.fill('=') << cout.width(121) << '\r';
	cout.fill(' ');
	cout << setw(20) << "ID" << setw(20) << "Password"
		<< setw(20) << "Create Time" << setw(20) << "Login Date" << setw(20) << "Logout Date";
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		CreateText(ID, Password, CreateTime, Login, Logout);
		cout << setiosflags(ios::right) << setw(20) << m_Text[0] <<
				setw(20) << m_Text[1] << setw(20) << m_Text[2] <<
				setw(20) << m_Text[3] << setw(20) << m_Text[4] << endl;
	}
	cout.fill('=');cout.width(121);	cout << '\r';
	SQLCloseCursor(m_hStmt);
}

void SQLServer::CreateText(const SQLCHAR* ID, const SQLCHAR* Password,
	const TIMESTAMP_STRUCT& Create, const TIMESTAMP_STRUCT& Login, const TIMESTAMP_STRUCT& Logout)
{
	string _ID = (char*)ID;
	string _Password = (char*)Password;

	m_Text[0].assign(_ID, 0, _ID.find_first_of(' '));
	m_Text[1].assign(_Password, 0, _Password.find_first_of(' '));

	m_Text[2] = to_string(Create.hour) + "시 " + to_string(Create.minute) + "분 ";
	m_Text[3] = to_string(Login.hour) + "시 " + to_string(Login.minute) + "분 ";
	m_Text[4] = to_string(Logout.hour) + "시 " + to_string(Logout.minute) + "분 ";
}

void SQLServer::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}