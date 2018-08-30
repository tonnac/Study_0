#include "Maze.h"

Maze::Maze() : m_pBoxinfo(nullptr), m_pVisited(nullptr)
{
	m_hBluePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
}
Maze::~Maze()
{
	if (m_pBoxinfo)
	{
		for (size_t i = 0; i < m_iHeight; ++i)
		{
			delete[] m_pBoxinfo[i];
		}
		delete[] m_pBoxinfo;
	}
	if (m_pTileSet)
	{
		for (size_t i = 0; i < m_iMaxTileHeight; ++i)
		{
			delete[] m_pTileSet[i];
		}
		delete m_pTileSet;
	}
	m_pBoxinfo = nullptr;
	m_pTileSet = nullptr;
	DeleteObject(m_hBluePen);
}
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
		memset(m_pBoxinfo[i], 0, sizeof(MazeBoxInfo)* m_iWidth);
	}
	m_pVisited = new bool*[m_iHeight];
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		m_pVisited[i] = new bool[m_iWidth];
		memset(m_pVisited[i], 0, sizeof(bool)*m_iWidth);
	}
	VisitVertex(0, 0);
	delete[] m_pVisited;
	m_pVisited = nullptr;

	m_Wall.Load(L"../../data/tile4.bmp");
	m_Wall.Init();

	m_Road.Load(L"../../data/sand.bmp");
	m_Road.Init();

	CreatePloydPath();

	CreateTile();
}
void Maze::CreateTile()
{
	m_iMaxTileHeight = 2 * m_iHeight + 1;
	m_iMaxTileWidth = 2 * m_iWidth + 1;

	FLOAT xTileDistance, yTileDistance;

	xTileDistance = static_cast<FLOAT>(g_rtClient.right) / m_iMaxTileWidth;
	yTileDistance = static_cast<FLOAT>(g_rtClient.bottom) / m_iMaxTileHeight;

	m_pTileSet = new Tile*[m_iMaxTileHeight];
	for (size_t i = 0; i < m_iMaxTileHeight; ++i)
	{
		m_pTileSet[i] = new Tile[m_iMaxTileWidth];
		memset(m_pTileSet[i], 0, sizeof(Tile) * m_iMaxTileWidth);
	}
	
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		for (size_t j = 0; j < m_iWidth; ++j)
		{
			MazeBoxInfo mbi = m_pBoxinfo[i][j];
			size_t x = j * 2 + 1;
			size_t y = i * 2 + 1;
			if (mbi.getLeft() == 1)
			{
				m_pTileSet[y][x].m_iType = 1;
				m_pTileSet[y][x - 1].m_iType = 1;
			}
			if (mbi.getRight() == 1)
			{
				m_pTileSet[y][x].m_iType = 1;
				m_pTileSet[y][x + 1].m_iType = 1;
			}
			if (mbi.getTop() == 1)
			{
				m_pTileSet[y][x].m_iType = 1;
				m_pTileSet[y - 1][x].m_iType = 1;
			}
			if (mbi.getBottom() == 1)
			{
				m_pTileSet[y][x].m_iType = 1;
				m_pTileSet[y + 1][x].m_iType = 1;
			}
		}
	}

	for (size_t i = 0; i < m_iMaxTileHeight; ++i)
	{
		for (size_t j = 0; j < m_iMaxTileWidth; ++j)
		{
			m_pTileSet[i][j].m_point = { xTileDistance * j , yTileDistance * i };
		}
	}

}
bool Maze::Render()
{
	int iOffSetHeight = g_rtClient.bottom / m_iHeight;
	int iOffSetWidth = g_rtClient.right / m_iWidth;

	HPEN oldpen = static_cast<HPEN>(SelectObject(g_hOffScreenDC, m_hBluePen));

	for (size_t y = 0; y < m_iHeight; ++y)
	{
		for (size_t x = 0; x < m_iWidth; ++x)
		{
			MazeBoxInfo mbi = m_pBoxinfo[y][x];

			float x1 = static_cast<float>(x * iOffSetWidth);
			float y1 = static_cast<float>(y * iOffSetHeight);
			
			float x2 = static_cast<float>((x + 1)* iOffSetWidth);
			float y2 = static_cast<float>((y + 1)* iOffSetHeight);

			if (mbi.getLeft() == 0)
			{
				MoveToEx(g_hOffScreenDC, x1, y1, NULL);
				LineTo(g_hOffScreenDC, x1, y2);
			}
			if (mbi.getRight() == 0)
			{
				MoveToEx(g_hOffScreenDC, x2, y1, NULL);
				LineTo(g_hOffScreenDC, x2, y2);
			}
			if (mbi.getTop() == 0)
			{
				MoveToEx(g_hOffScreenDC, x1, y1, NULL);
				LineTo(g_hOffScreenDC, x2, y1);
			}
			if (mbi.getBottom() == 0)
			{
				MoveToEx(g_hOffScreenDC, x1, y2, NULL);
				LineTo(g_hOffScreenDC, x2, y2);
			}
		}
	}
	SelectObject(g_hOffScreenDC, oldpen);
	return true;
}
bool Maze::RenderTile()
{
	FLOAT xTileDistance = static_cast<float>(g_rtClient.right) / m_iMaxTileWidth;
	FLOAT yTileDistance = static_cast<float>(g_rtClient.bottom) / m_iMaxTileHeight;

	TBitmap * RoadBitmap = m_Road.m_pColorBitmap;
	TBitmap * WallBitmap = m_Wall.m_pColorBitmap;

	for (size_t i = 0; i < m_iMaxTileHeight; ++i)
	{
		for (size_t j = 0; j < m_iMaxTileWidth; ++j)
		{
			int x = static_cast<int>(m_pTileSet[i][j].m_point.x);
			int y = static_cast<int>(m_pTileSet[i][j].m_point.y);
			if (m_pTileSet[i][j].m_iType == 1)
			{
				StretchBlt(g_hOffScreenDC, x, y,
					static_cast<int>(xTileDistance),
					static_cast<int>(yTileDistance),
					RoadBitmap->m_hMemDC, 0, 0, RoadBitmap->m_bmpInfo.bmWidth,
					RoadBitmap->m_bmpInfo.bmHeight, SRCCOPY);
			}
			else
			{
				StretchBlt(g_hOffScreenDC, x, y,
					static_cast<int>(xTileDistance),
					static_cast<int>(yTileDistance),
					WallBitmap->m_hMemDC, 0, 0, WallBitmap->m_bmpInfo.bmWidth,
					WallBitmap->m_bmpInfo.bmHeight, SRCCOPY);
			}
		}
	}

	return true;
}
void Maze::VisitVertex(const int& x, const int& y)
{
	m_pVisited[y][x] = true;
	while (CanMove(x, y))
	{
		Dir eDir = static_cast<Dir>(rand() % 4);
		switch(eDir)
		{
		case Dir::LEFT:
			if (CanMoveLeft(x, y))
			{
				m_pBoxinfo[y][x].setLeft(1);
				m_pBoxinfo[y][x - 1].setRight(1);
				VisitVertex(x - 1, y);
			}
			break;
		case Dir::RIGHT:
			if (CanMoveRight(x, y))
			{
				m_pBoxinfo[y][x].setRight(1);
				m_pBoxinfo[y][x + 1].setLeft(1);
				VisitVertex(x + 1, y);
			}
			break;
		case Dir::TOP:
			if (CanMoveTop(x, y))
			{
				m_pBoxinfo[y][x].setTop(1);
				m_pBoxinfo[y - 1][x].setBottom(1);
				VisitVertex(x, y - 1);
			}
			break;
		case Dir::BOTTOM:
			if (CanMoveBottom(x, y))
			{
				m_pBoxinfo[y][x].setBottom(1);
				m_pBoxinfo[y + 1][x].setTop(1);
				VisitVertex(x, y + 1);
			}
			break;
		}
	}
}

