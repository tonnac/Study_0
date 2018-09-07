#include "PloydPath.h"

PloydPath::PloydPath()
{
	_RedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
}

void PloydPath::SetTarget(const Nodeindex& vStart, const Nodeindex& vTarget)
{
	_TargetTableindex._x = vStart._y * static_cast<int>(_Height) + vStart._x;
	_TargetTableindex._y = vTarget._y * static_cast<int>(_Height) + vTarget._x;
}
bool PloydPath::RenderPath()
{
	HPEN oldpen = (HPEN)SelectObject(g_hOffScreenDC, _RedPen);
	Nodeindex vStart = { 1,1 };
	for (auto iter : _PloydPath[_TargetTableindex._x][_TargetTableindex._y].m_Path)
	{
		Nodeindex vTarget = iter;
		vTarget *= 2, vTarget += 1;
		tPoint StartPos = (*_TileArray)[vStart._y][vStart._x]._CenterPos;
		tPoint TargetPos = (*_TileArray)[vTarget._y][vTarget._x]._CenterPos;
		MoveToEx(g_hOffScreenDC, StartPos.x, StartPos.y, NULL);
		LineTo(g_hOffScreenDC, TargetPos.x, TargetPos.y);
		vStart = vTarget;
	}
	SelectObject(g_hOffScreenDC, oldpen);
	return true;
}
void PloydPath::MakePloydPath(const Maze& Maze)
{
	_TileArray = Maze.getTileArray();
	MazeArray Maze_ = Maze.getMazeArray();
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
}
void PloydPath::MakeGraphTable(const MazeArray& Maze_)
{
	int k = 0;
	size_t Width = Maze_.cbegin()->size();
	size_t Height = Maze_.size();
	_Height = Height;
	size_t iWidth = Width * Height;
	size_t iHeight = iWidth;
	PathList pl;
	std::vector<PathList> Path(iWidth, pl);
	_PloydPath.assign(iHeight, Path);
	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
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
	for (int i = 0; i < iHeight; ++i)
	{
		for (int j = 0; j < iWidth; ++j)
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