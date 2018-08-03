#pragma once

#include <iostream>

using namespace std;

class Camera
{
public:
	void Photograph(void);
	void Zoom(int);
};

void Camera::Photograph()
{
	cout << "Take a photo..." << endl;
}

void Camera::Zoom(int zoom)
{
	cout << "Zoom..." << zoom << endl;
}