bool Maze::CanMove(const int& x, const int& y)
{
	return CanMoveLeft(x, y) || CanMoveRight(x, y) || CanMoveTop(x, y) || CanMoveBottom(x, y);
}
bool Maze::CanMoveLeft(const int& x, const int& y)
{
	if (x > 0 && m_pVisited[y][x - 1] == false)
	{
		return true;
	}
	return false;
}
bool Maze::CanMoveRight(const int& x, const int& y)
{
	if (x < m_iWidth - 1 && m_pVisited[y][x + 1] == false)
	{
		return true;
	}
	return false;
}
bool Maze::CanMoveTop(const int& x, const int& y)
{
	if (y > 0 && m_pVisited[y - 1][x] == false)
	{
		return true;
	}
	return false;
}
bool Maze::CanMoveBottom(const int& x, const int& y)
{
	if (y < m_iHeight - 1 && m_pVisited[y + 1][x] == false)
	{
		return true;
	}
	return false;
}
void Maze::CreatePloydPath()
{
	int ** GraphTable = nullptr;
	GraphTable = new int*[m_iHeight * m_iWidth];
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		GraphTable[i] = new int[m_iWidth * m_iHeight];
		memset(GraphTable[i], 0, sizeof(int)* m_iWidth * m_iHeight);
	}

	for (size_t i = 0; i < m_iHeight; ++i)
	{
		for (size_t j = 0; j < m_iWidth; ++j)
		{
			if (i == j)
			{
				GraphTable[i][j] = 0;
				continue;
			}
			MazeBoxInfo mbi = m_pBoxinfo[i][j];
			if (mbi.getLeft() == 1)
			{
				GraphTable[i][j - 1] = 1;
			}
			if (mbi.getRight() == 1)
			{
				GraphTable[i][j + 1] = 1;
			}
			if (mbi.getTop() == 1)
			{
				GraphTable[i - 1][j] = 1;
			}
			if (mbi.getBottom() == 1)
			{
				GraphTable[i + 1][j] = 1;
			}
		}
	}

}