#include "AStar.h"

AStar::Node::Node(Nodeindex coord_, Node * parent_) :m_coordinates(coord_), m_pParent(parent_), G(0), H(0)
{}

UINT AStar::Node::getScore()
{
	return G + H;
}
bool AStar::NodeCmp::operator () (Node* n1, Node* n2) const
{
	return n1->G < n2->G;
}

AStar::Generator::Generator()
{
	setDiagonalMovement(false);
	setHeuristic(&Heuristic::manhatten);
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
	if (m_iDirection < 8)
	{
		source_ = { 1,1 };
	}
	Node * currentNode = nullptr;
	NodeList openSet, closedSet;
	Node * pl = new Node(source_);
	openSet.insert(pl);

	while (openSet.empty() == false)
	{
		currentNode = *openSet.begin();
		for (auto node : openSet)
		{
			if (node->getScore() <= currentNode->getScore())
			{
				currentNode = node;
			}
		}

		if (currentNode->m_coordinates == target_)
		{
			break;
		}
		closedSet.insert(currentNode);
		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (UINT i = 0; i < m_iDirection; ++i)
		{
			Nodeindex newCoordinates(currentNode->m_coordinates + m_Direction[i]);
			if (detectCollision(newCoordinates))
			{
				continue;
			}
			if (findNodeOnList(closedSet, newCoordinates))
			{
				continue;
			}
			
			UINT totalCost = currentNode->G + ((i < 4) ? 10 : 14);

			Node * successor = findNodeOnList(openSet, newCoordinates);
			if (successor == nullptr)
			{
				successor = new Node(newCoordinates, currentNode);
				successor->G = totalCost;
				successor->H = heuristic(successor->m_coordinates, target_);
				openSet.insert(successor);
			}
			else if (totalCost < successor->G)
			{
				successor->m_pParent = currentNode;
				successor->G = totalCost;
			}
		}
	}

	CoordinateList path;
	while (currentNode != nullptr)
	{
		path.push_back(currentNode->m_coordinates);
		currentNode = currentNode->m_pParent;
	}

	releaseNodes(openSet);
	releaseNodes(closedSet);

	return path;
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
	for (auto node : nodes_)
	{
		if (node->m_coordinates == coordinates_)
		{
			return node;
		}
	}
	return nullptr;
}
void AStar::Generator::releaseNodes(NodeList& nodes_)
{
	for (auto iter : nodes_)
	{
		delete iter;
	}
	nodes_.clear();
}
Nodeindex AStar::Heuristic::getDelta(Nodeindex source_, Nodeindex target_)
{
	return { abs(source_._x - target_._x), abs(source_._y - target_._y) };
}
UINT AStar::Heuristic::manhatten(Nodeindex _source, Nodeindex target_)
{
	auto delta = std::move(getDelta(_source, target_));
	return static_cast<UINT>(10 * (delta._x + delta._y));
}
UINT AStar::Heuristic::euclidean(Nodeindex _source, Nodeindex target_)
{
	Nodeindex a = getDelta(_source, target_);
	Nodeindex&& delta = std::move(getDelta(_source, target_));
	return static_cast<UINT>(10 * sqrt(pow(delta._x, 2) + pow(delta._y, 2)));
}
UINT AStar::Heuristic::octagonal(Nodeindex _source, Nodeindex target_)
{
	auto delta = std::move(getDelta(_source, target_));
	return 10 * (delta._x + delta._y) + (-6) * min(delta._x, delta._y);
}
