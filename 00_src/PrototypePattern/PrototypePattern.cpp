#include <iostream>
#include <list>
#include <map>
class Position
{
public:
	Position() {}
	Position(int ix, int iy) : m_iposx(ix), m_iposy(iy)
	{}
	int m_iposx;
	int m_iposy;
};
class Graphic 
{
public:
	virtual Graphic * clone() = 0;
	virtual void Draw(Position pos) = 0;
};
class Triangle : public Graphic 
{
	Graphic * clone()
	{
		return new Triangle(*this);
	}
	void Draw(Position pos)
	{
		std::cout << "[ " << pos.m_iposx << ", " << pos.m_iposy << " ]";
	}
};
class Rectangle : public Graphic 
{
	Graphic * clone()
	{
		return new Rectangle(*this);
	}
	void Draw(Position pos)
	{
		std::cout << "[ " << pos.m_iposx << ", " << pos.m_iposy << " ]";
	}
};
class GraphicComposite : public Graphic 
{
public:
	std::list<Graphic*> m_Components;
	Graphic * clone()
	{
		GraphicComposite * pGc = new GraphicComposite(*this);
		
		std::list<Graphic*>::iterator itersrc;
		std::list<Graphic*>::iterator iterdes;
		iterdes = pGc->m_Components.begin();
		for (itersrc = m_Components.begin(); itersrc != m_Components.end(); itersrc++)
		{
			Graphic * pNewgraphic = (*itersrc)->clone();
			pGc->m_Components.push_back(pNewgraphic);
			//*iterdes = pNewgraphic;
			//iterdes++;
		}
		return pGc;
	}
	void Draw(Position pos)
	{
		std::cout << "[ " << pos.m_iposx << ", " << pos.m_iposy << " ]";
	}
};

class Mouse
{
public:
	Position m_pos;
	bool	 m_bButton[3];
	bool IsLeftButtonPushed()
	{
		return m_bButton[0];
	}
	Position GetPosition()
	{
		return m_pos;
	}
};
Mouse m_Mouse;

class Document
{
public:
	std::list<Graphic*> m_docList;
public:
	void Add(Graphic* pObj) 
	{
		m_docList.push_back(pObj);
	}
};
class GraphicEditor
{
public:
	Document m_doc;
public:
	void AddNewGraphics(Graphic * pSelected)
	{
		Graphic * obj = pSelected->clone();
		while (m_Mouse.IsLeftButtonPushed())
		{
			obj->Draw(m_Mouse.GetPosition());
		}
		m_doc.Add(obj);
	}
private:
};
class Palette {
private:
	std::map<int, Graphic*> m_items;
public:
	void Draw() {}
	Palette()
	{
		//원시 모델
		Graphic * pGraphic = new Triangle;
		m_items[0] = pGraphic;
		Graphic * pGraphic1 = new Rectangle;
		m_items[1] = pGraphic1;
	}
	//원시모델 추가등록
	void RegisterNewGraphic(Graphic * pGraphic)
	{
		m_items[m_items.size() + 1] = pGraphic;
	}

	Graphic * GetSelectedObj()
	{
		return m_items[GetItemOrder()];
	}
	int GetItemOrder()
	{
		int iItem = -1;
		//Collistion(m_Mouse.GetPosition());
		return iItem;
	}
};

int main(void)
{
	Palette pt;
	pt.Draw();
	GraphicEditor editer;
	editer.AddNewGraphics(pt.GetSelectedObj());
	GraphicComposite etc;
	std::list<Graphic*>::iterator iter;
	for (iter = editer.m_doc.m_docList.begin(); iter != editer.m_doc.m_docList.end(); iter++)
	{
		Graphic * pData = (*iter);
		etc.m_Components.push_back(pData);
	}
	pt.RegisterNewGraphic(&etc);
	/*Triangle tri;
	Rectangle rec;
	GraphicComposite etc;
	etc.m_Components.push_back(&tri);
	etc.m_Components.push_back(&rec);
	pt.RegisterNewGraphic(&etc);*/


	return 0;
}