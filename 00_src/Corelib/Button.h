#pragma once
#include "KObject.h"
#include "Input.h"

enum Btn_State
{
	Btn_Normal,
	Btn_Click,
	Btn_Active,
	Btn_Hover,
	Btn_Count
};

class Button : public KObject
{
	Bitmap*					m_BtnColorBitmap[Btn_Count];
	Bitmap*					m_BtnMaskBitmap[Btn_Count];
	Bitmap*					m_BtnCurrent;
public:
	bool					Init	() override;
	bool					Frame	() override;
	bool					Render	() override;
	bool					Release	() override;
	bool					LoadFile(const TCHAR*, const TCHAR*, int iState);
public:
	Button();
	virtual ~Button();
};

