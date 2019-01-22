#include <iostream>
#include <random>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
	auto d = normal_distribution<double>(0.0f, 1.0f);

	auto gen = bind(normal_distribution<float>{255, 4.0}, default_random_engine{});

	for (int i = 0; i < 500; ++i) cout << gen() << endl;

	return 0;
}
