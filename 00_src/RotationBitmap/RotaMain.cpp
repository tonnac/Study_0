#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"
#include <memory>

class KSample : public KCore
{
	std::shared_ptr<Scene>  m_pGameScene;
	KObject					m_tmbobj;
	HBITMAP					m_hColorRotateBitmap;
	HBITMAP					m_hMaskRotateBitmap;
	HDC						m_hRotationDC;
	HDC						m_hMemMaskDC;
	HDC						m_hMemColorDC;
	HBITMAP					m_hOldBitmap;
	float					m_fMaxDistance;
public:
	bool Init()
	{
		m_fMaxDistance = sqrt(m_tmbobj.m_rtDraw.right * m_tmbobj.m_rtDraw.right +
			m_tmbobj.m_rtDraw.bottom * m_tmbobj.m_rtDraw.bottom);

		m_hColorRotateBitmap = CreateCompatibleBitmap(m_hOnScreenDC, m_fMaxDistance, m_fMaxDistance);
		m_hMaskRotateBitmap = CreateCompatibleBitmap(m_hOnScreenDC, m_fMaxDistance, m_fMaxDistance);

		m_hRotationDC = CreateCompatibleDC(m_hOnScreenDC);
		m_hMemMaskDC = CreateCompatibleDC(m_hOnScreenDC);
		m_hMemColorDC = CreateCompatibleDC(m_hOnScreenDC);

		m_tmbobj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_tmbobj.Set(500, 500, 133, 1, 42, 59);
		m_tmbobj.Init();
		m_pGameScene = std::make_shared<SceneGame>();

		m_pGameScene->Init();
		return true;
	}
	void RotateBlt(float fAngle, HBITMAP hBitmap, Bitmap* pSrcBitmap)
	{
		float fRadian = fAngle * 3.141592f / 180.0f;
		float fCosine = cos(fRadian);
		float fSine = sin(fRadian);

		HBRUSH hbrBack = CreateSolidBrush(RGB(255, 0, 0));
		m_hOldBitmap = (HBITMAP)SelectObject(m_hRotationDC, hBitmap);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hRotationDC, hbrBack);
		PatBlt(m_hRotationDC, 0, 0, m_fMaxDistance, m_fMaxDistance, PATCOPY);
		DeleteObject(SelectObject(m_hRotationDC, hOldBrush));

		int iOldGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);

		XFORM xform;
		xform.eM11 = fCosine;			 xform.eM12 = -fSine;
		xform.eM21 = fSine;				 xform.eM22 = fCosine;
		xform.eDx  = m_fMaxDistance / 2; xform.eDy = m_fMaxDistance /2;

		SetWorldTransform(m_hRotationDC, &xform);

		BitBlt(m_hRotationDC, -(m_tmbobj.m_rtDraw.right / 2), -(m_tmbobj.m_rtDraw.bottom / 2),
			m_tmbobj.m_rtDraw.right, m_tmbobj.m_rtDraw.bottom,
			pSrcBitmap->m_hMemDC, m_tmbobj.m_rtDraw.left, m_tmbobj.m_rtDraw.top, SRCCOPY);

		xform.eM11 = 1;			 xform.eM12 = 0;
		xform.eM21 = 0;			 xform.eM22 = 1;
		xform.eDx = 0;			 xform.eDy = 0;
		SetWorldTransform(m_hRotationDC, &xform);
		SetGraphicsMode(m_hRotationDC, iOldGraphic);
	}
	bool Frame()
	{
		static float fAngle = 0.0f;
		fAngle += g_fSecPerFrame * 100.0f;
		RotateBlt(fAngle, m_hMaskRotateBitmap, m_tmbobj.m_MaskBitmap) ;
		RotateBlt(fAngle, m_hColorRotateBitmap, m_tmbobj.m_ColorBitmap);

		m_pGameScene->Frame();
		m_tmbobj.Frame();
		return true;
	}
	bool Render()
	{
		SelectObject(m_hMemMaskDC, m_hMaskRotateBitmap);
		SelectObject(m_hMemColorDC, m_hColorRotateBitmap);
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_tmbobj.m_CenterPos.x - (m_fMaxDistance / 2)),
			static_cast<int>(m_tmbobj.m_CenterPos.y - (m_fMaxDistance / 2)),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCAND);
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_tmbobj.m_CenterPos.x - (m_fMaxDistance / 2)),
			static_cast<int>(m_tmbobj.m_CenterPos.y - (m_fMaxDistance / 2)),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemColorDC,
			0, 0,
			SRCINVERT);
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_tmbobj.m_CenterPos.x - (m_fMaxDistance / 2)),
			static_cast<int>(m_tmbobj.m_CenterPos.y - (m_fMaxDistance / 2)),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCINVERT);
//		m_pGameScene->Render();
//		m_tmbobj.Render();
		return true;
	}
	bool Release()
	{
		m_tmbobj.Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst, 800, 600);
	wd.Run();
	return 0;
}