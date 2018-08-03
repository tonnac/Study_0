#include "Text.h"



Text::Text(const char*s)
{
	if (s)		// NULL이 아닌 문자열로 초기화할 경우
	{
		len = (int)strlen(s);		// 문자열 길이 계산
		str = new char[len + 1];		// 문자열 길이만큼 메모리 할당
		strcpy_s(str,len+1, s);			// 문자열을 복사해서 저장
	}
	else		// NULL로 초기화할 경우
	{
		len = 0;					// 길이를 0으로 초기화
		str = NULL;				// 포인터를 NULL로 초기화
	}

}
Text::Text(const Text &s)
{
	//int i = 0;
	//while (s.str[i++] != NULL);
	//len = i;
	/**this = s;*/
	len = s.len;			// 문자열 길이 설정
	str = new char[len + 1];		// 문자열 길이만큼 메모리 할당
	strcpy_s(str,strlen(s.str)+1 ,s.str);
}
Text& Text:: operator = (const Text &s)
{
	if (str)
	{
		delete[]str;
	}
	int i = 0;
	len = s.len;
	str = new char[len+1];
	do
	{
		*(str + i) = *(s.str + i);
	}while ((*(s.str + i++)) != NULL);
	return *this;
}
Text Text:: operator+ (const Text &s)
{
	int i = 0;
	Text temp;
	temp.len = len + s.len;
	temp.str = new char[len+s.len+1];
	do
	{
		*((temp.str) + i) = *(((*this).str)+i);
	} while (*((*this).str + i++) != NULL);
	for (i = 0; i < s.len + 1; i++)
		temp.str[len + i] = s.str[i];
	return temp;
}
char& Text::operator[](int index) const
{
	int i = 0;
	for (i = 0; i <= index; i++)
	{
		if (i == index)
		{
			return str[i];
		}
	}
}
Text& Text:: operator += (const Text &s)
{
	int i = 0;
	char * temp = new char[len + s.len + 1];
	if (str)
	{	
		strcpy_s(temp, len + 1, str);
		delete[]str;
	}	
	do
	{
		temp[len + i] = s[i];
	}while (s[i++] != NULL);
	len = len + s.len + 1;
	str = temp;
	return *this;
}
bool Text::operator==(const Text &s)
{
	if (len != s.len) { return false; }
	else
	{
		for (int i = 0; i < len;i++)
		{
			if (str[i] != s[i]) { return false; }
		}
	}
	return true;
}


Text::~Text()
{
	cout << "Destructor" << endl;
	delete[]str;
}
