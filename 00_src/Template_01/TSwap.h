#pragma once
#include <iostream>
using namespace std;
template <typename ZZZ>
void Swap(ZZZ &a, ZZZ& b)
{
	ZZZ temp;
	temp = a;
	a = b;
	b = temp;
}
template<>
void Swap(char*(&a), char*(&b))
{
	char * temp = NULL;
	temp = a;
	a = b;
	b = temp;
}