#include "AStar.h"

AStar::AStar(const Maze& Maze_) : _Diagonal(false), _NumDirection(4)
{
	_Redpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	_Direction[0] = { -1,0 };
	_Direction[1] = { 1,0 };
	_Direction[2] = { 0,-1 };
	_Direction[3] = { 0,1 };
	_Direction[4] = { -1,1 };
	_Direction[5] = { 1,-1 };
	_Direction[6] = { -1,-1 };
	_Direction[7] = { 1,1 };
	_HeuristicFunc = &Heuristic::Manhattan;
	_Tilearray = Maze_.getTileArray();
	ChangeDiagonal();
}

void AStar::ChangeDiagonal()
{
	_Diagonal = !_Diagonal;
	_NumDirection = (_Diagonal == true) ? 8 : 4;
}


bool AStar::RenderPath()
{
	HPEN oldpen = (HPEN)(SelectObject(g_hOffScreenDC, _Redpen));
	Nodeindex vStart = { 1,1 };
	for (auto iter : _AStarPath.m_Path)
	{
		Nodeindex vTarget = iter;
		tPoint StartPos = (*_Tilearray)[vStart._y][vStart._x]._CenterPos;
		tPoint TargetPos = (*_Tilearray)[vTarget._y][vTarget._x]._CenterPos;
		MoveToEx(g_hOffScreenDC, StartPos.x, StartPos.y, NULL);
		LineTo(g_hOffScreenDC, TargetPos.x, TargetPos.y);
		vStart = vTarget;
	}
	SelectObject(g_hOffScreenDC, oldpen);
	return true;
}
void AStar::MakeAStarPath(const Nodeindex& Start, const Nodeindex& Target)
{
	_AStarPath.m_Path.clear();
	List OpenList, ClosedList;

	AStarNode * CurrentNode = new AStarNode;
	CurrentNode->_TileIndex = Start;
	OpenList.insert(CurrentNode);

	while (OpenList.empty() == false)
	{
		CurrentNode = (*OpenList.begin());
		ClosedList.insert(CurrentNode);
		OpenList.erase(OpenList.begin());

		if (CurrentNode->_TileIndex == Target)
		{
			break;
		}

		for (int i = 0; i < _NumDirection; ++i)
		{
			Nodeindex TileIndex = CurrentNode->_TileIndex;
			TileIndex += _Direction[i];
			if (FindNodeList(ClosedList, TileIndex))
			{
				continue;
			}
			if ((*_Tilearray)[TileIndex._y][TileIndex._x]._TileType == 1)
			{
				continue;
			}

			int h = (i > 3) ? 14 : 10;
			AStarNode* aNewNode = FindNodeList(OpenList, TileIndex);
			if (aNewNode == nullptr)
			{
				aNewNode = new AStarNode;
				aNewNode->G = CurrentNode->G + h;
				aNewNode->_Parent = CurrentNode;
				aNewNode->_TileIndex = TileIndex;
				aNewNode->H = _HeuristicFunc(CurrentNode->_TileIndex, Target);
				OpenList.insert(aNewNode);
			}
			else
			{
				if (CurrentNode->G + CurrentNode->H > aNewNode->G + aNewNode->H)
				{
					ClosedList.insert(CurrentNode);
					CurrentNode = aNewNode;
				}
			}
		}
	}
	while (CurrentNode != nullptr)
	{
		_AStarPath.m_Path.push_front(CurrentNode->_TileIndex);
		_AStarPath.m_iWeight += 1;
		CurrentNode = CurrentNode->_Parent;
	}
	ListRelease(ClosedList);
}
void AStar::SetHeuristic(HeuristicFunc func)
{
	this->_HeuristicFunc = func;
}
void AStar::ListRelease(List& list)
{
	for (auto iter : list)
	{
		delete iter;
	}
	list.clear();
}
AStarNode* AStar::FindNodeList(const List& List_, const Nodeindex& FindNode)
{
	List::iterator iter = std::find_if(List_.begin(), List_.end(), Cmp1(new AStarNode(FindNode)));
	if (iter == List_.end())
	{
		return nullptr;
	}
	return *iter;
}

Nodeindex Heuristic::getDistance(const Nodeindex& vStart, const Nodeindex& vTarget)
{
	return { abs(vStart._x - vTarget._x), abs(vStart._y - vTarget._y) };
}
UINT Heuristic::Euclidean(const Nodeindex& vStart, const Nodeindex& vTarget)
{
	Nodeindex Distance = getDistance(vStart, vTarget);
	return static_cast<UINT>(sqrt(pow(Distance._x, 2) + pow(Distance._y, 2)) * 10);
}
UINT Heuristic::Manhattan(const Nodeindex& vStart, const Nodeindex& vTarget)
{
	Nodeindex Distance = getDistance(vStart, vTarget);
	return (Distance._x + Distance._y) * 10;
}