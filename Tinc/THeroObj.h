#pragma once
#include "TObject.h"
class THeroObj : public TObject
{
public:
	bool m_bFadeState;
public:
	virtual bool	Render() override;
	virtual bool    FadeOut() override;
	virtual bool    FadeIn() override;
public:
	THeroObj();
	virtual ~THeroObj();
};

