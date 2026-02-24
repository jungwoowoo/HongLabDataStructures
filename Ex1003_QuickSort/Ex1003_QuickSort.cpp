#include <iostream>
#include <iomanip>
#include <math.h>

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

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}

// Hoare partition scheme
int Partition(int arr[], int low, int high, int n)
{
	int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
	int i = low - 1;
	int j = high + 1;

	// int middle_index = size_t(floorf((high - low) / 2.0f)) + low;

	// cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
	// cout << "middle_index=" << middle_index << endl;

	while (true)
	{
		// TODO:

		// int middle_index = size_t(floorf((high - low) / 2.0f)) + low;

		cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
		// cout << "middle_index=" << middle_index << endl;
		// cout << "arr[i]=" << arr[i] << endl;
		// cout << "arr[j]=" << arr[j] << endl;
		// cout << "         ";
		Print(arr, low, high, n);

		if( arr[i+1]<pivot && arr[j-1]>pivot )
		{
			i=i+1;
			j=j-1;
		}
		else if( arr[i+1]<pivot && arr[j-1]<=pivot )
		{
			i=i+1;
		}
		else if( arr[i+1]>=pivot && arr[j-1]>pivot )
		{
			j=j-1;
		}		
		else if( arr[i+1]>pivot && arr[j-1]<pivot )
		{			
			swap(arr[i+1],arr[j-1]);
			i=i+1;
			j=j-1;
		}
	
		else if( arr[i+1]==pivot && arr[j-1]<pivot )
		{
			swap(arr[i+1] , arr[j-1]);
			return i+1;

		}
		else if( arr[i+1]>pivot && arr[j-1]==pivot )
		{
			swap(arr[i+1] , arr[j-1]);
			return j-1;

		}		
		else if( arr[i+1]==pivot && arr[j-1]==pivot )
		{
			return i+1;
		}

	}
}

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		int p = Partition(arr, low, high, n);

		cout << " p = " << p << endl;

		QuickSort(arr, low, p, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}
