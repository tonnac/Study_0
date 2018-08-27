#pragma once
#include <list>
#include <stack>
#include <iostream>

enum Vertex
{
	A = 0, B, C, D, E, F
};

using GraphData = int;
using GraphStack = std::stack<GraphData>;
using GraphList = std::list<GraphData>;
using GraphIter = std::list<GraphData>::const_iterator;

class Graph
{
public:
	Graph();
	~Graph();
public:
	void		setVertex			(const int& verNum);
	void		AddEdge				(const Vertex& fromV, const Vertex& toV);
	void		ShowGraphEdgeInfo	();
	void		DFSShowGraphVertex	(const int& startV);
private:
	void		VisitVertex			(const Vertex& Ver);
private:
	GraphList * m_pGList;
	int			m_iEdgeNumber;
	int			m_iVerNumver;
	int*		m_iVisitInfo;
};