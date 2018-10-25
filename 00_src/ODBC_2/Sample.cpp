#include <iostream>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>

SQLHENV g_hEnv;
SQLHDBC g_hDbc;
SQLHSTMT g_hStmt;


/*
	insert into tblCigar(name, price, korean) values('aaa', 3000, 1)
	_T("insert into tblCigar(name, price, korean) values('bbb', 4000, 1)");
*/
bool Add();
/*
	select ,, from table
	select ,, from table where?=?
*/
void Select();
bool Delete();
bool Update();

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
	SQLTCHAR szInCon[256];
	_stprintf_s(szInCon, 256, _TEXT("DBBegin"));
//	_stprintf_s(szInCon, 256, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\cigarette.mdb;"), L"..\\..\\data");

	SQLTCHAR szOutCon[256] = { 0, };

	//sRet = SQLDriverConnect(
	//	g_hDbc,
	//	NULL,
	//	(SQLTCHAR*)szInCon,
	//	_countof(szInCon),
	//	szOutCon,
	//	_countof(szOutCon),
	//	&cbCon,
	//	SQL_DRIVER_NOPROMPT);

	sRet = SQLConnect(g_hDbc, szInCon, SQL_NTS, (SQLTCHAR*)L"sa", SQL_NTS, (SQLTCHAR*)L"kgca!@34", SQL_NTS);

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
		return -1;
	}

	// 명령 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);
	bool bExit = false;
	while (bExit != true)
	{
		int iSelect;
		printf("1:추가 2:삭제 3:수정 9:종료 0:출력\n입력: ");
		scanf_s("%d", &iSelect);
		switch (iSelect)
		{
			case 0: Select(); break;
			case 1: Add(); break;
			case 2: Delete(); break;
			case 3: Update(); break;
			case 9:
			{
				bExit = true;
			}break;
			default:
			{
				system("cls");
				printf("잘못된 입력\n");
			}break;
		}

	}

	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
	return 0;
}

bool Add()
{
	SQLTCHAR szSQL[256] = { 0, };
	char naame[20] = { 0, };
	SQLTCHAR Name[20] = { 0, };
	char paass[20] = { 0, };
	SQLTCHAR Pass[20] = { 0, };

	printf("ID입력: ");
	scanf_s("%s", naame, 20);
	MultiByteToWideChar(CP_ACP, 0, naame, -1, Name, sizeof(naame));
	printf("패스워드입력: ");
	scanf_s("%s", paass, 20);
	MultiByteToWideChar(CP_ACP, 0, paass, -1, Pass, sizeof(paass));

	
	wsprintf(szSQL, _T("insert into USERLIST values('%s', '%s')"), Name, Pass);
	SQLRETURN sRet;
	sRet = SQLExecDirect(g_hStmt, szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}
void Select()
{
	SQLRETURN sRet;
	SQLCHAR Name[20] = { 0, };
	SQLCHAR Pass[20] = { 0, };
	SQLLEN lName, lPass;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, Name, sizeof(Name), &lName);
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, Pass, sizeof(Pass), &lPass);
	sRet = SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select * from USERLIST"), SQL_NTS);
	if (sRet != SQL_SUCCESS)
	{
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		printf("[USERID : %s] [USERPS : %s]\n", Name, Pass);
	}
	SQLCloseCursor(g_hStmt);
}
bool Delete()
{
	SQLTCHAR szSQL[256] = { 0, };
	char naame[20] = { 0, };
	SQLTCHAR Name[20] = { 0, };

	printf("ID입력: ");
	scanf_s("%s", naame, 20);
	MultiByteToWideChar(CP_ACP, 0, naame, -1, Name, sizeof(naame));

	wsprintf(szSQL, _T("delete from USERLIST where USERID='%s'"), Name);
	SQLRETURN sRet;
	sRet = SQLExecDirect(g_hStmt, szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}
bool Update()
{
	SQLTCHAR szSQL[256] = { 0, };
	char befnaame[20] = { 0, };
	SQLTCHAR befName[20] = { 0, };
	char afnaame[20] = { 0, };
	SQLTCHAR afName[20] = { 0, };

	char afpass[20] = { 0, };
	SQLTCHAR afnpass[20] = { 0, };

	printf("변경할 ID입력: ");
	scanf_s("%s", befnaame, 20);
	MultiByteToWideChar(CP_ACP, 0, befnaame, -1, befName, sizeof(befnaame));


	printf("ID입력: ");
	scanf_s("%s", afnaame, 20);
	MultiByteToWideChar(CP_ACP, 0, afnaame, -1, afName, sizeof(afnaame));
	printf("패스워드입력: ");
	scanf_s("%s", afpass, 20);
	MultiByteToWideChar(CP_ACP, 0, afpass, -1, afnpass, sizeof(afnpass));

	wsprintf(szSQL, _T("update USERLIST set USERID='%s', USERPS='%s' where USERID='%s'"), afName, afnpass, befName);
	SQLRETURN sRet;
	sRet = SQLExecDirect(g_hStmt, szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}