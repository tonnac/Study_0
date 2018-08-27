#pragma once
#include "TObject.h"
class TBkObj : public TObject
{	
public:
	bool Frame();
	bool Render();
	bool RenderScrool();
	bool FadeOut();
	bool FadeIn();
public:
	TBkObj();
	virtual ~TBkObj();
};

