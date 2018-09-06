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

	VisitVertex(0, 0);

	_Wall.Init();
	_Road.Init();

	_Wall.Load(L"../../data/tile4.bmp");
	_Road.Load(L"../../data/sand.bmp");


	CreateTile();
}
bool Maze::Render()
{
	TBitmap * pRoad = _Road.m_pColorBitmap;
	TBitmap * pWall = _Wall.m_pColorBitmap;
	int xDistance = g_rtClient.right / _TileSize._x;
	int yDistance = g_rtClient.bottom / _TileSize._y;
	for (size_t y = 0; y < _TileSize._y; ++y)
	{
		for (size_t x = 0; x < _TileSize._x; ++x)
		{
			if (_TileArray[y][x]._TileType == 0)
			{
				StretchBlt(g_hOffScreenDC,
					_TileArray[y][x]._DrawPos.x,
					_TileArray[y][x]._DrawPos.y,
					xDistance, yDistance,
					pRoad->m_hMemDC,
					0, 0,
					pRoad->m_bmpInfo.bmWidth,
					pRoad->m_bmpInfo.bmHeight,
					SRCCOPY);
			}
			else
			{
				StretchBlt(g_hOffScreenDC,
					_TileArray[y][x]._DrawPos.x,
					_TileArray[y][x]._DrawPos.y,
					xDistance, yDistance,
					pWall->m_hMemDC,
					0, 0,
					pWall->m_bmpInfo.bmWidth,
					pWall->m_bmpInfo.bmHeight,
					SRCCOPY);
			}
		}
	}
	return true;
}
MazeArray Maze::getMazeArray()
{
	return _MazeArray;
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
		{
			if (CanMoveLeft(x, y))
			{
				_MazeArray[y][x].setLeft(0);
				_MazeArray[y][x - 1].setRight(0);
				VisitVertex(x - 1, y);
			}
			break;
		}
		case DIR::TOP:
		{
			if (CanMoveTop(x, y))
			{
				_MazeArray[y][x].setTop(0);
				_MazeArray[y - 1][x].setBottom(0);
				VisitVertex(x, y - 1);
			}
			break;
		}
		case DIR::RIGHT:
		{
			if (CanMoveRight(x, y))
			{
				_MazeArray[y][x].setRight(0);
				_MazeArray[y][x + 1].setLeft(0);
				VisitVertex(x + 1, y);
			}
			break;
		}
		case DIR::BOTTOM:
		{
			if (CanMoveBottom(x, y))
			{
				_MazeArray[y][x].setBottom(0);
				_MazeArray[y + 1][x].setTop(0);
				VisitVertex(x, y + 1);
			}
			break;
		}
		}
	}
}
void Maze::CreateTile()
{
	_TileSize = _MazeSize * 2;
	_TileSize += 1;
	std::vector<MazeTile> tile(_TileSize._x, MazeTile());
	_TileArray.assign(_TileSize._y, tile);

	int iOffSetWidth = g_rtClient.right / _TileSize._x;
	int iOffSetHeight = g_rtClient.bottom / _TileSize._y;

	int iHalfX = iOffSetWidth / 2;
	int iHalfY = iOffSetHeight / 2;

	for (size_t y = 0; y < _MazeSize._y; ++y)
	{
		for (size_t x = 0; x < _MazeSize._x; ++x)
		{
			int tileX = x * 2 + 1;
			int tileY = y * 2 + 1;
			_TileArray[tileY][tileX]._TileType = 0;
			if (_MazeArray[y][x].getLeft() == 0)
			{
				_TileArray[tileY][tileX - 1]._TileType = 0;
			}
			if (_MazeArray[y][x].getTop() == 0)
			{
				_TileArray[tileY - 1][tileX]._TileType = 0;
			}
			if (_MazeArray[y][x].getRight() == 0)
			{
				_TileArray[tileY][tileX + 1]._TileType = 0;
			}
			if (_MazeArray[y][x].getBottom() == 0)
			{
				_TileArray[tileY + 1][tileX]._TileType = 0;
			}
		}
	}
	for (size_t y = 0; y < _TileSize._y; ++y)
	{
		for (size_t x = 0; x < _TileSize._x; ++x)
		{
			_TileArray[y][x]._DrawPos = { static_cast<float>(x * iOffSetWidth), static_cast<float>(y * iOffSetHeight) };
			_TileArray[y][x]._CenterPos = { static_cast<float>(x * iOffSetWidth + iHalfX), 
				static_cast<float>(y * iOffSetHeight + iHalfY) };
		}
	}
}