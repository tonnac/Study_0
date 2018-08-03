#include <stdio.h>

int main(void)
{
	unsigned char fourBitVal1 = 0x05;
	unsigned char fourBitVal2 = 0x07;
	unsigned char eightBitVal;
	eightBitVal = fourBitVal1 << 4;
	eightBitVal |= fourBitVal2;
	printf("%#X,%#X->%#X\n",
		fourBitVal1, fourBitVal2, eightBitVal);
	return 0;
}