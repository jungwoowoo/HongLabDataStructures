#include <iostream>

#include "../shared/LimitedMaxHeap.h"

using namespace std;

int main()
{
	LimitedMaxHeap<int> h;

	/**
	 * 
	 * 큐의 크기가 제한된 상태에서 우선순위가 높은 것이 새로 추가가 되면 우선순위가 가장 낮은 것을 버리는 방식 구현
	 * 예시) 큐의 크기가 5개로 제한, 맥스 힙에 1, 2, 3, 4, 5 가 들어 있는 상태에서 6을 추가하기 위해 가장 작은 1을 버려서 
	 * 결과적으로 2, 3, 4, 5, 6이 남게 되는 구조. (저장 순서 무관)
	 */	

	 h.Push(1);
	 h.Push(2);
	 h.Push(3);
	 h.Push(4);
	 h.Push(5);

	//  h.Push(3);
	//  cout << h.Top() << endl;  // must be 5

	 // or
	h.Push(6);
	cout << h.Top() << endl;  // must be 6

	//h.Pop();

	return 0;
}
