#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

class TStudent
{
public:
	int m_iIndex;
//	std::string m_szName;
	int m_iType = 0;
	TStudent(int iData)
	{
		std::cout << "11" << std::endl;
		m_iIndex = iData;
		m_iType = 0;
	}
	//TStudent(std::string name)
	//{
	//	m_szName = name;
	//	m_iType = 1;
	//}
	//bool operator() (TStudent * data)		//연산자 재정의된 함수 호출
	//{
	//	if (m_iType == 0)
	//	{
	//		return (data->m_iIndex == m_iIndex);
	//	}
	//	else if (m_iType == 1)
	//	{
	//		return (data->m_szName == m_szName);
	//	}
	//}
	//bool operator < (TStudent * data)		//연산자 재정의된 함수 호출
	//{
	//	if (m_iType == 0)
	//	{
	//		return (data->m_iIndex < m_iIndex);
	//	}
	//	//else if (m_iType == 1)
	//	//{
	//	//	return (data->m_szName == m_szName);
	//	//}
	//}
	~TStudent()
	{
		std::cout << "삭제" << std::endl;
	}
};
//
//TStudent* g_Data;
//
//void add(std::vector<TStudent*>& data)
//{
//	for (int i = 0; i < 10; i++)
//	{
//		TStudent * pData = new TStudent(i);
//		data.push_back(pData);
//		if (i == 5)
//		{
//			g_Data = pData;
//		}
//		
//	}
//}
//void del(std::vector<TStudent*>& copy)
//{
//	for (int i = 9; i >= 0; i--)
//	{
//		TStudent * data = copy[i];
//		delete data;
//		copy.pop_back();
//	}
//}
//bool check(TStudent * data)
//{
//	if (data->m_iIndex == 5)
//	{
//		return true;
//	}
//	return false;
//}
//bool check(TStudent * a, TStudent * b)
//{
//	if (a->m_iIndex > b->m_iIndex)
//	{
//		return true;
//	}
//	return false;
//}
//template <typename T>
//class TCheck
//{
//public:
//	TCheck(int m) : m_iFind(m)
//	{}
//	bool operator() (T data)		//연산자 재정의된 함수 호출
//	{
//		return data->m_iIndex == m_iFind;
//	}
//private:
//	int m_iFind;
//};

void Sow(TStudent Data)
{
	std::cout << &Data << std::endl;
}

int main()
{
	Sow(TStudent(5));

//	std::list<int> qwe;

//	qwe.resize(9);

//	std::vector<TStudent*> data;
//	add(data);
//	TCheck<TStudent*> checkptr(5);

/*	std::vector<TStudent*>::iterator iter = 
		find_if(data.begin(), 
		data.end(), 
		checkptr);  */				// 객체로 넘겨줘도 함수호출


	//std::list<TStudent*>::reverse_iterator   뒤에서부터 앞으로오는 iterator
	//for(iter = *.rbegin();
	//	iter != *.rend();
	//	iter++)
	////ee.sort();
//	std::cout << std::endl << std::endl;

//	std::vector<TStudent*>::iterator iter =	find_if(data.begin(),data.end(),TStudent(5));

//	del(data);
//	data.clear();

	//std::vector<TStudent> intArray;
	//std::vector<TStudent>::iterator iter;
	//int iFind = 5;
	//for (int i = 0; i < 15; i++)
	//{
	//	TStudent a;
	//	a.m_iIndex = i;
	//	intArray.push_back(a);
	//	intArray.insert(
	//		intArray.begin(), 
	//		a);
	//	/*if (i == iFind)
	//	{
	//		iter = intArray.begin();
	//	}*/
	//}
	//TStudent a;
	//a.m_iIndex = 20;
	//intArray.insert(
	//	intArray.begin(),
	//	a);

	//for (iter = intArray.begin();
	//	iter != intArray.end(); 
	//	iter++)
	//{
	//	TStudent a = *iter;
	//	std::cout << a.m_iIndex;
	//}

	//for (int i = 0; i < intArray.size(); i++)
	//{
	//	TStudent a = intArray[i];
	//	std::cout << a.m_iIndex;
	//	if (i != intArray.size() - 1)
	//	{
	//		std::cout << ",";
	//	}
	//}

	return 0;
}