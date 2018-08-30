#pragma once
#include "TObject.h"

#define INF	1000000
enum class Dir : unsigned char { LEFT = 0, RIGHT, TOP, BOTTOM };
using PloydList = std::list<int>;

struct Tile
{
	int		m_iType;
	tPoint	m_point;
};

struct MazeBoxInfo
{
public:
	MazeBoxInfo() : left(0), right(0), top(0), bottom(0)
	{}
public:
	int			 getLeft	() { return left; }
	int			 getRight	() { return right; }
	int			 getTop		() { return top; }
	int			 getBottom	() { return bottom; }
public:			 
	void		 setLeft	(const int& value) { left = value; }
	void		 setRight	(const int& value) { right = value; }
	void		 setTop		(const int& value) { top = value; }
	void		 setBottom	(const int& value) { bottom = value; }
private:
	unsigned int left : 1;
	unsigned int right : 1;
	unsigned int top : 1;
	unsigned int bottom : 1;
};

struct PloydPath
{
	PloydPath(const int& x, const int& y) : m_iHeight(y)
	{
		m_pPloydList = new PloydList*[y];
		for (size_t i = 0; i < y; ++i)
		{
			m_pPloydList[i] = new PloydList[x];
		}
	};
	~PloydPath()
	{
		for (size_t i = 0; i < m_iHeight; ++i)
		{
			delete[] m_pPloydList;
		}
		delete m_pPloydList;
		m_pPloydList = nullptr;
	}
	PloydList	getPloydList(const int& x, const int& y) { return m_pPloydList[y][x]; }
	void		setPloydList(PloydList ** pPloydList) { m_pPloydList = pPloydList; }
	PloydList** m_pPloydList;
	int			m_iHeight;
};

class Maze : public TObject
{
public:
	Maze();
	~Maze();
public:
	void			CreateMaze		(const int& width, const int& height);
public:
	void			CreateTile		();
public:
	bool			Render();
	bool			RenderTile();
private:
	void			VisitVertex		(const int& x, const int& y);
private:
	bool			CanMove			(const int& x, const int& y);
	bool			CanMoveLeft		(const int& x, const int& y);
	bool			CanMoveRight	(const int& x, const int& y);
	bool			CanMoveTop		(const int& x, const int& y);
	bool			CanMoveBottom	(const int& x, const int& y);
private:
	void			CreatePloydPath();
private:
	int				m_iWidth;
	int				m_iHeight;
	int				m_iScreenWidth;
	int				m_iScreenHeight;
	int				m_iMaxTileWidth;
	int				m_iMaxTileHeight;
private:
	Tile **			m_pTileSet;
	POINT			m_pLocation;
	MazeBoxInfo **	m_pBoxinfo;
	bool **			m_pVisited;
private:
	TObject			m_Wall;
	TObject			m_Road;
private:
	HPEN			m_hBluePen;
};