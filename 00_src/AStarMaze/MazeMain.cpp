#include "Maze.h"
#include "TCore.h"

class Sample : public TCore
{
public:
	bool		Init()
	{
		m_Maze.CreateMaze(2, 2);
		m_Maze.Init();
		return true;
	}
	bool		Frame()
	{
		return true;
	}
	bool		Render()
	{
		m_Maze.RenderTile();
		m_Maze.Render();
		return true;
	}
	bool		Release()
	{
		return true;
	}
private:
	Maze		m_Maze;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}