#pragma once

template<class K>
class Stack
{
public:
	void push(K data);
	K pop();
	bool empty();
	void show() const;
	K peek();
	Stack();
	int getTop() const { return m_iTop; }
	virtual ~Stack();
private:
	static const int MAX_LEN = 7;
	int m_iTop;
	K stcarr[MAX_LEN];
};