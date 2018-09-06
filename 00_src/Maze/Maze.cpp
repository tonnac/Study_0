#include "Maze.h"

MazeInfo::MazeInfo() : left(1), top(1), right(1), bottom(1), _isVisit(false)
{}
int MazeInfo::getLeft()
{
	return left;
}
int MazeInfo::getTop()
{
	return top;
}
int MazeInfo::getRight()
{
	return right;
}
int MazeInfo::getBottom()
{
	return bottom;
}
bool MazeInfo::getVisit()
{
	return _isVisit;
}
void MazeInfo::setLeft(const int& Left)
{
	left = Left;
}
void MazeInfo::setTop(const int& Top)
{
	top = Top;
}
void MazeInfo::setRight(const int& Right)
{
	right = Right;
}
void MazeInfo::setBottom(const int& Bottom)
{
	bottom = Bottom;
}
void MazeInfo::setVisit(const bool& Visit)
{
	_isVisit = Visit;
}
void Maze::CreateMaze(const int& iWidth, const int& iHeight)
{
	_MazeSize._x = iWidth, _MazeSize._y = iHeight;
	std::vector<MazeInfo> mazeinfo(iWidth, MazeInfo());
	_MazeArray.assign(iHeight, mazeinfo);



}
bool Maze::CanMove(const int& x, const int& y)
{
	return CanMoveLeft(x, y) || CanMoveTop(x, y) || CanMoveRight(x, y) || CanMoveBottom(x, y);
}
bool Maze::CanMoveLeft(const int& x, const int& y)
{
	if (x > 0 && _MazeArray[y][x - 1].getVisit() == false) return true;
	return false;
}
bool Maze::CanMoveTop(const int& x, const int& y)
{
	if (y > 0 && _MazeArray[y - 1][x].getVisit() == false) return true;
	return false;
}
bool Maze::CanMoveRight(const int& x, const int& y)
{
	if (x < _MazeSize._x - 1 && _MazeArray[y][x + 1].getVisit() == false) return true;
	return false;
}
bool Maze::CanMoveBottom(const int& x, const int& y)
{
	if (y < _MazeSize._y - 1 && _MazeArray[y + 1][x].getVisit() == false) return true;
	return false;
}
void Maze::VisitVertex(const int& x, const int& y)
{
	_MazeArray[y][x].setVisit(true);

	while (CanMove(x, y))
	{
		DIR dir = static_cast<DIR>(rand() % 4);
		switch (dir)
		{
		case DIR::LEFT:

			break;
		case DIR::TOP:
			break;
		case DIR::RIGHT:
			break;
		case DIR::BOTTOM:
			break;
		}
	}
}