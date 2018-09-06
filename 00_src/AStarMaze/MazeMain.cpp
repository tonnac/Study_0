#include "Maze.h"
#include "TCore.h"
#include <ctime>
#include "AStar.h"

class Sample : public TCore
{
public:
	bool		Init()
	{
		srand(time(NULL));
		m_Maze.CreateMaze(5, 5);
		m_Maze.Init();
		
		generator.setWorldSize({ m_Maze.getMaxTileWidth(), m_Maze.getMaxTileHeight() });

		for (int h = 0; h < m_Maze.getMaxTileHeight(); ++h)
		{
			for (int w = 0; w < m_Maze.getMaxTileWidth(); ++w)
			{
				if (m_Maze.m_pTileSet[h][w].m_iType == 0)
				{
					generator.addCollision({ w,h });
				}
			}
		}

		generator.setHeuristic(AStar::Heuristic::octagonal);
//		generator.setDiagonalMovement(true);

		return true;
	}
	bool		Frame()
	{
		DWORD dwKey = I_Input.m_dwMouseState[0];
		if (dwKey == KEY_PUSH)
		{
			m_Maze.m_PathList.clear();
			Nodeindex TargetNode = m_Maze.getTargetIndex(I_Input.m_MousePos.x, I_Input.m_MousePos.y);
//			m_Maze.SelectPath(TargetNode);
			TargetNode = TargetNode * 2;
			TargetNode += 1;

			AStar::CoordinateList path = generator.findPath({ 0,0 }, TargetNode);
			for (auto pos : path)
			{
				m_Maze.m_PathList.push_back({ pos._x, pos._y });
			}
			std::reverse(m_Maze.m_PathList.begin(), m_Maze.m_PathList.end());
		}
		return true;
	}
	bool		Render()
	{
		m_Maze.Reset();
		m_Maze.RenderTile();
		m_Maze.RenderPath(true);
	//	m_Maze.RenderPath();
		m_Maze.Render();
		return true;
	}
	bool		Release()
	{
		return true;
	}
private:
	Maze			 m_Maze;
	AStar::Generator generator;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}