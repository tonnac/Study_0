#pragma once
#include "TObject.h"

enum class DIR : unsigned char
{
	LEFT = 0,
	TOP,
	RIGHT,
	BOTTOM
};

struct MazeTile
{
	MazeTile() : _TileType(1), _CenterPos({0,0}), _DrawPos({0,0})
	{}
	int		_TileType;
	tPoint  _CenterPos;
	tPoint  _DrawPos;
};

struct PathList
{
	PathList() : m_iWeight(0)
	{
		m_Path.clear();
	}
	int					 m_iWeight;
	std::list<Nodeindex> m_Path;
};

class MazeInfo
{
public:
	MazeInfo();
public:
	int			 getLeft		() const;
	int			 getTop			() const;
	int			 getRight		() const;
	int			 getBottom		() const;
	bool		 getVisit		() const;
public:			 
	void		 setLeft		(const int& Left);
	void		 setTop			(const int& Top);
	void		 setRight		(const int& Right);
	void		 setBottom		(const int& Bottom);
	void		 setVisit		(const bool& Visit);
private:
	unsigned int left : 1;
	unsigned int top : 1;
	unsigned int right : 1;
	unsigned int bottom : 1;
	bool		 _isVisit;
};

using MazeArray = std::vector<std::vector<MazeInfo>>;
using TileArray = std::vector<std::vector<MazeTile>>;

class Maze : public TObject
{
public:
	void				CreateMaze		(const int& iWidth, const int& iHeight);
public:
	bool				Reset();
	bool				Render();
public:
	MazeArray			getMazeArray	() const;
	const TileArray*	getTileArray	() const;
	Nodeindex			getTargetIndex	(const POINT& TargetPoint) const;
private:
	bool				CanMove			(const int& x, const int& y);
	bool				CanMoveLeft		(const int& x, const int& y);
	bool				CanMoveTop		(const int& x, const int& y);
	bool				CanMoveRight	(const int& x, const int& y);
	bool				CanMoveBottom	(const int& x, const int& y);
private:
	void				VisitVertex		(const int& x, const int& y);
	void				CreateTile		();
private:
	Nodeindex			_MazeSize;
	Nodeindex			_TileSize;
	MazeArray			_MazeArray;
	TileArray			_TileArray;
	TObject				_Wall;
	TObject				_Road;
};