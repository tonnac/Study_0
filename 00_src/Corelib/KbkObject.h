#pragma once
#include "KObject.h"
class KbkObject : public KObject
{
public:
	bool			Frame		() override;
	bool			Render		() override;
	bool			FadeOut		() override;
	bool			FadeIn		() override;
	bool			RenderScroll();
};