#include <iostream>
#include <chrono>
#include <ctime>
using namespace std::chrono;

int main()
{
	time_point<steady_clock> t = steady_clock::now();
	time_t tim = system_clock::to_time_t(system_clock::now());
	char buf[256] = { 0, };
	tm pe;
	tim = system_clock::to_time_t(system_clock::now());
	localtime_s(&pe, &tim);
	strftime(buf, 256, "%I : %M : %S", &pe);
	std::cout << buf << '\n';
	steady_clock::time_point p = steady_clock::now();

	for (uint64_t i = 0; i < 18446744073709551614; ++i)
	{

	}
	
	time_point<steady_clock> l = steady_clock::now();
	
	steady_clock::duration e = l - t;
//	steady_clock::duration d = t - p;
	tim = system_clock::to_time_t(system_clock::now());
	localtime_s(&pe, &tim);
	
	strftime(buf, 256, "%I : %M : %S", &pe);
	std::cout << buf << '\n';
	std::cout << "something took " << e.count() << "nano\n";
	std::cout << "something took " << duration_cast<seconds>(e).count() << '\n';

	return 0;
}