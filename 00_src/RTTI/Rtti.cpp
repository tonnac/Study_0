#include <iostream>
#include <typeinfo.h>
#include <conio.h>
#include <vector>
#include <queue>

#define STRING(S) #S		// #스트링화 연산자
#define LINK(i,j) i##j		// ##연결 연산자

#define DECLARE_CLASSNAME static char lpszClassName[]
#define IMPLEMENT_CLASSNAME(s) char s##::lpszClassName[] = #s
#define RUNTIME_CLASS(s) &(s::class##s)

#define DECLARE_DYNAMIC(s) static CRuntimeClass class##s
#define DECLARE_DYN_CREATE static CObject* CreateObject()
#define IMPLEMENT_DYN_CREATE(s) CObject* s::CreateObject() { return new s;}
#define IMPLEMENT_DYNAMIC(s) CRuntimeClass s::class##s = { #s, sizeof(s), s::CreateObject }
//&(CUser::classCUser);

class CObject;
struct CRuntimeClass
{
	char m_lpszClassName[21];
	int  m_iObjectSize;
	CObject* (*pfnCreateObject)();
	CObject* CreateObject()
	{
		return (*pfnCreateObject)();
	}
};

class CObject 
{
public:
	DECLARE_CLASSNAME;
	static CRuntimeClass classCObject;
	virtual char* GetClassName() const
	{
		return NULL;
	}
	virtual ~CObject() {}
protected:
	CObject() {}
};

CRuntimeClass CObject::classCObject = {"CObject", sizeof(CObject), nullptr};
IMPLEMENT_CLASSNAME(CObject);

//---------------------------------------------------------------------------

class SessionMgr
{
public:
	std::queue<CObject*> m_userlist;
	static std::queue<CObject*> m_staticlist;
	void Create(CRuntimeClass* pRTC)
	{
		for (int iQueue = 0; iQueue < 1000; ++iQueue)
		{
			CObject* pObj = pRTC->CreateObject();
			m_userlist.push(pObj);
		}
	}
	CObject* CreateNewSession()
	{
		CObject* newSession = m_staticlist.front();
		m_staticlist.pop();
		m_userlist.push(newSession);
		return newSession;
	}
	void RemoveSession(CObject* pSession)
	{
		//m_userlist. 유저리스트에서 찾고
		m_staticlist.push(pSession); // 넣어준다.
	}
};

SessionMgr g_SessionMgr;

class CMyclass : public CObject 
{
public:
	DECLARE_CLASSNAME;
	DECLARE_DYN_CREATE;
	DECLARE_DYNAMIC(CMyclass);
	virtual char* GetClassName() const
	{
		return lpszClassName;
	}
};
IMPLEMENT_DYNAMIC(CMyclass);
IMPLEMENT_CLASSNAME(CMyclass);
IMPLEMENT_DYN_CREATE(CMyclass);
//static CObject* CreateObject()


int main(void)
{
	g_SessionMgr.Create(RUNTIME_CLASS(CMyclass));
	CObject* p = g_SessionMgr.m_userlist.back();
	//CObject* p = pRTCMyClass->CreateObject();
	//CMyclass * pChild = (CMyclass*)p;
	std::cout << p->GetClassName() << std::endl;
	delete p;
#pragma region LINK & STRING
	std::cout << STRING(adasd) << std::endl;
	char m_szValue[] = "KGCAGAME";
	std::cout << LINK(m_sz, Value) << std::endl;
	int LINK(m_i, Data) = 0;
#pragma endregion
#pragma region TypeInfo
	//CBase parent;
	//CChild child;
	//const type_info& tBase = typeid(parent);
	//const type_info& tChild = typeid(child);

	//std::cout << tBase.name() << "{}" << std::endl;
	//std::cout << typeid(parent).name() << std::endl;

	//std::cout << tChild.name() << std::endl;
	//std::cout << typeid(child).name() << std::endl;

	//std::cout << tBase.before(tChild) << std::endl;
	//std::cout << tChild.before(tBase) << std::endl;
	//std::cout << (tChild == tBase) << std::endl;
#pragma endregion
	_getch();
	return 0;
}