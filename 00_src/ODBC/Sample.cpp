#include <iostream>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>

SQLHENV g_hEnv;
SQLHDBC g_hDbc;
SQLHSTMT g_hStmt;

void Select()
{
	SQLRETURN sRet;
	SQLCHAR Name[20] = { 0, };
	SQLINTEGER Price;
	SQLINTEGER Korean;
	SQLLEN lName, lPrice, lKorean;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, Name, sizeof(Name), &lName);
	SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);
	sRet = SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar where name='this'"), SQL_NTS);
	if (sRet != SQL_SUCCESS)
	{
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		printf("[Name : %10s] [Price : %4d] [Korean : %3s]\n", Name, Price, (Korean == 1) ? "Yes" : "No");
	}
	SQLCloseCursor(g_hStmt);
}

int main(void)
{
	SQLRETURN sRet;
	// 환경 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv);
	if (sRet != SQL_SUCCESS)
	{
		return -1;
	}
	sRet = SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (sRet != SQL_SUCCESS)
	{
		return -1;
	}
	// 연결 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc);
	SQLTCHAR szInCon[256] = { 0, };
	_stprintf_s(szInCon, 256, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\cigarette.mdb;"), L"..\\..\\data");

	SQLTCHAR szOutCon[256] = { 0, };
	SQLSMALLINT cbCon;

	sRet = SQLDriverConnect(
		g_hDbc,
		NULL,
		(SQLTCHAR*)szInCon,
		_countof(szInCon),
		szOutCon,
		_countof(szOutCon),
		&cbCon,
		SQL_DRIVER_NOPROMPT);

	if ((sRet != SQL_SUCCESS) && (sRet != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;
		// 단순한 에러
	//	SQLError(g_hEnv, g_hDbc, g_Stmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

		// 모든 에러 나열됨.
		int iErrorCnt = 1;
		while (sRet = SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc, iErrorCnt++, sqlstate, &sqlcode,
			buffer, sizeof(buffer), &length) != SQL_NO_DATA)
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return FALSE;
	}

	// 명령 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);
	while (1)
	{
		int iSelect;
		scanf_s("%d", &iSelect);
		switch (iSelect)
		{
		case 0: Select(); break;
		case 1: break;
		case 2: break;
		case 3: break;
		default:
			break;
		}

	}

	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
	return 0;
}