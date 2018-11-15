#pragma once
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <array>

class SQLServer
{
public:
	bool Initialize();
	void Release();

	bool SearchUser(const std::string& UserID);
	bool AddUser(const std::string& UserID, const std::string& UserPW);
	bool DelUser(const std::string& UserID);
	bool EditUser(const std::string& befUserID, const std::string& afUserID);
	bool EditPassword(const std::string& UserID, const std::string& Password);
	bool LoginUser(const std::string& UserID, const std::string& UserPW);
	void Logout(const std::string& UserID);
	void ShowDatabase();

private:
	void CreateText(const SQLCHAR* ID, const SQLCHAR* Password,
					const TIMESTAMP_STRUCT& Create, const TIMESTAMP_STRUCT& Login, const TIMESTAMP_STRUCT& Logout,
					SQLLEN lLogin, SQLLEN lLogout);

private:
	std::array<std::string, 5> m_Text;

	SQLHENV		 m_hEnv;
	SQLHDBC		 m_hDbc;
	SQLHSTMT	 m_hStmt;
};

#ifndef SQLExp
#define SQLExp(x)																			\
{																							\
	SQLRETURN sRet;																			\
	sRet = (x);																				\
	if(sRet != SQL_SUCCESS && sRet != SQL_SUCCESS_WITH_INFO)								\
	{																						\
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];										\
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];											\
		SQLINTEGER sqlcode;																	\
		SQLSMALLINT length;																	\
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);							\
		int iErrorCnt = 1;																	\
		while (sRet = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDbc, iErrorCnt++, sqlstate, &sqlcode,\
			buffer, sizeof(buffer), &length) != SQL_NO_DATA)								\
		{																					\
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);						\
		}																					\
		return false;																		\
	}																						\
																		\
}
#endif