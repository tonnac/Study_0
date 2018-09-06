#include "Maze.h"

Maze::Maze() : m_pBoxinfo(nullptr), m_pVisited(nullptr), m_pPloydPath(nullptr)
{
	m_hBluePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	m_hRedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
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
		delete[] m_pTileSet;
	}
	if (m_pPloydPath)
	{
		for (size_t i = 0; i < m_iHeight * m_iWidth; ++i)
		{
			delete[] m_pPloydPath[i];
		}
		delete[] m_pPloydPath;
	}
	m_pBoxinfo = nullptr;
	m_pTileSet = nullptr;
	m_pPloydPath = nullptr;
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

	MakeGraphTable();
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
			m_pTileSet[i][j].m_CenterPos = { (xTileDistance * j) + (xTileDistance / 2), 
				(yTileDistance * i) + (yTileDistance / 2) };
		}
	}

}
Nodeindex Maze::getTargetIndex(const int& x, const int& y)
{
	int iOffSetWidth = g_rtClient.right / m_iWidth;
	int iOffSetHeight = g_rtClient.bottom / m_iHeight;

	return { x / iOffSetWidth, y / iOffSetHeight };
}
void Maze::SelectPath(const Nodeindex& nIndex)
{
	m_CurrentPath = m_pPloydPath[0][nIndex._y * m_iWidth + nIndex._x];
}
bool Maze::Reset()
{
	int iScreenWidth = g_rtClient.right - g_rtClient.left;
	int iScreenHeight = g_rtClient.bottom - g_rtClient.top;
	if (iScreenWidth == m_iScreenWidth && m_iScreenHeight == iScreenHeight)
	{
		return false;
	}
	m_iScreenHeight = iScreenHeight;
	m_iScreenWidth = iScreenWidth;

	FLOAT iOffSetWidth = static_cast<FLOAT>(m_iScreenWidth) / m_iMaxTileWidth;
	FLOAT iOffSetHeight = static_cast<FLOAT>(m_iScreenHeight) / m_iMaxTileHeight;

	for (size_t i = 0; i < m_iMaxTileHeight; ++i)
	{
		for (size_t j = 0; j < m_iMaxTileWidth; ++j)
		{
			m_pTileSet[i][j].m_point = { iOffSetWidth * j , iOffSetHeight * i };
			m_pTileSet[i][j].m_CenterPos = { (iOffSetWidth * j) + (iOffSetWidth / 2),
				(iOffSetHeight * i) + (iOffSetHeight / 2) };
		}
	}
	return true;
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

			float x1 = m_pTileSet[y * 2][x * 2].m_CenterPos.x;
			float y1 = m_pTileSet[y * 2][x * 2].m_CenterPos.y;
			
			float x2 = m_pTileSet[y * 2 + 2][x * 2 + 2].m_CenterPos.x;
			float y2 = m_pTileSet[y * 2 + 2][x * 2 + 2].m_CenterPos.y;

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
bool Maze::RenderPath()
{
	HPEN oldpen = static_cast<HPEN>(SelectObject(g_hOffScreenDC, m_hRedPen));
	Nodeindex vStart(1, 1);
	for (auto iter : m_CurrentPath.m_pPloydList)
	{
		Nodeindex vTarget = iter * 2;
		vTarget += 1;
		MoveToEx(g_hOffScreenDC, 
			m_pTileSet[vStart._y][vStart._x].m_CenterPos.x, 
			m_pTileSet[vStart._y][vStart._x].m_CenterPos.y, NULL);
		LineTo(g_hOffScreenDC, 
			m_pTileSet[vTarget._y][vTarget._x].m_CenterPos.x,
			m_pTileSet[vTarget._y][vTarget._x].m_CenterPos.y);
		vStart = vTarget;
	}
	SelectObject(g_hOffScreenDC, oldpen);
	return true;
}
bool Maze::RenderPath(const bool& ep)
{
	HPEN OldPen = (HPEN)SelectObject(g_hOffScreenDC, m_hRedPen);
	Nodeindex vStart = { 1,1 };
	for(auto iter : m_PathList)
	{
		Nodeindex vTarget = iter;
		MoveToEx(g_hOffScreenDC, 
			m_pTileSet[vStart._y][vStart._x].m_CenterPos.x, 
			m_pTileSet[vStart._y][vStart._x].m_CenterPos.y, NULL);
		LineTo(g_hOffScreenDC, 
			m_pTileSet[vTarget._y][vTarget._x].m_CenterPos.x, 
			m_pTileSet[vTarget._y][vTarget._x].m_CenterPos.y);
		vStart = vTarget;
	}
	SelectObject(g_hOffScreenDC, OldPen);
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
					RoadBitmap->m_hMemDC, 0, 0, 
					RoadBitmap->m_bmpInfo.bmWidth,
					RoadBitmap->m_bmpInfo.bmHeight, SRCCOPY);
			}
			else
			{
				StretchBlt(g_hOffScreenDC, x, y,
					static_cast<int>(xTileDistance),
					static_cast<int>(yTileDistance),
					WallBitmap->m_hMemDC, 0, 0,
					WallBitmap->m_bmpInfo.bmWidth,
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
void Maze::MakeGraphTable()
{
	m_pPloydPath = new PloydPathNode*[m_iWidth * m_iHeight];
	for (size_t i = 0; i < m_iHeight * m_iWidth; ++i)
	{
		m_pPloydPath[i] = new PloydPathNode[m_iWidth * m_iHeight];
	}
	int k = 0;
	for (size_t i = 0; i < m_iHeight; ++i)
	{
		for (size_t j = 0; j < m_iWidth; ++j)
		{
			MazeBoxInfo mbi = m_pBoxinfo[i][j];
			if (mbi.getLeft() == 1)
			{
				m_pPloydPath[k][k - 1].m_iWeight = 1;
				m_pPloydPath[k][k - 1].m_pPloydList.push_back(Nodeindex(j - 1, i));
			}
			if (mbi.getRight() == 1)
			{
				m_pPloydPath[k][k + 1].m_iWeight = 1;
				m_pPloydPath[k][k + 1].m_pPloydList.push_back(Nodeindex(j + 1, i));
			}
			if (mbi.getTop() == 1)
			{
				m_pPloydPath[k][k - m_iWidth].m_iWeight = 1;
				m_pPloydPath[k][k - m_iWidth].m_pPloydList.push_back(Nodeindex(j, i - 1));
			}
			if (mbi.getBottom() == 1)
			{
				m_pPloydPath[k][k + m_iWidth].m_iWeight = 1;
				m_pPloydPath[k][k + m_iWidth].m_pPloydList.push_back(Nodeindex(j, i + 1));
			}
			++k;
		}
	}
	CreatePloydPath();
}
void Maze::CreatePloydPath()
{
	for (size_t i = 0; i < m_iHeight * m_iWidth; ++i)
	{
		for (size_t j = 0; j < m_iHeight * m_iWidth; ++j)
		{
			if (i != j && m_pPloydPath[i][j].m_iWeight == 0)
			{
				m_pPloydPath[i][j].m_iWeight = INF;
			}
		}
	}

	for (size_t k = 0; k < m_iHeight * m_iWidth; ++k)
	{
		for (size_t i = 0; i < m_iHeight * m_iWidth; ++i)
		{
			for (size_t j = 0; j < m_iHeight * m_iWidth; ++j)
			{
				int NewWeight = m_pPloydPath[i][k].m_iWeight + m_pPloydPath[k][j].m_iWeight;
				if (NewWeight < m_pPloydPath[i][j].m_iWeight)
				{
					m_pPloydPath[i][j].m_iWeight = NewWeight;

					m_pPloydPath[i][j].m_pPloydList.assign(
						m_pPloydPath[i][k].m_pPloydList.begin(),
						m_pPloydPath[i][k].m_pPloydList.end()
					);
					m_pPloydPath[i][j].m_pPloydList.insert(
						m_pPloydPath[i][j].m_pPloydList.end(),
						m_pPloydPath[k][j].m_pPloydList.begin(),
						m_pPloydPath[k][j].m_pPloydList.end()
					);
				}
			}
		}
	}
}
int Maze::getMaxTileWidth()
{
	return m_iMaxTileWidth;
}
int Maze::getMaxTileHeight()
{
	return m_iMaxTileHeight;
}