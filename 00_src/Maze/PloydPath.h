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
	bool			RenderPath		();
	void			MakePloydPath	(const MazeArray& Maze_);
private:
	void			MakeGraphTable	(const MazeArray& Maze_);
private:

	PloydPathList	_PloydPath;
};