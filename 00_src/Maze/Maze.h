#pragma once
#include "TObject.h"

enum class DIR : unsigned char
{
	LEFT = 0,
	TOP,
	RIGHT,
	BOTTOM
};

struct MazeTile
{
	MazeTile() : _TileType(0), _CenterPos({0,0}), _DrawPos({0,0})
	{}
	int _TileType;
	tPoint _CenterPos;
	tPoint _DrawPos;
};

class MazeInfo
{
public:
	MazeInfo();
public:
	int getLeft();
	int getTop();
	int getRight();
	int getBottom();
	bool getVisit();
public:
	void setLeft(const int& Left);
	void setTop(const int& Top);
	void setRight(const int& Right);
	void setBottom(const int& Bottom);
	void setVisit(const bool& Visit);
private:
	unsigned int left : 1;
	unsigned int top : 1;
	unsigned int right : 1;
	unsigned int bottom : 1;
	bool _isVisit;
};

using MazeArray = std::vector<std::vector<MazeInfo>>;

class Maze : public TObject
{
public:
	void		CreateMaze(const int& iWidth, const int& iHeight);
private:
	bool		CanMove(const int& x, const int& y);
	bool		CanMoveLeft(const int& x, const int& y);
	bool		CanMoveTop(const int& x, const int& y);
	bool		CanMoveRight(const int& x, const int& y);
	bool		CanMoveBottom(const int& x, const int& y);
private:
	void		VisitVertex(const int& x, const int& y);
private:
	Nodeindex	_MazeSize;
	MazeArray	_MazeArray;
};