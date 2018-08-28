#include "Graph.h"

Graph::Graph(const int& verNum) : m_iEdgeNumber(0), m_iVerNumver(verNum)
{
	m_pGList = new GraphList[verNum];
	m_bVisitInfo = new bool[verNum];
	memset(m_bVisitInfo, 0, sizeof(bool) * verNum);
}
Graph::~Graph()
{
	delete[] m_bVisitInfo;
	m_bVisitInfo = nullptr;
	delete[] m_pGList;
	m_pGList = nullptr;
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
void Graph::DFSShowGraphVertex(const Vertex& startV)
{
	GraphStack gstack;
	Vertex visitV = startV;
	Vertex nextV = visitV;
	GraphIter* iter;
	iter = new GraphIter[m_iVerNumver];
	for (int iVer = 0; iVer < m_iVerNumver; ++iVer)
	{
		iter[iVer] = m_pGList[iVer].begin();
	}

	VisitVertex(visitV);

	while (true)
	{
		while (iter[visitV] != m_pGList[visitV].end())
		{
			if (VisitVertex(*iter[visitV]) == true)
			{
				nextV = *iter[visitV];
				gstack.push(visitV);
				iter[visitV]++;
				visitV = nextV;
			}
			else
			{
				iter[visitV]++;
			}
		}

		if (gstack.empty() == false)
		{
			visitV = gstack.top();
			gstack.pop();
		}
		else
		{
			break;
		}
	}
	memset(m_bVisitInfo, 0, sizeof(bool) * m_iVerNumver);
	delete[] iter;
	return;
}
bool Graph::VisitVertex(const Vertex& Ver)
{
	if (m_bVisitInfo[Ver] == false)
	{
		m_bVisitInfo[Ver] = true;
		std::cout << static_cast<char>(Ver + 65) << " ";
		return true;
	}
	return false;
}