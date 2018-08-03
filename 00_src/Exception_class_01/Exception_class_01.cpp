#include <iostream>

using namespace std;

class Exception
{
public:
	enum ExceptionType{ZERO,TOO_BIG,ODD_NUM,NEGATIVE};
	Exception(ExceptionType type);
	void message(void);

private:
	ExceptionType type;
};
Exception::Exception(ExceptionType type)
{
	this->type = type;
}
void Exception::message(void)
{
	switch (type)
	{
	case ZERO: cout << "0 <- X" << endl; break;
	case TOO_BIG: cout << "100>  <- X" << endl; break;
	case ODD_NUM: cout << "1,3,5 <-X" << endl; break;
	case NEGATIVE: cout << "0< <- X" << endl;
	}
}

void compute(int num) throw(Exception)
{
	if (num == 0)
		throw Exception(Exception::ZERO);
	else if (num > 100)
		throw Exception(Exception::TOO_BIG);
	else if (num % 2 == 1)
		throw Exception(Exception::ODD_NUM);
}
void print(int num) throw(Exception)
{
	if (num < 0)
		throw Exception(Exception::NEGATIVE);
}

int main(void)
{
	int num;
	cout << "input" << endl;
	cin >> num;
	try
	{
		compute(num);
		cout << "done" << endl;
		print(num);
		cout << "printed" << endl;
	}
	catch (Exception a)
	{
		a.message();
	}
	return 0;
}
