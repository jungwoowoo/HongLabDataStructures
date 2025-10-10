#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

int Sum(int* arr, int n)
{
	int sum = 0;

	for (int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

int RecurSum(int* arr, int n)
{
	/* 힌트: 역순으로 더하기 (매개변수에 시작 인덱스를 추가하지 않아도 되기 때문)
	  (1 + 2 + ... 8 + 9 + 10)
	= (1 + 2 + ... 8 + 9) + 10
	= ((1 + 2 + ... 8) + 9) + 10
	= ...
	*/
	//int result = 0;

	// exit condition
	//if ( n == 0 ) return result;
	if ( n == 0 ) return 0;
	else
	{
		cout << "RecurSum arr[n-1] " << arr[n-1] << endl;
		int c = RecurSum(arr , n-1);
		c += arr[n-1];
		cout << "RecurSum c " << c << endl;
		return c; // <- TODO:
	}
	//result = RecurSum(arr, n-1);
}

// int RecurSum(int* arr , int n)
// {
// 	if ( n <= 0) return 0;
// 	else
// 	{
// 		return RecurSum(arr, n-1) + arr[n-1];
// 	}
// }

int main()
{
	// Sum vs RecurSum

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << Sum(arr, n) << endl;
	cout << RecurSum(arr, n) << endl;

	return 0;
}
