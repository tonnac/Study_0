#pragma once
#include <iostream>
using namespace std;

template <class AI>

class Point
{
private:
	AI m_A;
	AI m_B;
public:
	Point(AI _m_A, AI _m_B);
	Point operator + (const Point & data);
	Point operator = (const Point & data);
	Point& operator << (const Point & data);
	Point& operator >> (const Point & data);
	friend ostream& operator << (ostream & os, const Point&data);
};

template <class AI>
Point<AI>::Point<AI>(AI _m_A, AI _m_B)
{
	m_A = _m_A;
	m_B = _m_B;
}
template <class AI>
Point<AI> Point<AI>::operator + (const Point<AI>& data)
{
	Point temp;
	temp.m_A = m_A + data.m_A;
	temp.m_B = m_B = data.m_B;
	return temp;
}
template <class AI>
Point<AI> Point<AI>::operator = (const Point<AI>& data)
{
	Point temp;
	temp.m_A = m_A + data.m_A;
	temp.m_B = m_B = data.m_B;
	return temp;
}
template <class AI>
Point<AI>& Point<AI>::operator << (const Point<AI>& data)
{
	m_A <<= data.m_A;
	m_B<<= data.m_B;
}
template <class AI>
Point<AI>& Point<AI>::operator >> (const Point<AI>& data)
{
	m_A >>= data.m_A;
	m_B >>= data.m_B;
}
template <class AI>
ostream& operator << (ostream & os, const Point<AI>&data)
{
	os << '[' << data.m_A << ", " << data.m_B << ']' << endl;
	return os;
}