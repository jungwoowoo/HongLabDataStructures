#include <iostream>
#include "../shared/Queue.h"
//#include <math.h>
#include <cmath> 

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int GetMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);

	Queue<int> queues[10];

	int m = GetMax(arr, n); // 가장 큰 자리수를 찾기 위해서

	int k = 1;
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		// TODO:
		for(int i=0; i<n; i++)
		{
			int origin_val = arr[i];
			float temp = pow(10.0f,-k);
			float temp2 = float(origin_val) * temp;
			float t = trunc(temp2);

			float target_n = (temp2 - t) * 10;
			int n = int(target_n);

			cout << "target_n=" << n << endl;

			queues->Enqueue(n);

			if(queues->Front() < n) queues->Enqueue(n);
			//float target_n = temp2 - t;
			//int target_n = float(origin_val)

			
			// cout << "temp2=" << temp2 << endl;
			// cout << "t=" << t << endl;
			
		}

		Print(arr, n);
		k++;
	}

	return 0;
}
