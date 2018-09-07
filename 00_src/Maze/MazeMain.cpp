#include "TCore.h"
#include "Maze.h"
#include "PloydPath.h"
#include "AStar.h"

//#define Ployd
#define AStarPath

class Sample : public TCore
{
public:
	Sample() : _AStar(_Maze)
	{}
public:
	bool Init()
	{
		_Maze.CreateMaze(60, 60);
#ifdef Ployd
		_Ployd.MakePloydPath(_Maze);
#endif
		return true;
	}
	bool Frame()
	{
		DWORD dwKey = I_Input.m_dwMouseState[0];
		if (dwKey == KEY_PUSH)
		{
			Nodeindex vStart = { 1,1 };
			Nodeindex vTarget = _Maze.getTargetIndex(I_Input.m_MousePos);
#ifdef Ployd
			_Ployd.SetTarget(vStart, vTarget);
#endif
#ifdef AStarPath
			vTarget *= 2;
			vTarget += 1;
			_AStar.MakeAStarPath(vStart, vTarget);
#endif
		}
		return true;
	}
	bool Render()
	{
		_Maze.Render();
#ifdef Ployd
		_Ployd.RenderPath();
#endif
#ifdef AStarPath
		_AStar.RenderPath();
#endif
		_Maze.Reset();
		return true;
	}
	bool Release()
	{
		return true;
	}
private:
	Maze		_Maze;
	PloydPath	_Ployd;
	AStar		_AStar;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1800, 1000);
	wd.Run();

	return 0;
}