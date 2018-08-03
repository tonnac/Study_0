#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
#include <functional>		// 함수객체
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

void PRINTER(TStudent * pData)				//인자를 늘리고싶다.
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
//	std::set 중복 입력 불가.
	//std::set<int> setList;

	//setList.insert(5);
	//setList.insert(5);
	//setList.insert(4);
	//setList.insert(4);
	//imCnt = setList.size();
	//imCnt = setList.count(2);				//  있는지 없는지만 찾는다.

	//setList.erase(4);

	//setList.clear();

	////////////////////////////////////////////////////////////////////

//	std::multiset 중복입력가능, 자동 정렬
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
////		std::cout << msetList[i];			 // 인덱싱 지원이 안됨
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
//		PRINTER(*iter);					// 인자에 const
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
	////		std::cout << msetList[i];			 // 인덱싱 지원이 안됨
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
	//	std::mem_fun_ref(&TStudent::print));   //대상이 포인터가 아니면 _ref사용
	//										   //set,multiset은 안된다.
	//TData data;
	//data.a = 1;
	//data.b = 2;
	//data.c = 3;
	//for_each(setList.begin(),
	//	setList.end(),
	//	std::bind2nd(std::mem_fun(&TStudent::printWithString),data)); // 함수의 인자 1개를 늘린다.
	//																  // 여러개 받고 싶으면 클래스를 넣어주자
	//for_each(setList.begin(),
	//	setList.end(),
	//	PRINTER);

	////////////////////////////////////////////////////////////////////

	//std::list<int> coll;										//std::list<int> coll(5) 만들고 generate쓰는게 일반적
	//std::generate_n(std::front_inserter(coll), 10, intData(1)); //generate로 컨테이너에 데이터 넣기
	//std::generate_n(std::front_inserter(coll), 10, setData);	//for_each와 유사 but 함수의 리턴값이 존재해야함
	//std::generate(coll.begin(), coll.end(), setData);
	//std::generate(coll.begin(), coll.end(), intData(2));

	////////////////////////////////////////////////////////////////////

	// 사전식 자료관리
	// PAIR = 인덱스 키+값
	//std::map<int, std::string> mapList;
	//mapList.insert(std::make_pair(0, "qqq"));   // 짝을지어줘서 insert
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
	//	int iValue = iter->second;  // second에 클래스가 일반적
	//	std::cout << "[" <<iKey << ", " << iValue << "]" << std::endl;
	//}
	//
	//std::cout << std::endl;

	//for (int iCnt=0; iCnt<intmapList.size(); iCnt++)
	//{
	//	std::cout << intmapList[iCnt] << std::endl;   // 인덱싱은 키값 확인못함
	//}

	return 0;
}