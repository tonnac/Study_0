#pragma once
class Array
{
public:
	Array();
	Array(int size);
	~Array();
	bool SetData(int pos, int data);
	bool GetData(int pos, int&data);
private:
	int *pData;
	int maxsize;
};

