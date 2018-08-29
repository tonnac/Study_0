#include "MazeMap.h"

MazeMap::MazeMap() : m_pMazeBoxInfo(nullptr), m_pVisited(nullptr)
{
	m_hBluePen = CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
}

void MazeMap::Create(int iWidth, int iHeight, int iScreenWidth, int iScreenHeight)
{
	m_iScreenHeight = iScreenHeight;
	m_iScreenWidth = iScreenWidth;
	m_iHeight = iHeight;
	m_iWidth = iWidth;

	m_pMazeBoxInfo = new MazeBoxInfo[m_iWidth * m_iHeight];
	m_pVisited = new bool[m_iWidth * m_iHeight];
	memset(m_pVisited, 0, sizeof(bool) * m_iHeight * m_iWidth);

	Visit(0, 0);
	delete[] m_pVisited;
	m_pVisited = nullptr;

	MakePloydPass();

	m_Wall.Init();
	m_Wall.Load(L"../../data/tile4.bmp");
	m_Road.Init();
	m_Road.Load(L"../../data/sand.bmp");

	CreateTile();
}
bool MazeMap::Render()
{
	int iOffsetHeight = g_rtClient.bottom / m_iHeight;
	int iOffsetWidth = g_rtClient.right / m_iWidth;

	HPEN oldpen = (HPEN)SelectObject(g_hOffScreenDC, m_hBluePen);

	for (int y = 0; y < m_iHeight; ++y)
	{
		for (int x = 0; x < m_iWidth; ++x)
		{
			MazeBoxInfo mbi = m_pMazeBoxInfo[y * m_iWidth + x];

			float x0 = (float)(x * iOffsetWidth);
			float y0 = (float)(y * iOffsetHeight);

			float x1 = (float)((x + 1) * iOffsetWidth);
			float y1 = (float)((y + 1) * iOffsetHeight);

			if (mbi.getLeft() == 1)
			{
				MoveToEx(g_hOffScreenDC, x0, y0, NULL);
				LineTo(g_hOffScreenDC, x0, y1);
			}
			if (mbi.getRight() == 1)
			{
				MoveToEx(g_hOffScreenDC, x1, y0, NULL);
				LineTo(g_hOffScreenDC, x1, y1);
			}
			if (mbi.getTop() == 1)
			{
				MoveToEx(g_hOffScreenDC, x0, y0, NULL);
				LineTo(g_hOffScreenDC, x1, y0);
			}
			if (mbi.getBottom() == 1)
			{
				MoveToEx(g_hOffScreenDC, x0, y1, NULL);
				LineTo(g_hOffScreenDC, x1, y1);
			}
		}
	}

	return true;
}
bool MazeMap::Release()
{
	if (m_pMazeBoxInfo)
	{
		delete[] m_pMazeBoxInfo;
		m_pMazeBoxInfo = nullptr;
	}
	m_Wall.Release();
	m_Road.Release();
	return true;
}
void MazeMap::Reset()
{
	return;
}
bool MazeMap::CreateTile()
{
	m_iMaxTileHeight = 2 * m_iHeight + 1;
	m_iMaxTileWidth = 2 * m_iWidth + 1;
	m_TileData.resize(m_iMaxTileHeight * m_iMaxTileWidth);

	m_fTileDistance.x = g_rtClient.right / m_iMaxTileWidth;
	m_fTileDistance.y = g_rtClient.bottom / m_iMaxTileHeight;

	int iTileID = 0;
	float fHalfX = m_fTileDistance.x * 0.5;
	float fHalfY = m_fTileDistance.y * 0.5;

	for (int h = 0; h < m_iMaxTileHeight; ++h)
	{
		for (int w = 0; w < m_iMaxTileWidth; ++w)
		{
			tPoint pos = { w * m_fTileDistance.x + fHalfX, h * m_fTileDistance.y + fHalfY };
			iTileID = h * m_iMaxTileWidth + w;
			m_TileData[iTileID].index = iTileID;
			m_TileData[iTileID].iType = 1;
			m_TileData[iTileID].pos = pos;
		}
	}

	for (int h = 0; h < m_iHeight; ++h)
	{
		for (int w = 0; w < m_iWidth; ++w)
		{
			int index = h * m_iWidth + w;
			int iX = w * 2 + 1;
			int iY = h * 2 + 1;
			int iTileIndex = iY * m_iMaxTileWidth + iX;
			m_TileData[iTileIndex].iType = 0;

			if (m_pMazeBoxInfo[index].getLeft() == 0)
			{
				iTileIndex += -1;
				m_TileData[iTileIndex].iType = 0;
			}
			if (m_pMazeBoxInfo[index].getRight() == 0)
			{
				iTileIndex += 1;
				m_TileData[iTileIndex].iType = 0;
			}
			if (m_pMazeBoxInfo[index].getTop() == 0)
			{
				iTileIndex = (iY - 1)*m_iMaxTileWidth + iX;
				m_TileData[iTileIndex].iType = 0;
			}
			if (m_pMazeBoxInfo[index].getBottom() == 0)
			{
				iTileIndex = (iY + 1)*m_iMaxTileWidth + iX;
				m_TileData[iTileIndex].iType = 0;
			}
		}
	}
	return true;
}
bool MazeMap::RenderTile()
{
	int iOffSetWidth = g_rtClient.right / m_iMaxTileWidth;
	int iOffSetHeight = g_rtClient.bottom / m_iMaxTileHeight;

	for (int h = 0; h < m_iMaxTileHeight; ++h)
	{
		for (int w = 0; w < m_iMaxTileWidth; ++w)
		{
			int x = w * iOffSetWidth;
			int y = h * iOffSetHeight;
			int index = h * m_iMaxTileWidth + w;
			if (m_TileData[index].iType == 0)
			{
				StretchBlt(g_hOffScreenDC, x, y, iOffSetWidth, iOffSetHeight,
					m_Road.m_pColorBitmap->m_hMemDC, 0, 0, m_Road.m_pColorBitmap->m_bmpInfo.bmWidth,
					m_Road.m_pColorBitmap->m_bmpInfo.bmHeight, SRCCOPY);
			}
			if (m_TileData[index].iType == 1)
			{
				StretchBlt(g_hOffScreenDC, x, y, iOffSetWidth, iOffSetHeight,
					m_Wall.m_pColorBitmap->m_hMemDC, 0, 0, m_Wall.m_pColorBitmap->m_bmpInfo.bmWidth,
					m_Wall.m_pColorBitmap->m_bmpInfo.bmHeight, SRCCOPY);
			}
		}
	}
	return true;
}
void MazeMap::RenderPath()
{
	return;
}

