#include "TCore.h"
#include "Maze.h"

class Sample : public TCore
{
public:
	Sample()
	{}
public:
	bool Init()
	{
		_Maze.CreateMaze(3, 3);
		return true;
	}
	bool Frame()
	{

		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()
	{
		return true;
	}
private:
	Maze		_Maze;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}