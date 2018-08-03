#pragma once
template <class K>
class KQueue_Array
{
private:
	static const int MAX_LEN = 5;
	int m_iFront;
	int m_iRear;
	K karr[MAX_LEN];
public:
	bool put(const K & data);
	bool peek(K & data);
	void pop();
	bool empty() const;
	void show() const;
	KQueue_Array();
};

