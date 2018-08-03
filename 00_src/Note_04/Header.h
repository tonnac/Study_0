#pragma once
template <class K>
struct Node
{
	K m_kData;
	Node * m_pNext;
};

template <class K>
class List
{
private:
	Node<K> * m_pHead;
	Node<K> * m_pTail;
public:
	List()
	{
		m_pHead = nullptr;
		m_pTail = nullptr;
	}
	~List()
	{
		Node<K>* temp = m_pHead;
		Node<K>* tempp = temp;
		while (temp != nullptr)
		{
			tempp = temp->m_pNext;
			delete temp;
			temp = tempp;
		}
	}
	Node<K>* begin()
	{
		return m_pHead;
	}
	Node<K>* end()
	{
		return m_pTail->m_pNext;
	}
	void push_back(Node<K> * nNode)
	{
		if (m_pHead == nullptr)
		{
			m_pHead = m_pTail = nNode;
		}
		else
		{
			m_pTail->m_pNext = nNode;
			m_pTail = nNode;
		}
	}
	void push_back(const K& Data)
	{
		Node<K> * newNode = new Node<K>;
		newNode->m_kData = Data;
		newNode->m_pNext = nullptr;
		if (m_pHead == nullptr)
		{			
			m_pHead = m_pTail = newNode;
		}
		else
		{
			m_pTail->m_pNext = newNode;
			m_pTail = newNode;
		}
	}

private:
	template <class K>
	class slist_iterator
	{
	private:
		Node<K>* current;
	public:
		slist_iterator(Node<K>* p = nullptr) : current(p)
		{}
		slist_iterator& operator ++ (int m)
		{
			current = current->m_pNext;
			return *this;
		}
		K& operator *()
		{
			return current->m_kData;
		}
		bool operator != (const slist_iterator& p) { return *this == p; }
		bool operator != (Node<K>* ep) { return current != ep; }
		bool operator == (const slist_iterator& p) { return !(current == p); }
	};
public:
	using iterator = slist_iterator<K>;
};
