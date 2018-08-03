#include "DataLinkedList.h"

int main()
{
	DataLinkedList P1;
	StudentData * l = new StudentData("aaa", 10, 10, 20);
	StudentData * a = new StudentData("bbb", 10, 10, 20);
	StudentData * b = new StudentData("ccc", 10, 10, 20);
	StudentData * c = new StudentData("ddd", 10, 10, 20);
	StudentData * d = new StudentData("111", 10, 10, 20);
	StudentData * e = new StudentData("222", 10, 10, 20);
	StudentData * f = new StudentData("333", 10, 10, 20);
	StudentData * g = new StudentData("444", 10, 10, 20);

	P1.AddLink(*l);
	P1.AddLink(*a);
	P1.AddLink(*b);
	P1.AddLink(*c);
	P1.AddLink(*d);
	P1.AddLink(*e);
	P1.AddLink(*f);
	P1.AddLink(*g);
	P1.PrintAllData();
	P1.DelLink(l);
	P1.DelLink(c);
	P1.PrintAllData();
	StudentData * h = new StudentData("555", 10, 10, 20);
	P1.AddLink(*h);
	P1.PrintAllData();
	StudentData * i = new StudentData("qqq", 10, 10, 20);
	P1.AddLink(*i);
	P1.PrintAllData();
	StudentData * k = new StudentData("444", 10, 10, 20);
	P1.AddLink(*k);
	P1.PrintAllData();
	StudentData * j = new StudentData("444", 10, 10, 20);
	P1.AddLink(*j);
	P1.PrintAllData();
	P1.DelLink(e);
	P1.PrintAllData();
	sizeof(P1);
	P1.AddLink(*(new StudentData("zzz", 1, 1, 1)));
	P1.PrintAllData();
	P1.EditLink(f);
	return 0;
}