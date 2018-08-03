#include "TStudent.h"

TStudent operator + (int iValue, TStudent& data)
{
	TStudent ret;
	ret.SetSubject(data[0], data[1], data[2]);
	ret.SetTotal(data[3] + iValue);
	//data[3] += iValue;
	//data + iValue;
	return data;
}


int main()
{
	TStudent data;
	TStudent a[3];

	data.SetSubject(rand() % 100, rand() % 100, rand() % 100);
	a[0].SetSubject(rand() % 100, rand() % 100, rand() % 100);
	a[1].SetSubject(rand() % 100, rand() % 100, rand() % 100);
	a[2].SetSubject(rand() % 100, rand() % 100, rand() % 100);

	std::cout << a[0].GetTotal() << std::endl;
	std::cout << a[1].GetTotal() << std::endl;
	
	TStudent tmp = a[0];
	int itmp = a[0][0];

	/*std::cout << data[0] << " "
		<< data[1] << " "
		<< data[2] << " "
		<< data[3]
		<< std::endl;*/

	int totala = a[0].GetTotal() + a[1].GetTotal() + a[2].GetTotal();
	// +연산자 재정의
	TStudent total;
	for (int i = 0; i < 3; i++)
	{
		total += a[i];
	}

	TStudent tmp3 = total++;
	TStudent& tmp2 = ++total;

	TStudent d;
	d = 40 + d;

	total.Show();
}