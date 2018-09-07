#pragma once
#include "Maze.h"

#define INF 1000000

//using PathList = std::list<Nodeindex>;
struct PathList
{
	PathList() : m_iWeight(0)
	{
		m_Path.clear();
	}
	int					 m_iWeight;
	std::list<Nodeindex> m_Path;
};
using PloydPathList = std::vector<std::vector<PathList>>;

class PloydPath
{
public:
	PloydPath();
public:
	void			SetTarget		(const Nodeindex& vStart, const Nodeindex& vTarget);
	bool			RenderPath		();
	void			MakePloydPath	(Maze& Maze);
private:
	void			MakeGraphTable	(const MazeArray& Maze);
private:
	TileArray*		_TileArray;
	HPEN			_RedPen;
	Nodeindex		_TargetTableindex;
	size_t			_Height;
	PloydPathList	_PloydPath;
};