#pragma once

class SvrObject;

class Synchronize
{
public:
	SvrObject * m_pSvrObj;
public:
	Synchronize(SvrObject * pSvrObj);
	virtual ~Synchronize();
};