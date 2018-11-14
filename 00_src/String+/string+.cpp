wchar_t ID[256] = { 0, };
SQLTCHAR szSQL[256] = { 0, };

MultiByteToWideChar(CP_ACP, 0, UserID.c_str(), -1, ID, sizeof(ID));

SQLLEN lBytes;
SWORD sReturn;
SQLLEN cbRetParam = SQL_NTS;
lBytes = (SDWORD)12000;
SQLBindParameter(m_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_UNICODE_CHAR, SQL_LONGVARCHAR, lBytes, 0, ID, 0, nullptr);

_stprintf_s(szSQL, _T("{?=CALL usp_Search(?)}"));

SQLExecDirect(m_hStmt, szSQL, SQL_NTS);

SQLRETURN sRet;
while ((sRet = SQLMoreResults(m_hStmt)) != SQL_NO_DATA_FOUND);

if (sReturn != 0)
{
	SQLCloseCursor(m_hStmt);
	return false;
}

SQLCloseCursor(m_hStmt);
SQLFreeStmt(m_hStmt, SQL_UNBIND);
return true;