TIndex MazeMap::GetTileID(float x, float y)
{
	return { 0, 0 };
}
bool MazeMap::CanMove(int x, int y)
{
	return (CanMoveLeft(x, y) || CanMoveRight(x, y) || CanMoveTop(x, y) || CanMoveBottom(x, y));
}
bool MazeMap::CanMoveLeft(int x, int y)
{
	if (x > 0 && !m_pVisited[y * m_iWidth + x - 1])
	{
		return true;
	}
	return false;
}
bool MazeMap::CanMoveRight(int x, int y)
{
	if (x < m_iWidth - 1 && !m_pVisited[y * m_iWidth + x + 1])
	{
		return true;
	}
	return false;
}
bool MazeMap::CanMoveTop(int x, int y)
{
	if (y > 0 && !m_pVisited[(y - 1) * m_iWidth + x])
	{
		return true;
	}
	return false;
}
bool MazeMap::CanMoveBottom(int x, int y)
{
	if (y < m_iHeight - 1 && !m_pVisited[(y + 1) * m_iWidth + x])
	{
		return true;
	}
	return false;
}
void MazeMap::Visit(int x, int y)
{
	m_pVisited[y * m_iWidth + x] = true;
	
	MazeBoxInfo& mbi = m_pMazeBoxInfo[y * m_iWidth + x];

	while (CanMove(x, y))
	{
		int Dir = rand() % 4;

		switch (Dir)
		{
		case 0:
			if (CanMoveLeft(x, y))
			{
				mbi.setLeft(0);
				MazeBoxInfo &adjoinBox = m_pMazeBoxInfo[y * m_iWidth + x - 1];
				adjoinBox.setRight(0);
				Visit(x - 1, y);
			}
			break;
		case 1:
			if (CanMoveRight(x, y))
			{
				mbi.setRight(0);
				MazeBoxInfo &adjoinBox = m_pMazeBoxInfo[y * m_iWidth + x + 1];
				adjoinBox.setLeft(0);
				Visit(x + 1, y);
			}
			break;
		case 2:
			if (CanMoveTop(x, y))
			{
				mbi.setTop(0);
				MazeBoxInfo &adjoinBox = m_pMazeBoxInfo[(y - 1) * m_iWidth + x];
				adjoinBox.setBottom(0);
				Visit(x , y - 1);
			}
			break;
		case 3:
			if (CanMoveBottom(x, y))
			{
				mbi.setBottom(0);
				MazeBoxInfo &adjoinBox = m_pMazeBoxInfo[(y + 1) * m_iWidth + x];
				adjoinBox.setTop(0);
				Visit(x, y + 1);
			}
			break;
		}
	}
}

