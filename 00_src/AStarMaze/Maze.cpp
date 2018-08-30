#include "Maze.h"

Maze::Maze() : m_pBoxinfo(nullptr), m_pVisited(nullptr)
{}

void Maze::CreateMaze(const int& width, const int& height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_iScreenWidth = g_rtClient.right;
	m_iScreenHeight = g_rtClient.bottom;

	m_pBoxinfo = new MazeBoxInfo*[m_iHeight];
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		m_pBoxinfo[i] = new MazeBoxInfo[m_iWidth];
	}
	m_pVisited = new bool*[m_iHeight];
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		m_pVisited[i] = new bool[m_iWidth];
		memset(m_pVisited[i], 0, sizeof(bool)*m_iWidth);
	}
	Visit(0, 0);
	delete[] m_pVisited;
}
bool Maze::getLocation(const int& x, const int& y)
{
	LONG xpos, ypos;
	xpos = x, ypos = y;
	if (x >= m_iWidth && y < m_iHeight)
	{
		xpos = 0;
		ypos = y + 1;
	}
	if (x < 0 && y > 0)
	{
		xpos = m_iWidth - 1;
		ypos = y - 1;
	}
	m_pLocation = { xpos, ypos };

}

bool Maze::CanMove(const int& x, const int& y)
{
	return CanMoveLeft(x, y) || CanMoveRight(x, y) || CanMoveTop(x, y) || CanMoveBottom(x, y);
}
bool Maze::CanMoveLeft(const int& x, const int& y)
{
	POINT pt = getLocation(x - 1, y);
	if (x > 0 && m_pVisited[y][pt.x] == false)
	{
		return true;
	}
}
bool Maze::CanMoveRight(const int& x, const int& y)
{
	if (x < m_iWidth - 1 && m_pVisited[y][x] == false)
	{
		return true;
	}
}
bool Maze::CanMoveTop(const int& x, const int& y)
{
	if (x > 0 && m_pVisited[y][x] == false)
	{
		return true;
	}
}
bool Maze::CanMoveBottom(const int& x, const int& y)
{
	if (x > 0 && m_pVisited[y][x] == false)
	{
		return true;
	}
}