#include "TCore.h"
#include "Maze.h"
#include "PloydPath.h"

class Sample : public TCore
{
public:
	Sample()
	{}
public:
	bool Init()
	{
		_Maze.CreateMaze(3, 3);
		_Ployd.MakePloydPath(_Maze.getMazeArray());
		return true;
	}
	bool Frame()
	{
		DWORD dwKey = I_Input.m_dwMouseState[0];
		if (dwKey == KEY_PUSH)
		{
			Nodeindex vStart = { 0,0 };
			Nodeindex vTarget = _Maze.getTargetIndex(I_Input.m_MousePos);
		}

		return true;
	}
	bool Render()
	{
		_Maze.Render();
		_Ployd.RenderPath();
		return true;
	}
	bool Release()
	{
		return true;
	}
private:
	Maze		_Maze;
	PloydPath	_Ployd;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}