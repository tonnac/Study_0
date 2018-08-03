#include "Person.h"



Person::Person(int id) : id(id)
{
}


//Person::~Person()
//{
//}

void Person::show()
{
	std::cout << id << std::endl;
}