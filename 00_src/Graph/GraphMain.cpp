#include "Graph.h"

int main(void)
{
	Graph agraph(7);

	agraph.AddEdge(Vertex::A, Vertex::B);
	agraph.AddEdge(Vertex::A, Vertex::D);
	agraph.AddEdge(Vertex::B, Vertex::C);
	agraph.AddEdge(Vertex::C, Vertex::D);
	agraph.AddEdge(Vertex::D, Vertex::E);
	agraph.AddEdge(Vertex::E, Vertex::F);
	agraph.AddEdge(Vertex::E, Vertex::G);

	agraph.ShowGraphEdgeInfo();
	agraph.DFSShowGraphVertex(Vertex::A); std::cout << std::endl;
	agraph.DFSShowGraphVertex(Vertex::C); std::cout << std::endl;
	agraph.DFSShowGraphVertex(Vertex::E); std::cout << std::endl;
	agraph.DFSShowGraphVertex(Vertex::G); std::cout << std::endl;

	return 0;
}