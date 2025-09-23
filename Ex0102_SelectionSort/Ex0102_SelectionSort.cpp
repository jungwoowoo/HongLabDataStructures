#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

struct Element
{
	int key;
	char value;
};

bool CheckSorted(int* arr, int size)
{
	// TODO: 정렬 확인 함수 구현

	int temp_for_compare=0;
	bool asc_fault = false;
	for (int e = 0; e < size; e++) {
		if(arr[e] >= temp_for_compare) temp_for_compare = arr[e];
		else 
		{
			asc_fault=true; 
			break;
		}
	}

	if(!asc_fault) return true;
	else return false;
	
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void Print(Element* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i].key << " ";
	cout << endl;

	for (int i = 0; i < size; i++)
		cout << arr[i].value << " ";
	cout << endl;
}

int main()
{
	// 3개 정렬
	
	// {
	// 	for (int k = 0; k < 3; k++)
	// 		for (int j = 0; j < 3; j++)
	// 			for (int i = 0; i < 3; i++) {

	// 				int arr[3] = { i, j, k };
	// 				int size = sizeof(arr) / sizeof(arr[0]);

	// 				for (int e = 0; e < size; e++) {
	// 					cout << arr[e] << " " << flush;
	// 				}

	// 				cout << boolalpha;
	// 				cout << CheckSorted(arr, size); // 정렬 되었나 확인					
					
	// 				cout << " -> " << flush;

	// 				//TODO: 정렬 해보기

	// 				// 최소값 갱신
	// 				int min = INT32_MAX;
	// 				for (int e = 0; e < size; e++) {
	// 					if ( min > arr[e] ) min = arr[e];
	// 				}

	// 				for (int e = 0; e < size; e++) {
	// 					if(arr[e] > arr[e+1])
	// 					{
	// 						swap(arr[e] , arr[e+1]);

	// 						if( arr[e] > min )
	// 						{
	// 							continue;
	// 						}
	// 						else if ( arr[e] <= min )
	// 						{
	// 							min = arr[e];
	// 							swap(arr[0] , arr[e]);
	// 						}							
	// 					} 						
	// 				}						
				
	// 				for (int e = 0; e < size; e++) {
	// 					//cout << " result " << flush;
	// 					cout << arr[e] << " " << flush;
	// 				}

	// 				cout << boolalpha;
	// 				cout << CheckSorted(arr, size); // 정렬 되었나 확인
	// 				cout << endl;
	// 			}
	// }

	//return 0; // <- 실습용 임시

	// 5개라면? 더 많다면?
	{
		// 8 4 2 8 3
		// TODO: ???
		int arr[5] = { 8,4,2,8,3 };
		int size = sizeof(arr) / sizeof(arr[1]);

		cout << "############ 5 numbers #############" << endl;
		for (int e = 0; e < size; e++) {
			//cout << " result " << flush;
			cout << arr[e] << " " << flush;
		}
		cout << boolalpha;
		cout << CheckSorted(arr, size); // 정렬 되었나 확인
		cout << "" << endl;

		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if(arr[j]<arr[i])
				{
					swap(arr[j],arr[i]);
				}

			}
		}

		for (int e = 0; e < size; e++) {
			//cout << " result " << flush;
			cout << arr[e] << " " << flush;
		}		
		cout << boolalpha;
		cout << CheckSorted(arr, size); // 정렬 되었나 확인
		cout << "" << endl;

		// 8 3 2 5 1 1 2 5 8 9
		int arr1[10] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
		// TODO: ???
		int size1 = sizeof(arr1) / sizeof(arr1[1]);

		cout << "############ 10 numbers #############" << endl;
		for (int e = 0; e < size1; e++) {
			//cout << " result " << flush;
			cout << arr1[e] << " " << flush;
		}
		cout << boolalpha;
		cout << CheckSorted(arr1, size1); // 정렬 되었나 확인
		cout << "" << endl;

		for (int i = 0; i < size1; i++)
		{
			for (int j = i + 1; j < size1; j++)
			{
				if(arr1[j]<arr1[i])
				{
					swap(arr1[j],arr1[i]);
				}

			}
		}
		for (int e = 0; e < size1; e++) {
			//cout << " result " << flush;
			cout << arr1[e] << " " << flush;
		}		
		cout << boolalpha;
		cout << CheckSorted(arr1, size1); // 정렬 되었나 확인
		cout << "" << endl;
		// 100개라면?
	}

	//return 0;

	// 가장 작은 수 찾기
	{
		int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 }; // 임의의 숫자들, 변경 가능
		int size = sizeof(arr) / sizeof(arr[0]);

		assert(size > 0); // size가 1이상이라고 가정

		int min_number = INT32_MAX;
		for (int i=0; i<size; i++)
		{
			if( arr[i] < min_number )
			{
				min_number = arr[i];
				//min_number = std::min(arr[i] , min_number);
			}
		}
		// TODO:
		cout << "Minimum number is " << min_number << endl;
	}

	// 가장 작은 수의 인덱스 찾기
	{
		int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
		int size = sizeof(arr) / sizeof(arr[0]);

		assert(size > 0); // size가 1이상이라고 가정
		int min_number = INT32_MAX;
		int min_index = 0;
		for (int i=0; i<size; i++)
		{
			if( arr[i] < min_number )
			{
				min_number = arr[i];
				min_index = i;
			}
		}
		// TODO:

		cout << "The index of min is " << min_index << endl;
		cout << "Minimum number is " << arr[min_index] << endl;
	}

	// Selection Sort
	// 힌트: swap()
	{
		int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
		int size = sizeof(arr) / sizeof(arr[0]);

		int min_index;
		for (int i = 0; i < size - 1; i++)
		{

			// TODO:
			// int min_number_each_sub = INT32_MAX;
			// for (int j = i; j < size; j++)
			// {
			// 	if( arr[j] < min_number_each_sub )
			// 	{
			// 		min_number_each_sub = arr[j];
			// 		swap(arr[i] , min_number_each_sub);
			// 	}
			// }

			for (int j = i+1; j < size; j++)
			{
				if( arr[j] < arr[i] )
				{
					min_index = j;
					swap(arr[i],arr[min_index]);
				}
			}


			
			Print(arr, size);

			cout << boolalpha;
			cout << CheckSorted(arr, size);
			cout << endl;
		}
	}

	// 비교 횟수 세보기, 더 효율적인 방법은 없을까?
	// https://en.wikipedia.org/wiki/Sorting_algorithm
	{
		ofstream ofile("log.txt");
		for (int size = 1; size < 1000; size++)
		{
			int count = 0;
			int* arr = new int[size];
			for (int s = 0; s < size; s++) {
				arr[s] = size - s;
			}

			//TODO: count ++;
			count ++;
			cout << size << ", " << count << endl;
			ofile << size << ", " << count << endl;
			Print(arr, size);

			delete[] arr;
		}

		ofile.close();
	}

	// [2, 2, 1]
	// [1, 2, 2] // 첫 2가 마지막으로 이동

	// 안정성 확인(unstable)
	{
		Element arr[] = { {2, 'a'}, {2, 'b'}, {1, 'c'} };
		int size = sizeof(arr) / sizeof(arr[0]);

		Print(arr, size); // arr이 Element의 배열

		// TODO:

		Print(arr, size); // arr이 Element의 배열
	}
}
