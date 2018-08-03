#include "DataStructure.h"
#include <iostream>

template <class K>
bool stackpush<K>::Push(DataStructure<K> * pDs, const K& data)
{
	if (pDs->m_iIndex > pDs->LEN - 2)
	{
		std::cout << "overflow" << std::endl;
		return false;
	}
	pDs->arr[++(pDs->m_iIndex)] = data;
	return true;
}
template <class K>
bool stackpush<K>::operator()(DataStructure<K> * pDs, const K& data)
{
	if (pDs->m_iIndex > pDs->LEN - 2)
	{
		std::cout << "overflow" << std::endl;
		return false;
	}
	pDs->arr[++(pDs->m_iIndex)] = data;
	return true;
}
template <class K>
K stackpop<K>::Pop(DataStructure<K> * pDs)
{
	K rn = pDs->arr[pDs->m_iIndex];
	pDs->m_iIndex--;
	return rn;
}
template <class K>
K stackpop<K>::operator()(DataStructure<K> * pDs)
{
	K rn = pDs->arr[pDs->m_iIndex];
	pDs->m_iIndex--;
	return rn;
}
template <class K>
bool stackempty<K>::Empty(DataStructure<K> * pDs)
{
	if (pDs->m_iIndex == -1)
		return true;
	return false;
}
template <class K>
bool stackempty<K>::operator()(DataStructure<K> * pDs)
{
	if (pDs->m_iIndex == -1)
		return true;
	return false;
}
template <class K>
void stackprint<K>::Print(DataStructure<K> * pDs)
{
	for(int i=0; i<=pDs->m_iIndex; i++)
	{
		std::cout << pDs->arr[i] << std::endl;
	}
}
template <class K>
void stackprint<K>::operator()(DataStructure<K> * pDs)
{
	for (int i = 0; i <= pDs->m_iIndex; i++)
	{
		std::cout << pDs->arr[i] << std::endl;
	}
}

template <class K>
bool queuepush<K>::Push(DataStructure<K> * pDs, const K& data)
{
	if ((pDs->m_iRear + 1) % pDs->LEN == pDs->m_iFront)
	{
		std::cout << "overflow" << std::endl;
		return false;
	}
	pDs->m_iRear = (pDs->m_iRear + 1) % pDs->LEN;
	pDs->arr[pDs->m_iRear] = data;
	return true;
}
template <class K>
bool queuepush<K>::operator()(DataStructure<K> * pDs, const K& data)
{
	if ((pDs->m_iRear + 1) % pDs->LEN == pDs->m_iFront)
	{
		std::cout << "overflow" << std::endl;
		return false;
	}
	pDs->m_iRear = (pDs->m_iRear + 1) % pDs->LEN;
	pDs->arr[pDs->m_iRear] = data;
	return true;
}
template <class K>
K queuepop<K>::Pop(DataStructure<K> * pDs)
{
	if (pDs->m_iFront == pDs->m_iRear)
	{
		std::cout << "underflow" << std::endl;
		return 0;
	}
	pDs->m_iFront = (pDs->m_iFront + 1) % pDs->LEN;
	K rn = pDs->arr[pDs->m_iFront];
	return rn;
}
template <class K>
K queuepop<K>::operator()(DataStructure<K> * pDs)
{
	if (pDs->m_iFront == pDs->m_iRear)
	{
		std::cout << "underflow" << std::endl;
		return 0;
	}
	pDs->m_iFront = (pDs->m_iFront + 1) % pDs->LEN;
	K rn = pDs->arr[pDs->m_iFront];
	return rn;
}
template <class K>
bool queueempty<K>::Empty(DataStructure<K> * pDs)
{
	if (pDs->m_iFront == pDs->m_iRear)
		return true;
	return false;
}
template <class K>
bool queueempty<K>::operator()(DataStructure<K> * pDs)
{
	if (pDs->m_iFront == pDs->m_iRear)
		return true;
	return false;
}
template <class K>
void queueprint<K>::Print(DataStructure<K> * pDs)
{
	for (int i = (pDs->m_iFront+1) % pDs->LEN; i <= pDs->m_iRear % pDs->LEN; i++)
	{
		std::cout << pDs->arr[i] << std::endl;
	}
}
template <class K>
void queueprint<K>::operator()(DataStructure<K> * pDs)
{
	for (int i = (pDs->m_iFront + 1) % pDs->LEN; i <= pDs->m_iRear % pDs->LEN; i++)
	{
		std::cout << pDs->arr[i] << std::endl;
	}
}