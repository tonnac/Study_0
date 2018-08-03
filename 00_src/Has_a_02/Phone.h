#pragma once
#include "Camera.h"


class Phone
{
public:
	void CallUp(int number);
	void HangUp(void);
	void Photomail(int);
private:
	Camera camera;
};

void Phone::CallUp(int number)
{
	cout << "Call up..." << number << endl;
}

void Phone::HangUp()
{
	cout << "Hang up..." << endl;
}

void Phone::Photomail(int number)
{
	camera.Photograph();
	CallUp(number);
}