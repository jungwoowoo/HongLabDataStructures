#pragma once

#include <cassert>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <stack>

#include "../shared/Stack.h"

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// TODO: 연결 리스트 복사
		//first_ = list.first_;
		Node *cursor = first_;

		while(cursor)
		{
			PushBack(cursor->item);
			cursor = cursor->next;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		// TODO: size를 하나하나 세어서 반환

		return size;
	}

	T Front()
	{
		assert(first_);

		return T(); // TODO: 수정
	}

	T Back()
	{
		assert(first_);

		return T(); // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node *cursor_node = first_; 
		while(cursor_node->item!=item)
		{
			cursor_node = cursor_node->next;
		}

		if(cursor_node) return cursor_node;
		else return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		using namespace std;

		cout << " inserting " << endl;
		cout << item << endl;
		// param node -> item -> next node of param node
		// TODO:
		Node *insert_node = new Node;
		cout << " &insert_node " << endl;
		cout <<  &insert_node  << endl;
		insert_node->item = item;

		// save next_node_of_param_node
		Node *next_node_of_param_node = node->next;

		cout << " next_node_of_param_node " << endl;
		cout << next_node_of_param_node->item << endl;

		// param node -> item
		node->next = insert_node;

		// item -> next node of param node
		insert_node->next = next_node_of_param_node;

	}

	void Remove(Node* n)
	{
		assert(first_);

		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		Node* temp = first_;
		while(temp)
		{
			if(temp->next == n) break;
			temp = temp->next;
		}

		temp->next = n->next;
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)
		{
			Node* next_node = first_;
			first_ = new Node;
			first_->item = item;
			first_->next = next_node;			
		}

		// if(first_==nullptr)
		// {
		// 	// 새로운 노드 만들기
		// 	// TODO:
		// 	first_ = new Node;
		// 	first_->item = item;
		// }
		// else if(first_!=nullptr)
		// {
		// 	// 연결 관계 정리
		// 	// TODO:
			
		// 	Node* next_node = first_;
		// 	first_ = new Node;
		// 	first_->item = item;
		// 	first_->next = next_node;

		// }

	}

	void PushBack(T item)
	{
		using namespace std;
		if (first_)
		{
			cout << " push back item " << endl;
			cout << item << endl; 
			// TODO:
			Node *next = new Node;
			next->item = item;

			// find next==nullptr tail
			Node *tail = first_;

			while(tail->next!=nullptr)
			{
				tail = tail->next;
			}
			// connect tail->next = next
			tail->next = next;
		}
		else
		{
			// TODO:
			// first_ = new Node;
			// first_->item = item;
			PushFront(item);
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO: 메모리 삭제
		Node *new_first = first_->next;
		delete first_;
		first_ = new_first;
	}

	void PopBack()
	{
		using namespace std;
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.
		Node *temp = first_;
		while(temp)
		{
			if(temp->next->next==nullptr) break;
			temp = temp->next;
		}

		cout << "prev node of last " << temp->item << endl;

		assert(first_);

		// TODO: 메모리 삭제
		delete temp->next;
		temp->next = nullptr;

	}

	void Reverse()
	{
		using namespace std;
		// TODO:

		{ //

		  Node *current = first_;
		  Node *prev = NULL;

		  while(current)
		  {
			Node *temp = NULL;
			temp = prev;
			prev = current; // 1 2 3 4 5

			current = current->next; // 2 3 4 5 null
			//cout << " prev->item " << prev->item << endl;
			
			prev->next = temp;
		  }

		  cout << " while end ? prev " << prev->item << endl;
		  first_ = prev;

		}

		{ // using std:stack
		// Node *tail = first_;

	    // stack<Node*> node_stacks;
		// //Stack<Node*> node_stacks;

		// while(tail!=nullptr)
		// {
		// 	cout << " tail -> item" << endl;
		// 	cout << tail->item << endl;
			
		// 	node_stacks.push(tail);
		// 	tail = tail->next;
		// }

		// Node *current_cursor = nullptr;
		// Node *origin_first = first_;
		// while(!node_stacks.empty())
		// {
		// 	current_cursor = node_stacks.top();

		// 	if(current_cursor == origin_first)
		// 	{
		// 		cout << " origin_first found and it will be new last " << endl;
		// 		current_cursor->next = nullptr;
		// 		cout << current_cursor->item << endl;
		// 		node_stacks.pop();
		// 	}
		// 	else if(current_cursor->next == nullptr)
		// 	{
		// 		cout << " last found and it will be new first_ " << endl;
		// 		first_ = current_cursor;
		// 		node_stacks.pop();

		// 		cout << " last found and it will be new first_ , and next " << endl;
		// 		cout << node_stacks.top()->item << endl;
		// 		first_->next = node_stacks.top();
		// 	}
		// 	else
		// 	{
		// 		cout << " the others found " << endl;
		// 		cout << current_cursor->item << endl;
		// 		node_stacks.pop();
		// 		current_cursor->next = node_stacks.top();
		// 	}
		// }
		}
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};