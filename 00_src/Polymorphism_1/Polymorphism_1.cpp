
#include "TDepartment.h"

int main()
{
	TDepartment pp;
	pp.AddEmployee(new TMonthby("qqq", Pos::TEMPORARY, 3));
	pp.AddEmployee(new TTimeby("www", Pos::CHIEF, 60));
	pp.AddEmployee(new TYearby("eee", Pos::PRESIDENT, 3));
	pp.AddEmployee(new TTimeby("qqq", Pos::PERMANENT, 50));
	pp.AddEmployee(new TTimeby("rrr", Pos::TEMPORARY, 50));

	pp.ShowSalary();

	return 0;
}