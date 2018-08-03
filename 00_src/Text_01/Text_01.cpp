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
	Text t1("Text");			// ù��° ���ڿ�
	Text t2("Test");			// �ι�° ���ڿ�
	Text t3("Text Test");		// ù��°�� �ι�°�� ��
	Text t4 = t1;				// ���ڿ� ����
	t4 = t2;
	Text t5;
	t5 = t1 + t2;
	t4 += Text(" ") + t2;		// ���ڿ� �̾� ���̱�
	cout << "t3: " << t3 << endl;	// ���ڿ� ���
	cout << "t4: " << t4 << endl;	// ���ڿ� ���

	if (t3 == t4)				// ���ڿ� ��
		cout << "t3�� t4�� �����ϴ�" << endl;

	for (int i = 0; i< t4.length(); i++)
		cout << t4[i] << " / ";	// �ε����� ���� ����

	cout << endl;
	return 0;
}