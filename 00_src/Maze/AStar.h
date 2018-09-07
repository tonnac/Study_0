#pragma once
#include "Maze.h"
#include <set>
#include <algorithm>

struct AStarNode
{
	AStarNode() : G(0), H(0), _Parent(nullptr)
	{}
	AStarNode(const Nodeindex& nIndex) : G(0), H(0), _Parent(nullptr) 
	{
		_TileIndex._x = nIndex._x;
		_TileIndex._y = nIndex._y;
	}
	AStarNode* _Parent;
	UINT G, H;
	Nodeindex _TileIndex;
};
struct Cmp1
{
	Cmp1(AStarNode* pNode) : anode(pNode)
	{}
	~Cmp1()
	{
		if (anode)
		{
			delete anode;
		}
		anode = nullptr;
	}
	Cmp1(Cmp1 && pnode)
	{
		this->anode = pnode.anode;
		pnode.anode = nullptr;
	}
	bool operator() (AStarNode * aNode)
	{
		return anode->_TileIndex == aNode->_TileIndex;
	}
	AStarNode* anode;
};
struct Cmp
{
	bool operator() (AStarNode* aNode, AStarNode* bNode)
	{
		return (aNode->G + aNode->H < bNode->G + bNode->H);
	}
};

using HeuristicFunc = UINT(*)(const Nodeindex& vStart, const Nodeindex& vTarget);
using AStarPathList = PathList;
using List = std::multiset<AStarNode*, Cmp>;


class AStar
{
public:
	AStar(const Maze& Maze_);
public:
	void				ChangeDiagonal();
	bool				RenderPath();
	void				MakeAStarPath(const Nodeindex& Start, const Nodeindex& Target);
	void				SetHeuristic(HeuristicFunc func);
private:
	void				ListRelease(List& list);
	AStarNode*			FindNodeList(const List& List_, const Nodeindex& FindNode);
private:
	HeuristicFunc		_HeuristicFunc;
	Nodeindex			_Direction[8];
	bool				_Diagonal;
	int					_NumDirection;
	const TileArray *	_Tilearray;
	HPEN				_Redpen;
	AStarPathList		_AStarPath;
};

class Heuristic
{
private:
	static Nodeindex getDistance(const Nodeindex& vStart, const Nodeindex& vTarget);
public:
	static UINT Euclidean(const Nodeindex& vStart, const Nodeindex& vTarget);
	static UINT Manhattan(const Nodeindex& vStart, const Nodeindex& vTarget);
};