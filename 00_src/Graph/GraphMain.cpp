#include "Graph.h"

int main(void)
{
	Graph agraph;
	agraph.setVertex(5);

	agraph.AddEdge(Vertex::A, Vertex::B);
	agraph.AddEdge(Vertex::A, Vertex::C);
	agraph.AddEdge(Vertex::A, Vertex::D);
	agraph.AddEdge(Vertex::B, Vertex::C);
	agraph.AddEdge(Vertex::C, Vertex::E);
	agraph.AddEdge(Vertex::C, Vertex::D);
	agraph.AddEdge(Vertex::D, Vertex::E);

	agraph.ShowGraphEdgeInfo();

	return 0;
}