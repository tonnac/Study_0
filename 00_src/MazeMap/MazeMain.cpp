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
		int iKey = I_Input.m_dwMouseState[0];
		if (iKey == KEY_PUSH)
		{
			int iUserTile = m_maze.GetPloydIndex(0, 0);
			int iTarget = m_maze.GetPloydIndex(I_Input.m_MousePos.x, I_Input.m_MousePos.y);
			m_pTargetPath = m_maze.GetPloydPathList(iUserTile, iTarget);
			m_PathList = m_maze.PloydListToTileList(iUserTile, iTarget);
		}
		return true;
	}
	bool Render()
	{
		m_maze.RenderTile();
		m_maze.Render();
		m_maze.RenderPath();
		return true;
	}
	bool Release()
	{
		m_maze.Release();
		return true;
	}
private:
	MazeMap				m_maze;
	PloydPath*			m_pTargetPath;
	std::vector<tPoint> m_PathList;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}