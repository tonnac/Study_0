#include "Graph.h"

Graph::Graph() : m_iEdgeNumber(0), m_iVisitInfo(nullptr)
{}
Graph::~Graph()
{
	delete[] m_pGList;
	m_pGList = nullptr;
}

void Graph::setVertex(const int& verNum)
{
	m_pGList = new GraphList[verNum];
	m_iVerNumver = verNum;
}

void Graph::AddEdge(const Vertex& fromV, const Vertex& toV)
{
	m_pGList[fromV].push_back(toV);
	m_pGList[toV].push_back(fromV);
	m_iEdgeNumber++;
}
void Graph::ShowGraphEdgeInfo()
{
	for (int iVer = 0; iVer < m_iVerNumver; ++iVer)
	{
		std::cout << static_cast<char>(iVer + 65) << " :";
		GraphIter iter = m_pGList[iVer].begin();
		for (; iter != m_pGList[iVer].end(); ++iter)
		{
			if (iter != m_pGList[iVer].end())
			{
				std::cout << " ";
			}
			std::cout << static_cast<char>(*iter + 65);
		}
		std::cout << std::endl;
	}
}
void Graph::DFSShowGraphVertex(const int& startV)
{
	GraphStack gstack;

	return;
}