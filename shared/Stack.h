#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (stack_) delete[] stack_;
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		memcpy(new_stack, stack_, sizeof(T) * Size());
		if (stack_) delete[] stack_;
		stack_ = new_stack;
		capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{
		//return false; // TODO:
		//bool empty_bool = false;//int(stack_[top_]) > 0;
		bool empty_bool = false;
		// cout << boolalpha;
		// cout << " int(stack_[top_]) ? " << int(stack_[top_]) << endl;
		// cout << " empty_bool ? " << empty_bool << endl;
		if(top_ >= 0) empty_bool = false;
		else if(top_==-1) empty_bool = true;

		return empty_bool;
		
	}

	int Size() const
	{
		//return 0; //TODO:
		return capacity_;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const
	{
		assert(!IsEmpty());
		return stack_[top_];
	}

	int getTopPos() const
	{
		return top_;
	}
	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		//using namespace std;
		//cout << "entering @Push top_ " << top_ << endl;
		// TODO: 필요하면 리사이즈 
		// if ( Size() == 0 )
		// {
		// 	Resize(1);
		// }
		top_ = top_+1;
		capacity_ = capacity_+1;
		// TODO:
		// cout << "@Push item " << item->item << endl;
		// cout << "@Push top_ " << top_ << endl;
		stack_[top_] = item;
	}

	// Delete the TOP element of the stack
	void Pop()
	{	
		assert(!IsEmpty());
		// TODO:
		using namespace std;
		cout << "@Pop top_ " << top_ << endl;
		cout << "@Pop stack_[top_] " << stack_[top_]->item << endl;
		delete stack_[top_];
		top_ = top_-1;
		capacity_ = capacity_-1;
		
	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님
	int capacity_ = 0;
};
