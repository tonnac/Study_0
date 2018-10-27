#define _USE_MATH_DEFINES
#include <iostream>
#include <map>
#include <windows.h>
#include <cmath>

using namespace std;

#define DegreeToRadian(x) (x) / 180.0 * M_PI
#define RadianToDegree(x) (x) / M_PI * 180.0f

#define ad 1.02564
#define bd -5.12821

struct a
{
	a() : b(2), c(3)
	{}
	int b;
	int c;
};

int main()
{
	double d = atan(1 / 3.73205);
	double f = RadianToDegree(d);
	double r = 3.73205 / 1.86603;
	double dret = -bd / ad;
	double fret = ad / (ad - 1) * dret;

	double gg = fret / (fret - dret);
	double kk = -((dret * fret) / (fret - dret));
	map<int, a> pe;
	a ee;
	void * ptr = &ee.b;
	void * ptr2 = &ee;
	pe.insert(make_pair(1, ee));

	LPVOID lll = &pe[1];

	a* qwe = (a*)lll;

	return 0;
}