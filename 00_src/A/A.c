#include <stdio.h>

int equal(int*n)
{
	int i, j, a;
	for (i = 0;i < 9;i++)
		for (j = 0;j < 9;j++)
			if (n[i] == n[j] && i != j)
				return 1;
	return 0;
}

int main(void)
{
	int arr[9];
	int a, b, c, d, i;
	for(arr[0]=1;arr[0]<10;arr[0]++)
		for (arr[1] = 1;arr[1]<10;arr[1]++)
			for (arr[2] = 1;arr[2]<10;arr[2]++)
				for (arr[3] = 1;arr[3]<10;arr[3]++)
					for (arr[4] = 1;arr[4]<10;arr[4]++)
						for (arr[5] = 1;arr[5]<10;arr[5]++)
							for (arr[6] = 1;arr[6]<10;arr[6]++)
								for (arr[7] = 1;arr[7]<10;arr[7]++)
									for (arr[8] = 1;arr[8] < 10;arr[8]++)
									{
										a = ((arr[0] * 10) + arr[1]) * arr[2];
										b = (arr[3] * 10) + arr[4];
										c = (arr[5] * 10) + arr[6];
										d = (arr[7] * 10) + arr[8];
										if (equal(arr))
											continue;
										else if (a == b && b + c == d)
										{
											for (i = 0;i < 9;i++)
												printf("%d ", arr[i]);
											puts("");
											return 0;
										}
									}
}