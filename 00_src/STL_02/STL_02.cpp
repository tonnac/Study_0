#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
#include <functional>		// �Լ���ü
#include <string>
#include <iterator>

struct TData
{
	int a;
	int b;
	int c;
};
class TStudent
{
public:
	int m_iValue;
	TStudent(int iValue) : m_iValue(iValue) {}
	void print() 
	{ 
		std::cout << m_iValue; 
	}
	void printWithString(TData data)
	{
		std::cout << m_iValue << data.a;
	}
};

void PRINTER(TStudent * pData)				//���ڸ� �ø���ʹ�.
{
	std::cout << pData->m_iValue;
}

class intData
{
public:
	int m_iValue;
	intData(int value) : m_iValue(value) {}
	int operator() ()
	{
		return m_iValue += 4;
	}
};

int setData()
{
	static int m_iValue = 0;
	return m_iValue += 5;
}

void getData(int iValue)
{
	std::cout << iValue << " ";
}

int main()
{
//	std::set �ߺ� �Է� �Ұ�.
	//std::set<int> setList;

	//setList.insert(5);
	//setList.insert(5);
	//setList.insert(4);
	//setList.insert(4);
	//imCnt = setList.size();
	//imCnt = setList.count(2);				//  �ִ��� �������� ã�´�.

	//setList.erase(4);

	//setList.clear();

	////////////////////////////////////////////////////////////////////

//	std::multiset �ߺ��Է°���, �ڵ� ����
//	std::multiset<int> setList;
//
//	setList.insert(5);
//	setList.insert(5);
//
//	size_t imCnt = setList.size();
//
//	setList.insert(4);
//	setList.insert(1);
//
//	imCnt = setList.size();
//	imCnt = setList.count(2);
//
////	for (int i = 0; i < imCnt; i++)
////	{
////		std::cout << msetList[i];			 // �ε��� ������ �ȵ�
////	}
//
//	for_each(setList.begin(), 
//			 setList.end(), 
//			 bind2nd(PRINTER,100));
//
//
//	std::multiset<int>::const_iterator iter;
//
//	for (iter = setList.cbegin();	    // const begin,end
//		iter != setList.cend(); 
//		iter++)
//	{
////		std::cout << *iter;			
//		PRINTER(*iter);					// ���ڿ� const
//	}
//	
//	setList.insert(2);
//	setList.insert(3);
//
//	imCnt = setList.size();
//
//	setList.insert(3);
//	setList.insert(3);
//	
//	setList.erase(3);
//
//	setList.clear();

	////////////////////////////////////////////////////////////////////

	//std::multiset<TStudent*> setList;

	//setList.insert(new TStudent(3));
	//setList.insert(new TStudent(1));
	//setList.insert(new TStudent(2));
	//setList.insert(new TStudent(5));
	//setList.insert(new TStudent(6));
	//setList.insert(new TStudent(7));
	//setList.insert(new TStudent(8));



	////	for (int i = 0; i < imCnt; i++)
	////	{
	////		std::cout << msetList[i];			 // �ε��� ������ �ȵ�
	////	}
	//for_each(setList.begin(),
	//	setList.end(),
	//	std::mem_fun(&TStudent::print));

	//std::vector<TStudent> mrefList;
	//TStudent a(3);
	//TStudent b(4);
	//TStudent c(5);
	//mrefList.push_back(a);
	//mrefList.push_back(b);
	//mrefList.push_back(c);

	//for_each(mrefList.begin(),
	//	mrefList.end(),
	//	std::mem_fun_ref(&TStudent::print));   //����� �����Ͱ� �ƴϸ� _ref���
	//										   //set,multiset�� �ȵȴ�.
	//TData data;
	//data.a = 1;
	//data.b = 2;
	//data.c = 3;
	//for_each(setList.begin(),
	//	setList.end(),
	//	std::bind2nd(std::mem_fun(&TStudent::printWithString),data)); // �Լ��� ���� 1���� �ø���.
	//																  // ������ �ް� ������ Ŭ������ �־�����
	//for_each(setList.begin(),
	//	setList.end(),
	//	PRINTER);

	////////////////////////////////////////////////////////////////////

	//std::list<int> coll;										//std::list<int> coll(5) ����� generate���°� �Ϲ���
	//std::generate_n(std::front_inserter(coll), 10, intData(1)); //generate�� �����̳ʿ� ������ �ֱ�
	//std::generate_n(std::front_inserter(coll), 10, setData);	//for_each�� ���� but �Լ��� ���ϰ��� �����ؾ���
	//std::generate(coll.begin(), coll.end(), setData);
	//std::generate(coll.begin(), coll.end(), intData(2));

	////////////////////////////////////////////////////////////////////

	// ������ �ڷ����
	// PAIR = �ε��� Ű+��
	//std::map<int, std::string> mapList;
	//mapList.insert(std::make_pair(0, "qqq"));   // ¦�������༭ insert
	//mapList.insert(std::make_pair(1, "www"));   
	//mapList.insert(std::make_pair(2, "eee"));   

	////////////////////////////////////////////////////////////////////

	std::map<int, int> intmapList;
	for (int i = 0; i < 100000000; i++)
	{
		intmapList.insert(std::make_pair(i,rand()%1000));
	}
	std::map<int, int>::iterator iter;
	iter = intmapList.find(940000);
	if (iter != intmapList.end())
	{
		int iKey = iter->first;
		int iValue = iter->second; 
		std::cout << "[" <<iKey << ", " << iValue << "]" << std::endl;
	}
	//for (iter = intmapList.begin(); iter != intmapList.end(); iter++)
	//{
	//	int iKey = iter->first;
	//	int iValue = iter->second;  // second�� Ŭ������ �Ϲ���
	//	std::cout << "[" <<iKey << ", " << iValue << "]" << std::endl;
	//}
	//
	//std::cout << std::endl;

	//for (int iCnt=0; iCnt<intmapList.size(); iCnt++)
	//{
	//	std::cout << intmapList[iCnt] << std::endl;   // �ε����� Ű�� Ȯ�θ���
	//}

	return 0;
}