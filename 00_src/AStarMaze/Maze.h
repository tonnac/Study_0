#pragma once
#include "TObject.h"

#define INF	1000000
enum class Dir : unsigned char { LEFT = 0, RIGHT, TOP, BOTTOM };

struct Tile
{
	int		m_iType;
	tPoint	m_point;
	tPoint	m_CenterPos;
};
struct Nodeindex
{
	Nodeindex operator*(const int& Multipie)
	{
		_x *= Multipie;
		_y *= Multipie;
		return *this;
	}
	Nodeindex operator+=(const int& AddValue)
	{
		_x += AddValue;
		_y += AddValue;
		return *this;
	}
	Nodeindex(const int& x, const int& y) : _x(x), _y(y)
	{}
	int _x, _y;
};
using PloydList = std::list<Nodeindex>;
struct PloydPathNode
{
	PloydPathNode() : m_iWeight(0)
	{
		m_pPloydList.clear();
	}
	int			m_iWeight;
	PloydList	m_pPloydList;
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

class Maze : public TObject
{
public:
	Maze();
	~Maze();
public:
	void			CreateMaze		(const int& width, const int& height);
public:
	Nodeindex		getTargetIndex	(const int& x, const int& y);
	void			SelectPath		(const Nodeindex& nIndex);
public:
	bool			Reset			();
	bool			Render			();
	bool			RenderPath		();
	bool			RenderTile		();
private:
	void			CreateTile		();
private:
	void			VisitVertex		(const int& x, const int& y);
private:
	bool			CanMove			(const int& x, const int& y);
	bool			CanMoveLeft		(const int& x, const int& y);
	bool			CanMoveRight	(const int& x, const int& y);
	bool			CanMoveTop		(const int& x, const int& y);
	bool			CanMoveBottom	(const int& x, const int& y);
private:
	void			MakeGraphTable();
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
	PloydPathNode	m_CurrentPath;
	PloydPathNode **m_pPloydPath;
private:
	TObject			m_Wall;
	TObject			m_Road;
private:
	HPEN			m_hRedPen;
	HPEN			m_hBluePen;
};