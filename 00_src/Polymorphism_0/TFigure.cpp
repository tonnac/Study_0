#include "TFigure.h"

void TFigure::Move(int x, int y)
{
	m_ix += x;
	m_iy += y;
}
void TFigure::Resize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}
void TFigure::Draw()
{
	std::cout << "TFigure::Draw()" << std::endl;
}

TFigure::TFigure()
{
	m_ix = 0, m_iy = 0;
	std::cout << "TFigure::TFigure()" << std::endl;
}


TFigure::~TFigure()
{
	std::cout << "TFigure::~TFigure()" << std::endl;
}
