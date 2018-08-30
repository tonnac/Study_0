#pragma once
#include "TStd.h"
#include "TObject.h"
#include <bitset>

#define INF 1000000

struct PloydPath
{
	DWORD					m_dwCost;
	std::vector<DWORD>		m_VertexList;
};

struct Tile
{
	int index;
	int iType;
	tPoint pos;
};

using TileVec = std::vector<Tile>;

struct MazeBoxInfo
{
	MazeBoxInfo() : left(1), right(1), top(1), bottom(1)
	{}

	void setLeft	(const int& value) { left = value; }
	void setRight	(const int& value) { right = value; }
	void setTop		(const int& value) { top = value; }
	void setBottom	(const int& value) { bottom = value; }

	int getLeft		() { return left; }
	int getRight	() { return right; }
	int getTop		() { return top; }
	int getBottom	() { return bottom; }
private:
	unsigned char left : 1;
	unsigned char right : 1;
	unsigned char top : 1;
	unsigned char bottom : 1;
};

class MazeMap : public TObject
{
public:
	MazeMap();
public:
	void  				Create				(int iWidth, int iHeight, int iScreenWidth, int iScreenHeight);
	bool  				Render				();
	bool  				Release				();
	void  				Reset				();
	bool  				CreateTile			();
	bool  				RenderTile			();
	void  				RenderPath			();
private:
	bool				CanMove				(int x, int y);
	bool				CanMoveLeft			(int x, int y);
	bool				CanMoveRight		(int x, int y);
	bool				CanMoveTop			(int x, int y);
	bool				CanMoveBottom		(int x, int y);
	void				Visit				(int x, int y);
public:
	int	  				GetPloydIndex		(float fX, float fY);
	PloydPath*			GetPloydPathList(DWORD dwStart, DWORD dwEnd);
	vector<tPoint>&		PloydListToTileList(DWORD dwStart, DWORD dwEnd);
private:
	TIndex				GetTileID			(float x, float y);
	bool				MakePloydPass		();
	bool				ComputePloydPass	();
private:
	tPoint				m_fTileDistance;
	TileVec				m_TileData;
	TObject				m_Wall;
	TObject				m_Road;
	MazeBoxInfo*		m_pMazeBoxInfo;
	bool*				m_pVisited;
	int					m_iWidth;
	int					m_iHeight;
	int					m_iMaxTileWidth;
	int					m_iMaxTileHeight;
	int					m_iScreenWidth;
	int					m_iScreenHeight;
private:
	DWORD				m_dwNumNodes;
	WORD*				m_pPloydVertexArray;
	PloydPath*			m_pPloydPathList;
	POINT*				m_pPloydVertex;
	std::vector<tPoint> m_PathList;
private:
	HPEN				m_hBluePen;
	HPEN				m_hRedPen;
};