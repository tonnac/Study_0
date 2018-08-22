#include "BKObject.h"
#include "Rendering.h"
#include "TerrainObject.h"
#include "Collision.h"
#include "Player.h"
#include "ScrollObject.h"
#include "PlatObject.h"

BKObject::BKObject()
{
	m_pObjList.clear();
	m_pPlatList.clear();
}

//bool BKObject::Init()
//{
//	m_pRendering = New Rendering(this);
//	return true;
//}
bool BKObject::Frame()
{
	for (auto it : m_pObjList)
	{
		it->Frame();
	}
	if (!m_pPlatList.empty())
	{
		for (auto iter : m_pPlatList)
		{
			iter->Frame();
		}
	}
	return Object::Frame();

}

bool BKObject::Render()
{
	Object::Render();


	if (isDebugMode)
	{
		for (auto it : m_pObjList)
		{
			it->Render();
		}
	}
	if (!m_pPlatList.empty())
	{
		for (auto iter : m_pPlatList)
		{
			iter->Render();
		}
	}
	return true;
}
bool BKObject::Release()
{
	if (!m_pPlatList.empty())
	{
		for (auto iter : m_pPlatList)
		{
			iter->Release();
			delete iter;
		}
	}
	for (auto it : m_pObjList)
	{
		it->Release();
		delete it;
	}
	m_pObjList.clear();
	Object::Release();
	return true;
}
bool BKObject::MoveScrollBk(const LONG& fsize)
{
//	m_fScroll = m_rtDraw.left;
	for (auto it : m_pObjList)
	{
		it->MoveScrollObj(fsize);
	}
	if (!m_pPlatList.empty())
	{
		for (auto iter : m_pPlatList)
		{
			iter->MoveScrollObj(fsize);
		}
	}
	if (fsize < 0)
	{
		m_fScroll += -(g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}
	else
	{
		m_fScroll += (g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}

	return true;
}
void BKObject::AddTerrain(TerrainObject * m_ptObject)
{
	m_pObjList.push_back(m_ptObject);
}
void BKObject::AddPlat(PlatObject * m_pObject)
{
	m_pPlatList.push_back(m_pObject);
}
bool BKObject::Collision(Object* pObject)
{
	CharacterObject * pCharObj = dynamic_cast<CharacterObject*>(pObject);
	bool isLanding = false;
	for (auto it : m_pObjList)
	{
		if (it->Collision(pObject))
		{
			isLanding = true;
		}
		bool flag = pCharObj->isFallState();
		if (flag == false)
		{
			RECT ObjRT = *pObject->getCollisionRt();
			RECT rtrt = *it->getCollisionRt();
			RECT faRT = { ObjRT.left + 27, ObjRT.bottom, ObjRT.right - 27, ObjRT.bottom + 10 };
			if (CollisionClass::RectInRect(faRT, rtrt))
			{
				isLanding = true;
			}
		}
	}
	for (auto iter : m_pPlatList)
	{
		if (iter->Collision(pObject))
		{
			isLanding = true;
		}
		bool flag = pCharObj->isFallState();
		if (flag == false)
		{
			RECT ObjRT = *pObject->getCollisionRt();
			RECT rtrt = *iter->getCollisionRt();
			RECT faRT = { ObjRT.left + 27, ObjRT.bottom, ObjRT.right - 27, ObjRT.bottom + 10 };
			if (CollisionClass::RectInRect(faRT, rtrt))
			{
				isLanding = true;
			}
		}
	}
	pObject->setLanding(isLanding);
	return Frame();
}
void BKObject::ReverseSet()
{
	for (auto it : m_pObjList)
	{
		it->ReverseSet(m_rtDraw.right - g_rtClient.right);
	}
	m_rtDraw.left += m_rtDraw.right - g_rtClient.right;
	m_fScroll = m_rtDraw.left;
}