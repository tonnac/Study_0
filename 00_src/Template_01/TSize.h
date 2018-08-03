#pragma once
#include <iostream>

template <typename P>
void Size(P & value)
{
	cout << "'s datatype = " << sizeof(value) << endl;
}
template<>
void Size<char*>(char *(&ch))
{
	cout << "char" << "'s length = " << strlen(ch) << endl;
}