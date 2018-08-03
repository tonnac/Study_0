#include <iostream>

using namespace std;

class Counter
{
public:
	void Reset(void);
	void Click(void);
	int GetCount(void);
	Counter();
	~Counter();
private:
	int count;
};


int main(void)
{
	/*int counter = 0;
	counter++;
	counter++;
	cout << counter << endl;*/

	Counter ct;
	ct.Reset;
	ct.Click;
	ct.Click;
	ct.Click;
	ct.Click;
	cout << ct.GetCount();
	cout << endl;
}

void Counter::Reset(void)
{
	count = 0;
}

void Counter::Click(void)
{
	count++;
}

int Counter::GetCount(void)
{
	return count;
}

Counter::Counter()
{
	count = 0;
	cout << "Constructor" << endl;
}

Counter ::~Counter()
{
	cout << "Distructor" << endl;
}