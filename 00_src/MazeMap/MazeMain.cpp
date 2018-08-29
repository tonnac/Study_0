#include "TCore.h"
#include "MazeMap.h"

class Sample : public TCore
{
public:
	Sample()
	{}
public:
	bool Init()
	{
		m_maze.Create(2, 2, g_rtClient.right, g_rtClient.bottom);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		m_maze.RenderTile();
		m_maze.Render();
		return true;
	}
	bool Release()
	{
		m_maze.Release();
		return true;
	}
private:
	MazeMap m_maze;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}