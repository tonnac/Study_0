#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

template <typename T>
void templateFunc(T Func)
{
	Func();
}

float Func1(const float f1, const float f2, const float f3)
{
	float f4 = f1 + f2 + f3;
	return f4;
}

std::function<void(void)> getLambda() {
	return []() {std::cout << "Hello World" << std::endl;};
}

struct SumFunctor : public std::unary_function<int, void>
{
	SumFunctor(int& number) : sum(number)
	{}
	void operator() (int& number)
	{
		sum += number;
	}
private:
	int & sum;
};
std::function<float(float)> pie()
{
	return [](float x)->float {return 3.14 + x;};
}
using fFunc = std::function<float(float)>;

int main(void)
{
	std::function<float(float)> pe = pie();

	std::array<int, 5> numbers = { 1,2,3,4,5 };
	int sum = 0;
	std::for_each(numbers.begin(), numbers.end(), SumFunctor(sum));
	std::cout << sum << std::endl;

	sum = 0;
	std::for_each(numbers.begin(), numbers.end(), [&sum](int& number)->int{ return sum += number;});

	auto introduce = [](std::string name) {
		std::cout << "Name is " << name << std::endl;
	};

	auto foo = []() {std::cout << "eewq" << std::endl;};

	auto fooe = getLambda();
	fooe();

	fFunc floatrn = [](float x)->float {return static_cast<float>(3.14 + x);};
	std::cout << floatrn(3.14) << std::endl;


	std::string name = "Jinsoo Heo";

	[name]() {
		std::cout << "My name is " << name << std::endl;
	}();

	float p = 0.5f;
	float p3 = 0.7f;
	auto func3 = [p, p3]()->float
	{
		return Func1(p, p3, 0.3);
	};
	std::cout << func3() << std::endl;

	std::vector<int*> l;
	int * ptr = new int;
	*ptr = 3;
	l.push_back(ptr);
	ptr = new int;
	*ptr = 5;
	l.push_back(ptr);
	ptr = new int;
	*ptr = 10;
	l.push_back(ptr);
	ptr = new int;
	*ptr = 1;
	l.push_back(ptr);

	std::sort(l.begin(), l.end(), [](int* x, int* y) {return *x < *y;});

	return 0;
}