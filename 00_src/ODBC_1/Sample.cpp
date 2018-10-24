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
	_stprintf_s(szInCon, 256, _TEXT("FileDsn=%s\\cigarette"), L"..\\..\\data");
//	_stprintf_s(szInCon, 256, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\cigarette.mdb;"), L"..\\..\\data");

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
	SQLINTEGER Price;
	BOOL isKorean = TRUE;

	printf("이름입력: ");
	scanf_s("%s", naame, 20);
	MultiByteToWideChar(CP_ACP, 0, naame, -1, Name, sizeof(naame));

	printf("가격입력: ");
	scanf_s("%d", &Price);
	printf("국산여부: ");
	scanf_s("%d", &isKorean);
	
	wsprintf(szSQL, _T("insert into tblCigar(name, price, korean) values('%s', %d, %d)"), Name, Price, isKorean);
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
	SQLINTEGER Price;
	SQLINTEGER Korean;
	SQLLEN lName, lPrice, lKorean;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, Name, sizeof(Name), &lName);
	SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);
	sRet = SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar"), SQL_NTS);
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
bool Delete()
{
	SQLTCHAR szSQL[256] = { 0, };
	char naame[20] = { 0, };
	SQLTCHAR Name[20] = { 0, };

	printf("이름입력: ");
	scanf_s("%s", naame, 20);
	MultiByteToWideChar(CP_ACP, 0, naame, -1, Name, sizeof(naame));

	wsprintf(szSQL, _T("delete from tblCigar where name='%s'"), Name);
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
	SQLINTEGER Price;
	BOOL isKorean = TRUE;

	printf("변경할 이름입력: ");
	scanf_s("%s", befnaame, 20);
	MultiByteToWideChar(CP_ACP, 0, befnaame, -1, befName, sizeof(befnaame));


	printf("이름입력: ");
	scanf_s("%s", afnaame, 20);
	MultiByteToWideChar(CP_ACP, 0, afnaame, -1, afName, sizeof(afnaame));
	printf("가격입력: ");
	scanf_s("%d", &Price);
	printf("국산여부: ");
	scanf_s("%d", &isKorean);

	wsprintf(szSQL, _T("update tblCigar set name='%s', price=%d, korean=%d where name='%s'"), afName, Price, isKorean, befName);
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