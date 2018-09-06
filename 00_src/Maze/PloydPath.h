#pragma once
#include "Maze.h"

using PathList = std::list<Nodeindex>;
using PloydPathList = std::vector<std::vector<PathList>>;

class PloydPath
{
public:
	bool			RenderPath		();
	void			MakePloydPath	(const MazeArray& Maze_);
private:
	PloydPathList	MakeGraphTable	(const MazeArray& Maze_);
private:
	PloydPathList	_PloydPath;
};