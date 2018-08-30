#pragma once
#include "TObject.h"

struct MazeBoxInfo
{
public:
	MazeBoxInfo() : left(1), right(1), top(1), bottom(1)
	{}
public:
	int			getLeft		() { return left; }
	int			getRight	() { return right; }
	int			getTop		() { return top; }
	int			getBottom	() { return bottom; }
public:
	void		 setLeft	(const int& value) { left = value; }
	void		 setRight	(const int& value) { right = value; }
	void		 setTop		(const int& value) { top = value; }
	void		 setBottom	(const int& value) { bottom = value; }
private:
	unsigned int left : 1;
	unsigned int right : 1;
	unsigned int top : 1;
	unsigned int bottom : 1;
};


class Maze : public TObject
{
public:
	Maze();
public:
	void			CreateMaze		(const int& width, const int& height);
private:
	void			Visit			(const int& x, const int& y);
	bool			getLocation		(const int& x, const int& y);
private:
	bool			CanMove			(const int& x, const int& y);
	bool			CanMoveLeft		(const int& x, const int& y);
	bool			CanMoveRight	(const int& x, const int& y);
	bool			CanMoveTop		(const int& x, const int& y);
	bool			CanMoveBottom	(const int& x, const int& y);
private:
	int				m_iWidth;
	int				m_iHeight;
	int				m_iScreenWidth;
	int				m_iScreenHeight;
private:
	POINT			m_pLocation;
	MazeBoxInfo **	m_pBoxinfo;
	bool **			m_pVisited;
};