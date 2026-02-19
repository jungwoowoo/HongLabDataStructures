#pragma once

#include "BinarySearchTree.h"

template<typename K, typename V>
class AVL : public BinarySearchTree<K, V>
{
	typedef BinarySearchTree<K, V> Base;
public:
	
    using typename BinarySearchTree<K, V>::Item;
    using typename BinarySearchTree<K, V>::Node;

	// struct Item {
	// 	K key = K();	// first
	// 	V value = V();	// second
	// };

	// struct Node {
	// 	Item item;
	// 	Node* left = nullptr;
	// 	Node* right = nullptr;
	// };

	int Height(Node* node)
	{
		return Base::Height(node); // 헷갈림 방지용
	}

	int Balance(Node* node)
	{
		if (node)
			return this->Height(node->left) - this->Height(node->right);
		else
			return 0;
	}

	Node* RotateLeft(Node* parent)
	{
		// TODO:
		using namespace std;
		// TODO:
		int balance = Balance(parent) * (-1);
		Node *center_node = parent;
		int center_count = int(balance/2);

		int count = 0;
		while(count!=center_count)
		{
			center_node = center_node->right;
			count++;
		}

		//cout << "parent->item.key " << parent->item.key << endl;

		if(!center_node->left)
		{
			center_node->left = new Node{ parent->item , nullptr , nullptr };
			swap( parent , center_node );
		}
		else if(center_node->left)
		{
			Node* temp_parent = parent;

			//cout << "temp_parent->item.key " << temp_parent->item.key << endl;

			// center_node->left->left = new Node{ temp_parent->left->item , nullptr , nullptr };
			// center_node->left->left->left = new Node{ temp_parent->item , nullptr , nullptr };
			center_node->left->left = new Node{ temp_parent->item , nullptr , nullptr };
			center_node->left->left->left = new Node{ temp_parent->left->item , nullptr , nullptr };
			//center_node->left = center_node->right;
			swap( parent , center_node );
		}

		return parent;
	}

	Node* RotateRight(Node* parent)
	{
		using namespace std;
		// TODO:
		int balance = Balance(parent);
		Node *center_node = parent;
		int center_count = int(balance/2);

		int count = 0;
		while(count!=center_count)
		{
			center_node = center_node->left;
			count++;
		}

		// cout << "parent->item.key " << parent->item.key << endl;
		// cout << "center_node->item.key " << center_node->item.key << endl;
		// center_node->right = new Node{ node->item , nullptr , nullptr };
		// swap( node , center_node );

		if(!center_node->right)
		{
			center_node->right = new Node{ parent->item , nullptr , nullptr };
			swap( parent , center_node );
		}
		else if(center_node->right)
		{
			Node* temp_parent = parent;

			//cout << "temp_parent->item.key " << temp_parent->item.key << endl;
			//center_node->right->right = new Node{ temp_parent->item , nullptr , nullptr };

			center_node->right->left = new Node{ temp_parent->item , nullptr , nullptr };
			center_node->right->right = new Node{ temp_parent->right->item , nullptr , nullptr };
			//center_node->left = center_node->right;
			swap( parent , center_node );
		}

		return parent;
	}

	void Insert(const Item& item)
	{
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		using namespace std;
		if (!node)
			return new Node{ item, nullptr, nullptr };

		const auto& key = item.key;

		if (key < node->item.key)
			node->left = Insert(node->left, item);
		else if (key > node->item.key)
			node->right = Insert(node->right, item);
		else
		{
			node->item = item;
			return node;
		}

		int balance = Balance(node);

		//cout << "current node " << node->item.key << " balance " << balance << endl;
		cout << item.key << " will be inserted " << endl;
		// cout << " Balance(node->left) " << Balance(node->left) << endl;
		// cout << " Balance(node->right) " << Balance(node->right) << endl;

		// balance가 0, 1, -1 이면 조절할 필요가 없다고 판단

		// LL -> Right Rotation
		if (balance > 1 && Balance(node->left) >= 0)
		{
			//	TODO:
			cout << " LL -> Right Rotation " << endl;

			node = RotateRight(node);
			//Insert(Item{ 8 , 'I'});
		}
		
		// RR -> Left Rotation
		if (balance < -1 && Balance(node->right) <= 0)
		{
			//	TODO:
			cout << " RR -> Left Rotation " << endl;
			
			node = RotateLeft(node);
		}
		
		// LR -> Left-Right Rotation
		if (balance > 1 && Balance(node->left) < 0)
		{
			//	TODO:
			cout << " LR -> Left-Right Rotation " << endl;

			node = RotateLeft(node);
			node = RotateRight(node);
		}

		// RL -> Right-Left Rotation
		if (balance < -1 && Balance(node->right) > 0)
		{
			//	TODO:
			cout << " RL -> Right-Left Rotation " << endl;
			node = RotateRight(node);
			node = RotateLeft(node);
			
		}

		return node;
	}

	Node* MinKeyNode(Node* node)
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}

	Node* Remove(Node* node, const K& key)
	{
		// BST와 동일
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			if (!node->left)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}

			Node* temp = MinKeyNode(node->right);
			node->item = temp->item;
			node->right = Remove(node->right, temp->item.key);
		}

		//if (node == NULL)	return node; // 불필요 (입력 node의 자식이 하나이거나 없는 경우에는 위에서 return 하기 때문)

		// 균형 잡기

		int balance = Balance(node);

		// TODO:

		return node;
	}

private:
	Node*& root_ = Base::root_;
    //this->root_로도 사용 가능
};