#include <iostream>
//#include "../shared/Queue.h"
#include <queue>
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

	std::queue<int> queues[10];

	int m = GetMax(arr, n); // 가장 큰 자리수를 찾기 위해서

	int k = 1;
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		// TODO:
		for(int i=0; i<n; i++)
		{
			int origin_val = arr[i];
			int pow_n = pow(10,k-1);

			int target_n = 0;

			if(k==1)
			{
				target_n = origin_val%10;
			}
			else
			{
				target_n = static_cast<int>(floor(origin_val/pow_n))%pow_n;
				//target_n = int(floor(origin_val/pow_n))%pow_n;
			}

			cout << "target_n=" << target_n << endl;

			//cout << "queues[target_n]= " << queues[target_n].Size() << endl;

			queues[target_n].push(origin_val);
		}

		for(int w=0; w<10; w++)
		{
			//cout << "queues[w].Size" << queues[w].Size() << endl;
			for(int y=0; y<queues[w].size(); y++)
			{
				cout << "w=" << w << " queues[w].Size()=" << queues[w].size() << endl;
				//queues[w].();
			}
		}

		int target = 0;
		for(int w=0; w<10; w++)
		{
			while(!queues[w].empty())
			{
				int top = queues[w].front();
				arr[target] = top;
				queues[w].pop();
				target++;
			}
		}

		Print(arr, n);
		k++;
	}

	return 0;
}
