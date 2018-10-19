#pragma once
class SvrObject
{
public:
	CRITICAL_SECTION m_cs;
public:
	SvrObject();
	virtual ~SvrObject();
};