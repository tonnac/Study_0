#include "h2.h"

struct D
{
	int a;
	int b;
	int c;
};

template<class X>
class A
{
public:
	A<X>() {};

	void foo()
	{
		int k = 5;
	}

public:
	int a;
	int b;
	D d;
};

template<>
class A<int>
{
public:
	A() {};

	void foo()
	{
		int j = 5;
	}
public:
	int a;
	int b;
	D d;
};

template<class X>
class B : public A<X>
{
public:
	void foo()
	{
		A<X>::a = 5;
		A<X>::b = 3;
		D& e = A<X>::d;
		e.a = 1;
		e.b = 2;
		e.c = 3;
	}
};

template<>
class B<int> : public A<int>
{
public:
	void foo()
	{
		D& e = A<int>::d;
		e.a = 1;
		e.b = 2;
		e.c = 3;
	}
};

class C : public B<int>
{

};


template <typename T>
class D
{
public:
	int a;
};

template <>
class D<int>
{
public:
	int a;
};

int main()
{
	C e;
	e.foo();
	
	A<int> a;
	a.foo();

	B<int> b;
	b.foo();

	B<char> c;
	c.foo();


}