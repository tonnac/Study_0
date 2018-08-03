#pragma once
#include "Camera.h"


class Phone
{
public:
	void CallUp(int number);
	void HangUp(void);
};

void Phone::CallUp(int number)
{
	cout << "Call up..." << number << endl;
}

void Phone::HangUp()
{
	cout << "Hang up..." << endl;
}