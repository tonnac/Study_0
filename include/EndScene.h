#pragma once
#include "Scene.h"
class EndScene : public Scene
{
public:
	Button					m_btnStart;
public:
	virtual	bool			Init() override;
	virtual	bool			Frame() override;
	virtual	bool			Render() override;
	virtual bool			Release() override;
	virtual bool			Reset() { return true; }
	//	virtual bool			isDead();
public:
	EndScene();
	virtual ~EndScene();
};

