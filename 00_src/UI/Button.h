#pragma once
#include "KObject.h"

class Button : public KObject
{
public:
	bool					Init();
	bool					Frame();
	bool					Render();
	bool					Release();
public:
	Button();
	virtual ~Button();
};