int	 MazeMap::GetPloydIndex(float fX, float fY)
{
	return 0;
}
bool MazeMap::MakePloydPass()
{
	m_dwNumNodes = m_iWidth * m_iHeight;
	m_pPloydVertex = new POINT[m_dwNumNodes];
	m_pPloydVertexArray = new WORD[m_dwNumNodes * m_dwNumNodes];
	memset(m_pPloydVertexArray, 0, sizeof(WORD) * m_dwNumNodes * m_dwNumNodes);
	m_pPloydPathList = new PloydPath[m_dwNumNodes * m_dwNumNodes];

	int iOffSetWidth = m_iScreenWidth / m_iWidth;
	int iOffSetHeight = m_iScreenHeight / m_iHeight;

	int iPloydVertexCnt = 0;
	float x0, x1, y0, y1;
	for (int y = 0; y < m_iHeight; y++)
	{
		for (int x = 0; x < m_iWidth; x++)
		{
			x0 = (float)(x * iOffSetWidth);
			y0 = (float)(y * iOffSetHeight);
			x1 = (float)((x + 1) * iOffSetWidth);
			y1 = (float)((y + 1) * iOffSetHeight);
			m_pPloydVertex[iPloydVertexCnt].x = (x1 + x0) / 2.0f;
			m_pPloydVertex[iPloydVertexCnt++].y = (y1 + y0) / 2.0f;

			int iIndex = y * m_iWidth + x;
			int iArrayIndex = iIndex * (m_iWidth*m_iHeight);
			MazeBoxInfo MazeBox = m_pMazeBoxInfo[iIndex];

			if (x == y)
			{
				m_pPloydVertexArray[iArrayIndex] = 1;
			}
			if (MazeBox.getTop() == 0)
			{
				m_pPloydVertexArray[iArrayIndex + iIndex - m_iWidth] = 1;
			}
			if (MazeBox.getBottom() == 0)
			{
				m_pPloydVertexArray[iArrayIndex + iIndex + m_iWidth] = 1;
			}
			if (MazeBox.getLeft() == 0)
			{
				m_pPloydVertexArray[iArrayIndex + iIndex - 1] = 1;
			}
			if (MazeBox.getRight() == 0)
			{
				m_pPloydVertexArray[iArrayIndex + iIndex + 1] = 1;
			}
		}
	}

	return true;
}
bool MazeMap::ComputePloydPass()
{
	return true;
}
//vector<tPoint>&	MazeMap::PloydListToTileList(DWORD dwStart, DWORD dwEnd)
//{
//
//}
