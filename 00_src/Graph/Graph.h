#pragma once
#include <list>
#include <stack>
#include <iostream>

enum Vertex
{
	A = 0, B, C, D, E, F, G
};

using GraphData = Vertex;
using GraphStack = std::stack<GraphData>;
using GraphList = std::list<GraphData>;
using GraphIter = std::list<GraphData>::const_iterator;

class Graph
{
public:
	Graph(const int& verNum);
	~Graph();
public:
	void		AddEdge				(const Vertex& fromV, const Vertex& toV);
	void		ShowGraphEdgeInfo	();
	void		DFSShowGraphVertex	(const Vertex& startV);
private:
	bool		VisitVertex			(const Vertex& Ver);
private:
	GraphList * m_pGList;
	int			m_iEdgeNumber;
	int			m_iVerNumver;
	bool*		m_bVisitInfo;
};