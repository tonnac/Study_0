#include "Text.h"

ostream &operator << (ostream &os, const Text &s)
{
	os << s.str << endl;
	return os;
}
istream &operator >> (istream &is, Text &s)
{
	char ch[256];
	is >> ch;
	/*Text * temp = new Text(ch);
	s = *temp;*/
	s.str = new char[strlen(ch)+1];
	strcpy_s(s.str,strlen(ch)+1, ch);
	s.len = strlen(ch);
	return is;
}

int main()
{
	//Text a("qwe");
	//Text b("zxc");
	//Text c;
	//c = a + b;
	//cout << c;
	////cout << a;
	Text t1("Text");			// 첫번째 문자열
	Text t2("Test");			// 두번째 문자열
	Text t3("Text Test");		// 첫번째와 두번째의 합
	Text t4 = t1;				// 문자열 대입
	t4 = t2;
	Text t5;
	t5 = t1 + t2;
	t4 += Text(" ") + t2;		// 문자열 이어 붙이기
	cout << "t3: " << t3 << endl;	// 문자열 출력
	cout << "t4: " << t4 << endl;	// 문자열 출력

	if (t3 == t4)				// 문자열 비교
		cout << "t3와 t4는 같습니다" << endl;

	for (int i = 0; i< t4.length(); i++)
		cout << t4[i] << " / ";	// 인덱스에 의한 접근

	cout << endl;
	return 0;
}