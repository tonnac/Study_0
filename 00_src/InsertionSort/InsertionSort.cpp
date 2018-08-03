#include <iostream>
#include <ctime>

using namespace std;

void InsertionSort(int arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		for (; j >= 0 && temp < arr[j]; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = temp;
	}
}

int main()
{
	srand(time(NULL));
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
		{
			cout << " ";
		}
		cout << arr[i];
	}
	cout << endl;
	InsertionSort(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
		{
			cout << " ";
		}
		cout << arr[i];
	}
	cout << endl;
	return 0;
}