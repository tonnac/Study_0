#pragma once
#include "Maze.h"

#define INF 1000000

//using PathList = std::list<Nodeindex>;

using PloydPathList = std::vector<std::vector<PathList>>;

class PloydPath
{
public:
	PloydPath();
public:
	void			SetTarget		(const Nodeindex& vStart, const Nodeindex& vTarget);
	bool			RenderPath		();
	void			MakePloydPath	(const Maze& Maze);
private:
	void			MakeGraphTable	(const MazeArray& Maze);
private:
	const TileArray*_TileArray;
	HPEN			_RedPen;
	Nodeindex		_TargetTableindex;
	size_t			_Height;
	PloydPathList	_PloydPath;
};