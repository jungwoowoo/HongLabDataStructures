#pragma once

#include <iostream>
#include <fstream>
#include <string> // BinaryTree 출력
#include <math.h>

#include "Queue.h"
#include "Stack.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr; // Left child
		Node* right = nullptr; // Right child
	};

	// 디버깅 도구: 큐에서 주소 대신에 아이템 출력
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	// 디버깅 도구: 스택에서 주소 대신에 아이템 출력
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " "; // 수행하고 싶은 작업 구현(여기서는 출력)
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
		// TODO:
		int sum = 0;
		//sum += node->item;
		if(node)
		{ 
			sum += node->item;
			sum += Sum(node->left) + Sum(node->right);
		}
		else if(node==nullptr)
		{
			return sum;
		}
		
		return sum;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		using namespace std;
		// TODO:
		int height = 0;
		if(node)
		{
			height = height + 1;

			if(node->left==nullptr && node->right==nullptr) return height;	
			else if(node->left!=nullptr || node->right!=nullptr)
			{			
				if(node->left && node->right)
				{
					height+= (Height(node->left) >= Height(node->right)) ? Height(node->left) : Height(node->right);
				}
				else if(node->left)
				{
					height+=Height(node->left);
				}
				else if(node->right)
				{
					height+=Height(node->right);
				}
			}
		}
		else if(node==nullptr)
		{
			return height;
		}

		return height;

	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			// TODO: 힌트 Post-order
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)
	{
		// TODO:
		if(node)
		{
			Visit(node);

			if(node->left) Preorder(node->left);
			if(node->right) Preorder(node->right);
		}		
	};

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
		// TODO:
		if(node)
		{
			if(node->left)
			{
				Inorder(node->left);
			}

			Visit(node);

			if(node->right)
			{
				Inorder(node->right);
			}	
		}
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node)
	{
		// TODO:	
		if(node->left) Postorder(node->left);
		if(node->right) Postorder(node->right);

		Visit(node);
	}

	void LevelOrder()
	{		
	
		// 힌트: MyQueue q;
		MyQueue q;

		Node* current = root_;
		
		while (current)
		{
			if(!q.IsEmpty()) 
			{
				current=q.Front();
				q.Dequeue();
			}
			
			if(current) 
			{
				Visit(current);
				// TODO:
				if(current->left) q.Enqueue(current->left);
				if(current->right) q.Enqueue(current->right);
				else if(!current->left && !current->left) q.Enqueue(nullptr);
			}

		}
	}

	void IterPreorder()
	{
		if (!root_) return;
		//Stack<Node*> s; // 힌트: MyStack q;
		MyStack s;
		s.Push(root_);

		while (!s.IsEmpty())
		{
			// TODO:
			Node *left_temp = s.Top()->left ? s.Top()->left : nullptr;
			Node *right_temp = s.Top()->right ? s.Top()->right : nullptr;

			Visit(s.Top());
			s.Pop();

			if(right_temp) s.Push(right_temp);
			if(left_temp) s.Push(left_temp);
		}
	}

	void IterInorder()
	{
		using namespace std;

		cout << " root_->item " << root_->item << endl;

		if (!root_) return;

		Stack<Node*> s;

		Node* current = root_;

		while (current || !s.IsEmpty())
		{
			//cout << "current->item : " << current->item << endl;

			// TODO:
			while(current)
			{
				s.Push(current);
				current = current->left;
			}

			//cout << "1111 s.getTopPos()" << s.getTopPos() << endl;
			//current = s.Top();
			//if(s.Top()==root_) current=s.Top()->right;

			Node *temp = s.Top();

			Visit(s.Top());
			s.Pop();

			if(temp->right) s.Push(temp->right);

			//cout << "2222 s.getTopPos()" << s.getTopPos() << endl;
			// if(current->right)
			// {
			// 	cout << "2222222 current->right " << current->right->item << endl;
			// 	s.Push(current->right);
			// 	current = current->right;
			// }
		}

		//cout << "s.Top() " << s.Top()->item << endl;
		//s.Print();

	}

	void IterPostorder()
	{
		using namespace std;
		if (!root_) return;

		Stack<Node*> s1, s2;

		s1.Push(root_);

		while (!s1.IsEmpty())
		{
			//TODO:
			while(s1.Top()->right)
			{
				if(s1.Top()==root_ && s1.Top()->left) s2.Push(s1.Top()->left);
				else if(s1.Top()!=root_ && s1.Top()->left) s1.Push(s1.Top()->left);
				s1.Push(s1.Top()->right);
			}
			break;
		}

		while (!s2.IsEmpty())
		{
			// TODO:
			while(s2.Top()->left)
			{
				if(s2.Top()->left) s2.Push(s2.Top()->left);
				if(s2.Top()->right) s2.Push(s2.Top()->right);
			}

			while(!s2.IsEmpty())
			{
				Visit(s2.Top());
				s2.Pop();
			}

			while(!s1.IsEmpty())
			{
				Visit(s1.Top());
				s1.Pop();
			}			
		}		

		

		// while(s1.Top())
		// {
		// 	Visit(s1.Top());
		// 	s1.Pop();
		// }
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}
