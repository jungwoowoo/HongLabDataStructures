#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{
	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		// TODO:
		int new_front = Base::front_-1;

		cout << "1 item " << item << endl;

		cout << "1 new_front " << new_front << endl;

		if(new_front > 0)
		{
			Base::front_--;
			new_front = Base::front_+1;
		}
		else if(new_front <= 0)
		{
			cout << "1 capacity_ " << Base::capacity_ << endl;
			Base::front_ = Base::capacity_-1;
			new_front = new_front + 1;
		}

		cout << "2 new_front " << new_front << endl;
		cout << "2 front_ " << Base::front_ << endl;

		Base::queue_[new_front]=item;
		
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());
		Base::rear_ = Base::rear_-1;
	}

private:
	// Queue와 동일	
};
