#include "PloydPath.h"


void PloydPath::MakePloydPath(const MazeArray& Maze_)
{
	PloydPathList GraphTable;
	GraphTable = MakeGraphTable(Maze_);

}