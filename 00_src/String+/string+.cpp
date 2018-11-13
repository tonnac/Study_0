#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;


int main()
{
	TIMESTAMP_STRUCT time;
	time.hour = 13;
	time.minute = 59;

	string m_Text;
	m_Text = to_string(time.hour) + "½Ã " + to_string(time.minute) + "ºÐ ";

	cout << m_Text << endl;

	SQLCHAR buf[10][20];
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (j == 19)
			{
				buf[i][j] = 0;
				continue;
			}
			if (j > 8)
			{
				buf[i][j] = ' ';
				continue;
			}
			buf[i][j] = 65 + i;
		}
	}
	string ll = (char*)buf[0];
	int sz = ll.find(' ');
	string mm(ll, 0, ll.find_first_of(' '));

	int p = (int)mm.find(' ');

//	string pp = buf[0];

	cout << cout.fill('=') << cout.width(121) << '\r';
	cout.fill(' ');

	static int qp = 0;
	cout << setw(20) << "ID" << setw(20) << "Password"
		<< setw(20) << "Created IP" << setw(20) << "Create Time"
		<< setw(20) << "Login Date" << setw(20) << "Logout Date";

	while (qp < 5)
	{

		string copybuf = (char*)buf[0];
		copybuf.assign(copybuf, 0, copybuf.find_first_of(' '));

		string copybuf1 = (char*)buf[1];
		copybuf1.assign(copybuf1, 0, copybuf1.find_first_of(' '));

		SQLCHAR ip[] = "192.168.0.101";

		cout << setiosflags(ios::right) << setw(20) << copybuf << setw(20) << copybuf1 << setw(20) << (char*)ip << setw(20) << m_Text << setw(20) << m_Text << setw(20) << m_Text;
		//	setw(20); cout << buf[0]; setw(20); cout << buf[1];
		++qp;
	}
	cout.fill('=');cout.width(121);	cout << '\r';
	cout.fill(' ');
	return 0;
}