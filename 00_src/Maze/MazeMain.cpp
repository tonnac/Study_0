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