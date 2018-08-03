#include "TextView.h"
class Shape 
{
public:
	virtual void Draw(int x, int y, const char*pName) = 0;
};
class LineShape : public Shape 
{
	void Draw(int x, int y, const char*pName)
	{
		std::cout << pName <<" x=" << x << ", y= "<< y << std::endl;
	}
};
class ptext : public Shape, public TextView // 다중상속으로만든 Adapter
{
public:
	void Draw(int x, int y, const char*pName)
	{
		PRINT(pName);
		std::cout << " x=" << x << ", y=" << y << std::endl;
	}
public:
	ptext() {}
	~ptext() {}
};
class text : public Shape
{
public: 
	TextView m_tv;  //포함으로만든 Adapter
	void Draw(int x, int y, const char*pName)
	{
		m_tv.PRINT(pName);
		std::cout << " x=" << x << ", y=" << y << std::endl;
	}
public:
	text() {}
	~text() {}
};
//class text : public TextView
//{
//public:
//	TextView m_tv;
//public:
//	text() {}
//	~text() {}
//};

int main()
{
	//text vt;
	//vt.PRINT("qwe");

	//vt.m_tv.PRINT("qwe");

	ptext pl;
	pl.PRINT("mm");

	Shape * pe = new LineShape;
	Shape * pp = new text;
	pe->Draw(10, 20, "Line");
	pp->Draw(10, 20, "Text");

	return 0;
}