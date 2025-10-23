﻿#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

void RecurPermutations(char* arr, int left, int right)
{
	// arr[left], ..., arr[right]

	//cout << "left ? " << left << endl;
	if (left == right)
	{
		for (int i = 0; i <= right; i++)
			cout << arr[i] << " ";
		cout << endl;
		
	}
	else
	{
		// 힌트
		// - for, swap(), 재귀호출
		// - 같은 변수끼리도 swap() 가능
		// - right는 고정

		// TODO:
		if (left>right)
		{
			return;
		}
		else{		
			// +1 incremented starting index will be transferred by recursive flow
			for(int i=left; i<=right; i++)
			{
				swap(arr[left],arr[i]);
				RecurPermutations(arr, left+1, right);
				swap(arr[left],arr[i]);
			}
			// for(int i=0; i<=right; i++)
			// {
			// 	swap(arr[left],arr[i]);	
			// 	for(int j=1; j<=right; j++)
			// 	{
			// 		//swap(arr[left],arr[j]);
			// 		for(int k=0; k<=right; k++)
			// 		{
			// 			if(left==0) RecurPermutations(arr, k+1, right);
			// 		}
			// 		//swap(arr[left],arr[j]);
			// 	}
			// 	swap(arr[left],arr[i]);
			// }
		}
	}
}

int main()
{
	/* a 한 글자의 순열 (Permutations) 

		a
	*/

	/* ab 두 글자의 순열 (Permutations)
		a b
		b a
	*/

	/*  abc 3 글자의 순열 (Permutations)

		a b c
		a c b
		b a c
		b c a
		c b a
		c a b
	*/

	// Permutations
	char arr[] = "abcd";

	RecurPermutations(arr, 0, 0);
	cout << endl;

	RecurPermutations(arr, 0, 1);
	cout << endl;

	RecurPermutations(arr, 0, 2);
	cout << endl;

	//RecurPermutations(arr, 0, 3);
	//cout << endl;

	return 0;
}
