#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"
#include <memory>

#define PI 3.141592
#define DegreetoRadian(x) (x) * PI / 180.0f;

class KSample : public KCore
{
	std::shared_ptr<Scene>				m_pGameScene;
	KObject								m_tmpObj;
	HBRUSH								m_hbkBrush;
	HBITMAP								m_hColorRotateBitmap;
	HBITMAP								m_hMaskRotateBitmap;
	HDC									m_hRotationDC;
	HDC									m_hMemMaskDC;
	HDC									m_hMemColorDC;
	float								m_fMaxDistance;

public:
	bool Init()
	{
		m_hbkBrush = CreateSolidBrush(RGB(0, 255, 0));

		m_fMaxDistance = (m_tmpObj.m_rtDraw.right) * (m_tmpObj.m_rtDraw.right) +
			(m_tmpObj.m_rtDraw.bottom) * (m_tmpObj.m_rtDraw.right);

		m_hColorRotateBitmap = CreateCompatibleBitmap(m_hOnScreenDC, m_fMaxDistance, m_fMaxDistance);
		m_hMaskRotateBitmap = CreateCompatibleBitmap(m_hOnScreenDC, m_fMaxDistance, m_fMaxDistance);

		m_hRotationDC = CreateCompatibleDC(m_hOnScreenDC);
		m_hMemMaskDC = CreateCompatibleDC(m_hOnScreenDC);
		m_hMemColorDC = CreateCompatibleDC(m_hOnScreenDC);

		m_tmpObj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_tmpObj.Set(300, 300, 133, 1, 42, 59);
				
		m_pGameScene = std::make_shared<SceneGame>();

		m_tmpObj.Init();
		m_pGameScene->Init();
		return true;
	}
	bool Frame()
	{
		static float fAngle = 0.0f;
		fAngle += g_fSecPerFrame * 100.0f;
		RotateBlt(fAngle, m_hMaskRotateBitmap, m_tmpObj.m_MaskBitmap);
		RotateBlt(fAngle, m_hColorRotateBitmap, m_tmpObj.m_ColorBitmap);

		m_pGameScene->Frame();
		m_tmpObj.Frame();
		return true;
	}
	bool Render()
	{
		HBITMAP hOldMask = static_cast<HBITMAP>(SelectObject(m_hMemMaskDC, m_hMaskRotateBitmap));
		HBITMAP hOldColor = static_cast<HBITMAP>(SelectObject(m_hMemColorDC, m_hColorRotateBitmap));
		BitBlt(g_hOffScreenDC,
			m_tmpObj.m_CenterPos.x - (m_fMaxDistance / 2),
			m_tmpObj.m_CenterPos.y - (m_fMaxDistance / 2),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCAND);
		BitBlt(g_hOffScreenDC,
			m_tmpObj.m_CenterPos.x - (m_fMaxDistance / 2),
			m_tmpObj.m_CenterPos.y - (m_fMaxDistance / 2),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemColorDC,
			0, 0,
			SRCINVERT);
		BitBlt(g_hOffScreenDC,
			m_tmpObj.m_CenterPos.x - (m_fMaxDistance / 2),
			m_tmpObj.m_CenterPos.y - (m_fMaxDistance / 2),
			m_fMaxDistance,
			m_fMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCINVERT);
		SelectObject(m_hMemMaskDC, hOldMask);
		SelectObject(m_hMemColorDC, hOldColor);
//		m_pGameScene->Render();
		return true;
	}
	bool Release()
	{
		return true;
	}
	void RotateBlt(float fAngle, HBITMAP hBitmap, Bitmap* pSrcBitmap)
	{
		float fRadian = DegreetoRadian(fAngle);
		float fCosine = cos(fRadian);
		float fSine = sin(fRadian);

		HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hRotationDC, m_hbkBrush));
		HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(m_hRotationDC, hBitmap));
		
		PatBlt(m_hRotationDC, 0, 0, m_fMaxDistance, m_fMaxDistance, PATCOPY);
		SelectObject(m_hRotationDC, hOldBrush);

		int iOldGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);

		XFORM xform;
		xform.eM11 = fCosine;			xform.eM12 = -fSine;
		xform.eM21 = fSine;				xform.eM22 = fCosine;
		xform.eDx = m_fMaxDistance / 2;	xform.eDy = m_fMaxDistance / 2;

		SetWorldTransform(m_hRotationDC, &xform);


		BitBlt(m_hRotationDC, -(m_tmpObj.m_rtDraw.right / 2), -(m_tmpObj.m_rtDraw.bottom / 2),
			m_tmpObj.m_rtDraw.right, m_tmpObj.m_rtDraw.bottom, pSrcBitmap->m_hMemDC,
			m_tmpObj.m_rtDraw.left, m_tmpObj.m_rtDraw.top, SRCCOPY);

		xform.eM11 = 1;			xform.eM12 = 0;
		xform.eM21 = 0;			xform.eM22 = 1;
		xform.eDx = 0;			xform.eDy = 0;

		SetWorldTransform(m_hRotationDC, &xform);
		SetGraphicsMode(m_hRotationDC, iOldGraphic);
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