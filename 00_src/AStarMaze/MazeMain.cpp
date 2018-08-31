#include "Maze.h"
#include "TCore.h"
#include <ctime>

class Sample : public TCore
{
public:
	bool		Init()
	{
		srand(time(NULL));
		m_Maze.CreateMaze(15, 15);
		m_Maze.Init();
		return true;
	}
	bool		Frame()
	{
		DWORD dwKey = I_Input.m_dwMouseState[0];
		if (dwKey == KEY_PUSH)
		{
			Nodeindex TargetNode = m_Maze.getTargetIndex(I_Input.m_MousePos.x, I_Input.m_MousePos.y);
			m_Maze.SelectPath(TargetNode);
		}
		return true;
	}
	bool		Render()
	{
		m_Maze.Reset();
		m_Maze.RenderTile();
		m_Maze.RenderPath();
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