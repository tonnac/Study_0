#pragma once
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

class SQLServer
{
public:

	bool Initialize();
	void Release();

	bool SearchUser(const std::string& UserID);
	void AddUser(const std::string& UserID, const std::string& UserPW);
	void DelUser(const std::string& UserID);
	void EditUser(const std::string& befUserID, const std::string& afUserID);
	void EditPassword(const std::string& UserID, const std::string& Password);
	bool LoginUser(const std::string& UserID, const std::string& UserPW);
	void ShowDatabase();
private:
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
	}																						\
	return false;																			\
}
#endif