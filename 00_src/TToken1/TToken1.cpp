#include "TToken1.h"

int TToken1::m_iCounter = 0;

ostream& operator <<(ostream & os, const TToken1* data)
{
	TToken1 *temp = const_cast<TToken1*>(data);
	for (int i = 0; i < data->m_iCounter; i++)
	{
		os << temp->m_pCh << endl;
		temp = temp->m_pNext;
	}
	return os;
}

void TToken1::addTToken(TToken1 * data)
{
	if (this->m_pCh == NULL)
	{
		m_pCh = new char[strlen(data->m_pCh) + 1];
		strcpy(m_pCh, data->m_pCh);
		return;
	}
	TToken1 * temp = this;
	while (temp->m_pNext != NULL)
	{
		temp = temp->m_pNext;
	}
	temp->m_pNext = data;
}
bool TToken1::TTokenCheck(const char * pChar)
{
	int i = 0;
	while (pChar[i] != NULL)
	{
		if (pChar[i++] == ' ')
			return false;
	}
	return true;
}

TToken1& TToken1::operator+= (TToken1 * data)
{
	this->addTToken(data);
	return *this;
}

TToken1::TToken1(const char * data) : m_pNext(NULL)
{
	if (TTokenCheck(data))
	{
		m_pCh = new char[strlen(data) + 1];
		strcpy(m_pCh, data);
		m_iCounter++;
		return;
	}
	char * temp;
	temp = strtok(const_cast<char*>(data), " ");
	while (temp!=NULL)
	{
		this->addTToken(new TToken1(temp));
		temp = strtok(NULL, " ");
	}
}
TToken1::~TToken1()
{
	delete[] m_pCh;
	TToken1 * Del = this->m_pNext;
	if (Del == NULL)
	{
		return;
	}
	delete Del;
}

