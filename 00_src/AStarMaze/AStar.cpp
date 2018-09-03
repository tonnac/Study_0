#include "AStar.h"


AStar::Node::Node(Nodeindex coord_, Node * parent_ = nullptr) :m_coordinates(coord_), m_pParent(parent_)
{}

UINT AStar::Node::getScore()
{
	return G + H;
}

bool AStar::NodeCmp::operator () (const Node* n1, const Node* n2)
{
	return n1->G < n2->G;
}
AStar::Generator::Generator()
{
	setDiagonalMovement(false);
	setHeuristic();
	m_Direction = {
	{0,1},
	{1,0},
	{0,-1},
	{-1,0},
	{-1,-1},{1,1},{-1,1},{1,-1}
	};
}
void AStar::Generator::setWorldSize(Nodeindex worldSize_)
{
	m_WorldSize = worldSize_;
}
void AStar::Generator::setDiagonalMovement(bool enable_)
{
	m_iDirection = (enable_ ? 8 : 4);
}
void AStar::Generator::setHeuristic(HeuristcFunction heuristic_)
{
	heuristic = std::bind(heuristic_, std::placeholders::_1, std::placeholders::_2);
}
AStar::CoordinateList AStar::Generator::findPath(Nodeindex source_, Nodeindex target_)
{
	Node * currentNode = nullptr;
	NodeList openSet, closedSet;
	openSet.push(currentNode);

	while (openSet.empty() == false)
	{
		currentNode = openSet.top();
	}
}
void AStar::Generator::addCollision(Nodeindex coordinates_)
{
	m_Walls.push_back(coordinates_);
}
void AStar::Generator::removeCollision(Nodeindex coordinates_)
{
	auto iter = std::find(m_Walls.begin(), m_Walls.end(), coordinates_);
	if (iter != m_Walls.end())
	{
		m_Walls.erase(iter);
	}
}
void AStar::Generator::clearCollisions()
{
	m_Walls.clear();
}
bool AStar::Generator::detectCollision(Nodeindex coordinates_)
{
	if (coordinates_._x < 0 || coordinates_._x >= m_WorldSize._x ||
		coordinates_._y < 0 || coordinates_._y >= m_WorldSize._y ||
		std::find(m_Walls.begin(), m_Walls.end(), coordinates_) != m_Walls.end())
	{
		return true;
	}
	return false;
}
AStar::Node* AStar::Generator::findNodeOnList(NodeList& nodes_, Nodeindex coordinates_)
{
}
void AStar::Generator::releaseNodes(NodeList& nodes_)
{
	while (nodes_.empty() == false)
	{
		Node * delNode = nodes_.top();
		delete delNode;
		nodes_.pop();
	}
}