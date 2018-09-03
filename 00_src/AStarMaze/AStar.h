#pragma once
#include "TStd.h"
#include <functional>
#include <queue>
#include <algorithm>

namespace AStar
{
	using HeuristcFunction = std::function<UINT(Nodeindex, Nodeindex)>;
	using CoordinateList = std::vector<Nodeindex>;

	struct Node
	{
		UINT G, H;
		Nodeindex m_coordinates;
		Node * m_pParent;

		Node(Nodeindex coord_, Node * parent_ = nullptr);
		UINT getScore();
	};

	struct NodeCmp
	{
		bool operator () (const Node* n1, const Node* n2);
	};

	using NodeList = std::priority_queue<Node*, std::vector<Node*>, NodeCmp>;

	class Generator
	{
	public:
		Generator();
	public:
		void			setWorldSize			(Nodeindex worldSize_);
		void			setDiagonalMovement		(bool enable_);
		void			setHeuristic			(HeuristcFunction heuristic_);
		CoordinateList	findPath				(Nodeindex source_, Nodeindex target_);
		void			addCollision			(Nodeindex coordinates_);
		void			removeCollision			(Nodeindex coordinates_);
		void			clearCollisions();
	private:
		bool			detectCollision			(Nodeindex coordinates_);
		Node*			findNodeOnList			(NodeList& nodes_, Nodeindex coordinates_);
		void			releaseNodes			(NodeList& nodes_);
	private:
		HeuristcFunction	heuristic;
		CoordinateList		m_Direction, m_Walls;
		Nodeindex			m_WorldSize;
		UINT				m_iDirection;
	};
}