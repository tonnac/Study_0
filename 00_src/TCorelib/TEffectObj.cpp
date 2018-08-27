#include "TEffectObj.h"
#include "TInput.h"
#include "TSound.h"

bool TEffectObj::Frame()
{
	if (m_bDead) return true;
	m_fLifeTime -= g_fSecPerFrame;
	if (m_fLifeTime < 0.0f)
	{
		m_fLifeTime = 1.0f;
		m_bDead = true;
	}
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	//m_pos.x += m_fDir[0] * m_fSpeed * g_fSecPerFrame;
	m_pos.y -= m_fSpeed * g_fSecPerFrame;
	m_posDraw.x = m_pos.x - iHalfX;
	m_posDraw.y = m_pos.y - iHalfY;

	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;
	return true;
}
TEffectObj::TEffectObj()
{
	m_iSpriteIndex = 0;
	m_iCurrentRect = 0;
	m_fSpriteTime = 1.0f;
	m_fOffset = 1.0f;
	m_fLifeTime = 1.0f;
}


TEffectObj::~TEffectObj()
{
}

bool TEffectMgr::Render()
{
	m_fAngle += g_fSecPerFrame * 100.0f;
	for (int iObj = 0; iObj < m_EffectObj.size(); iObj++)
	{
		m_EffectObj[iObj].RotationBlt(m_fAngle);
	}
	return true;
}
bool TEffectMgr::IsCollision(RECT rt)
{
	for (int ieffect = 0; ieffect < m_EffectObj.size(); ieffect++)
	{
		if (TCollision::SphereInSphere(rt,
			m_EffectObj[ieffect].m_rtCollision))
		{				
			return true;
		}
	}
	return false;
}
bool TEffectMgr::GameDataLoad(const TCHAR* pszLoad)
{
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };

	int iNumSprite = 0;
	FILE* fp_src;
	_wfopen_s(&fp_src, pszLoad, _T("rt"));
	if (fp_src == NULL) return false;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s%d%s"), pTemp, _countof(pTemp), &iNumSprite);
	m_rtSpriteList.resize(iNumSprite);

	for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
	{
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, _countof(pTemp), &iNumFrame);
		//m_rtSpriteList[iCnt].resize(iNumFrame);

		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, _countof(pTemp),
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			m_rtSpriteList[iCnt].push_back(rt);
		}
	}
	fclose(fp_src);
	return true;
}
bool TEffectMgr::Release()
{
	for (int iObj = 0; iObj < m_EffectObj.size(); iObj++)
	{
		m_EffectObj[iObj].Release();
	}
	return true;
}
bool TEffectMgr::Frame()
{
	if (I_Input.Key(VK_LBUTTON))
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;
		if (fAddTime >= 0.1f)
		{
			AddEffect(g_pHeroPos);// I_Input.m_MousePos);
			TSound::Get()->PlayEffect(5);
			fAddTime -= 0.1f;
		}
	}

	for (int iObj = 0; iObj < m_EffectObj.size(); iObj++)
	{
		m_EffectObj[iObj].m_fOffset = 1.0f / m_rtSpriteList[m_EffectObj[iObj].m_iSpriteIndex].size();
		m_EffectObj[iObj].m_fSpriteTime += g_fSecPerFrame;
		if (m_EffectObj[iObj].m_fSpriteTime >= m_EffectObj[iObj].m_fOffset)
		{
			m_EffectObj[iObj].m_iCurrentRect++;
			if (m_EffectObj[iObj].m_iCurrentRect >= m_rtSpriteList[m_EffectObj[iObj].m_iSpriteIndex].size())
			{
				m_EffectObj[iObj].m_iCurrentRect = 0;
				//m_EffectObj[iObj].m_iSpriteIndex = (++m_EffectObj[iObj].m_iSpriteIndex >= m_rtSpriteList.size()) ? 0 : m_EffectObj[iObj].m_iSpriteIndex;
			}
			m_EffectObj[iObj].m_fSpriteTime -= m_EffectObj[iObj].m_fOffset;
		}
		RECT rt = m_rtSpriteList[m_EffectObj[iObj].m_iSpriteIndex][m_EffectObj[iObj].m_iCurrentRect];
		m_EffectObj[iObj].m_rtDraw = rt;
		m_EffectObj[iObj].Frame();
	}
	
	return true;
}
void TEffectMgr::AddEffect(POINT pos)
{
	TEffectObj obj;
	obj.Init();
	obj.Set(pos.x, pos.y, 1, 142, 41, 41);
	obj.Load(
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp");
	obj.m_iSpriteIndex = rand() % m_rtSpriteList.size();
	obj.m_fSpeed = 1000.0f;
	m_EffectObj.push_back(obj);
}
TEffectMgr::TEffectMgr()
{
	m_fAngle = 0.0f;
}
TEffectMgr::~TEffectMgr()
{

}