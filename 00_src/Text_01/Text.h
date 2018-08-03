#pragma once
#include <iostream>
#include <conio.h>
using namespace std;


class Text
{
public:
	Text(const char *s = NULL);
	Text(const Text &s);
	~Text();
	size_t length() const { return len; }
	Text & operator = (const Text &s);
	char &operator[](int index) const;
	Text & operator += (const Text &s);
	Text operator+ (const Text &s);
	bool operator==(const Text &s);
	friend ostream &operator << (ostream &os, const Text &s);
	friend istream &operator >> (istream &is, Text &s);
private:
	char *str;
	size_t len;
};

