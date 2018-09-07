#include "PloydPath.h"

bool PloydPath::RenderPath()
{
	// 인덱스를 찾아서 인덱스 별로 선을 잇는다.
	return true;
}
void PloydPath::MakePloydPath(const MazeArray& Maze_)
{
	MakeGraphTable(Maze_);
	size_t Num = Maze_.cbegin()->size() * Maze_.size();
	for (size_t k = 0; k < Num; ++k)
	{
		for (size_t i = 0; i < Num; ++i)
		{
			for (size_t j = 0; j < Num; ++j)
			{
				if (_PloydPath[i][j].m_iWeight > _PloydPath[i][k].m_iWeight + _PloydPath[k][j].m_iWeight)
				{
					_PloydPath[i][j].m_Path.assign(_PloydPath[i][k].m_Path.begin(), _PloydPath[i][k].m_Path.end());
					_PloydPath[i][j].m_Path.insert(_PloydPath[i][j].m_Path.end(), _PloydPath[k][j].m_Path.begin(), _PloydPath[k][j].m_Path.end());
					_PloydPath[i][j].m_iWeight = _PloydPath[i][k].m_iWeight + _PloydPath[k][j].m_iWeight;
				}
			}
		}
	}
	int k = 0;
}
void PloydPath::MakeGraphTable(const MazeArray& Maze_)
{
	int k = 0;
	MazeArray& cMaze = const_cast<MazeArray&>(Maze_);
	size_t Width = Maze_.cbegin()->size();
	size_t Height = Maze_.size();
	size_t iWidth = Width * Height;
	size_t iHeight = iWidth;
	PathList pl;
	std::vector<PathList> Path(iWidth, pl);
	_PloydPath.assign(iHeight, Path);
	for (size_t y = 0; y < Height; ++y)
	{
		for (size_t x = 0; x < Width; ++x)
		{
			if (Maze_.at(y).at(x).getLeft() == 0)
			{
				_PloydPath.at(k).at(k - 1).m_Path.push_back(Nodeindex(x - 1, y));
				_PloydPath.at(k).at(k - 1).m_iWeight = 1;
			}
			if (Maze_.at(y).at(x).getTop() == 0)
			{
				_PloydPath.at(k).at(k - Width).m_Path.push_back(Nodeindex(x, y - 1));
				_PloydPath.at(k).at(k - Width).m_iWeight = 1;
			}
			if (Maze_.at(y).at(x).getRight() == 0)
			{
				_PloydPath.at(k).at(k + 1).m_Path.push_back(Nodeindex(x + 1, y));
				_PloydPath.at(k).at(k + 1).m_iWeight = 1;
			}
			if (Maze_.at(y).at(x).getBottom() == 0)
			{
				_PloydPath.at(k).at(k + Width).m_Path.push_back(Nodeindex(x, y + 1));
				_PloydPath.at(k).at(k + Width).m_iWeight = 1;
			}
			++k;
		}
	}
	for (size_t i = 0; i < iHeight; ++i)
	{
		for (size_t j = 0; j < iWidth; ++j)
		{
			if (i == j)
			{
				_PloydPath.at(i).at(j).m_iWeight = 0;
				continue;
			}
			if (_PloydPath.at(i).at(j).m_iWeight == 0)
			{
				_PloydPath.at(i).at(j).m_iWeight = INF;
			}
		}
	}
}