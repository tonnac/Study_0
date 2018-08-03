#pragma once
namespace Iterator
{
	template <class K>
	class IContainer
	{
	public:
		virtual bool Add(K elem) = 0;
		virtual void Remove(K elem) = 0;
		virtual void Clear() = 0;
		int m_iCount;
	};

	template <class K>
	class IIterator
	{
	public:
		virtual void Begin() = 0;
		virtual bool MoveNext() = 0;
		K Current;
	};

	template <class K>
	class Arr : public IContainer<K>
	{
		K* buffer;
		int max_element;
		int Find(K elem)
		{
			for (int i = m_iCount; i < max_element; i++)
			{
				if (buffer[i] == elem)
					return 1;
			}
			return -1;
		}
	public:
		Arr<K>(int me)
		{
			this->max_element = me;
			buffer = new K(max_element);
		}

		bool push_back(K elem)
		{
			if (m_iCount < max_element)
			{
				buffer[m_iCount] = elem;
				m_iCount++;
				return true;
			}
			return false;
		}

		void erase(K elem)
		{
			int index = Find(elem);
			if (index == -1)
			{
				return;
			}
			m_iCount--;
			for (int i = index; i < m_iCount; i++)
			{
				buffer[i] = buffer[i + 1];
			}
		}
		void Clear()
		{
			m_iCount = 0;
		}
	};
}