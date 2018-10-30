#include <iostream>
#include <conio.h>
using namespace std;


int main()
{
	cout.width(12); cout << "ID"; cout.width(20);cout << "PORT"; cout.width(16);cout << "IP" << endl;
	cout.fill('='); cout.width(55); cout << " " << endl;
	cout.fill(' ');

	cout.width(21); cout << "qqqqqqqqqqqqqqqqqqqq"; cout.width(12); cout << 12345; cout.width(20); cout << "192.168.0.1" << endl;
	cout.width(21); cout << "qqqqqqq"; cout.width(12); cout << 12345; cout.width(20); cout << "192.168.0.1" << endl;
	cout.width(21); cout << "qqqqasdsaqq"; cout.width(12); cout << 12345; cout.width(20); cout << "192.168.0.1" << endl;
	_getch();
	return 0;
}