#pragma once
#include "TObject.h"
enum Btn_State
{
	Btn_Normal,
	Btn_Click,
	Bin_Active,
	Btn_Hover,
	Btn_Count,
};
class TButton : public TObject
{
	TBitmap*   m_hBtnColorBitmap[Btn_Count];
	TBitmap*   m_hBtnMaskBitmap[Btn_Count];
	TBitmap*   m_hBtnCurrentBitmap;
public:
	bool	LoadUI(const TCHAR* pszColor,
		const TCHAR* pszMask, int iState);
	bool	Frame();
	bool	Render();
public:
	TButton();
	virtual ~TButton();
};

