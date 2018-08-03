#include "TToken1.h"

int main()
{
	char ch[] = "WKQEN KWJNE qwkjeN WKQJEN WQKJEN asMDN A<MEWN aS<MNE awJEN";
	TToken1 tk1(ch);
	TToken1 * qwe = new TToken1("lllll");
	tk1 += qwe;
	cout << &tk1;

	return 0;
}