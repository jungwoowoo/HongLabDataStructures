#include <iostream>
#include "../shared/SinglyLinkedList.h"
#include <math.h> // std::powf()

using namespace std;

struct Term
{
	float coef;
	int exp;
};

class LinkedPolynomial : public SinglyLinkedList<Term>
{
public:
	typedef SinglyLinkedList<Term>::Node Node;

	void NewTerm(float coef, int exp)
	{
		using namespace std;
		// TODO:

		Term *temp_term = new Term;

		temp_term->coef = coef;
		temp_term->exp = exp;
		
		PushBack(*temp_term);

		// Node *current = this->first_;

		// if(current==nullptr)
		// {
		// 	PushBack(*temp_term);
		// }
		// else if(current!=nullptr)
		// {
		// 	while(current)
		// 	{
		// 		if(temp_term->exp == current->item.exp)
		// 		{
		// 			float new_coef = temp_term->coef + current->item.coef;
		// 			current->item.coef = new_coef;
		// 			return;
		// 		}

		// 		current = current->next;
		// 	}

		// 	PushBack(*temp_term);
		// }
	}

	float Eval(float x)
	{
		using namespace std;
		float temp = 0.0f;

		// TODO:
		Node *current = first_;
		while(current)
		{
			Term *term = &(current->item);

			temp += term->coef * ( powf(x , (term->exp) ) );

			current = current->next;
		}

		return temp;
	}

	LinkedPolynomial Add(const LinkedPolynomial& poly)
	{
		using namespace std;
		// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
		// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

		LinkedPolynomial temp;

		Node* i = this->first_;
		Node* j = poly.first_;
		
		// TODO:
		while(i!=nullptr && j!=nullptr)
		{
			if(i->item.exp == j->item.exp)
			{
				float new_coef = i->item.coef + j->item.coef;
				temp.NewTerm(new_coef , i->item.exp);
			}
			else if(i->item.exp < j->item.exp)
			{
				temp.NewTerm(i->item.coef , i->item.exp);
				temp.NewTerm(j->item.coef , j->item.exp);
			} 
			else if(j->item.exp < i->item.exp)
			{
				temp.NewTerm(j->item.coef , j->item.exp);
				temp.NewTerm(i->item.coef , i->item.exp);
			}

			cout << " i->item.exp " << i->item.exp;
			cout << " j->item.exp " << j->item.exp;
			cout << endl;

			i = i->next;
			j = j->next;
		}

		Node *temp_k = i ? i : j;

		while(temp_k)
		{
			temp.NewTerm(temp_k->item.coef , temp_k->item.exp);
			temp_k = temp_k->next;
		}

		Node* t = temp.first_;

		while(t)
		{
			// cout << " t->item.exp " << t->item.exp;
			// cout << " t->item.coef " << t->item.coef;
			// cout << endl;

			Node* t_sub = temp.first_;

			while(t_sub)
			{
				if(t!=t_sub && t->item.exp == t_sub->item.exp)
				{
					// cout << " Before remove ";
					// //cout << " t->item.exp " << t->item.exp;
					// cout << " t_sub->item.exp " << t_sub->item.exp;

					// //cout << " t->item.coef " << t->item.coef;
					// cout << " t_sub->item.coef " << t_sub->item.coef;
					
					// cout << endl;

					float new_coef = t->item.coef + t_sub->item.coef;
					t->item.coef = new_coef;
					temp.Remove(t_sub);					
				}

				t_sub = t_sub->next;
			}

			t = t->next;
		}

		return temp;
	}

	void Print()
	{
		using namespace std;
		bool is_first = true; // 더하기 출력시 확인용
		int i = 0;
		// TODO:
		Node *current = first_;
		while(current)
		{
			Term *temp = &(current->item);
			// cout << "current coef " << temp->coef << endl;
			// cout << "current exp " << temp->exp << endl;
			current = current->next;
			if( temp->coef != 0.0f )
			{
				if (!is_first)
					cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력
				cout << temp->coef;

				if (i != 0) cout << "*" << "x^" << temp->exp;
				else
				{
					if(temp->exp>0) cout << "*" << "x^" << temp->exp;
				}

				is_first = false;
			}

			i = i+1;
		}
		cout << endl;
	}

private:
};

int main()
{
	using namespace std;

	LinkedPolynomial p1;

	// exp가 작은 항부터 추가한다고 가정
	p1.NewTerm(1.0f, 0);	// 1 * x^0 = 1
	p1.NewTerm(1.5f, 1);	// 1.5 * x^1
	p1.NewTerm(2.0f, 2);	// 2 * x^2

	p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	cout << p1.Eval(0.0f) << endl; // 1 + 1.5*0 + 2*0^2 = 1
	cout << p1.Eval(1.0f) << endl; // 1 + 1.5*1 + 2*1^2 = 4.5
	cout << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

	cout << endl;

	// Add() Test1
	cout << "Add() Test" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(5.0f, 7);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11

		cout << endl;
	}

	// Add() Test2
	cout << "Add() Test2" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);
		p1.NewTerm(5.0f, 7);
		p1.NewTerm(3.5f, 10);
		p1.NewTerm(5.5f, 20);
		p1.NewTerm(5.0f, 1000);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(3.2f, 0);
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11 + 5.5*x^20 + 5*x^1000

		cout << endl;
	}

	return 0;
}

