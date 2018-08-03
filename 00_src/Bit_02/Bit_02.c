#include <stdio.h>

int main(void)
{
	unsigned char eightBitVal = 0x57;
	unsigned char fourBitVal1, fourBitVal2;
	fourBitVal1 = eightBitVal >> 4;
	fourBitVal2 = eightBitVal & 0x0F;
	printf("%X->%X,%X\n", eightBitVal, fourBitVal1, fourBitVal2);

	return 0;
}