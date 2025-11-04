#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <math.h> // std::powf()

using namespace std;

// 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함

// exp항이 이미 존재하면 거기에 coef를 더해준다.
// 존재하지 않는다면 exp 오름 차순으로 정렬된 상태로 새로 추가한다.
void SparsePolynomial::NewTerm(float coef, int exp)
{
	if (coef == 0.0f) return; // 0이면 추가하지 않음

	if (num_terms_ >= capacity_)
	{
		// capacity 증가 (num_terms는 일단 고정)
		capacity_ = capacity_ > 0 ? capacity_ * 2 : 1; // 2배씩 증가
		Term* new_term = new Term[capacity_];

		// 원래 가지고 있던 데이터 복사
		memcpy(new_term, terms_, sizeof(Term) * num_terms_);

		// 메모리 교체
		if (terms_) delete[] terms_;
		terms_ = new_term;
	}

	terms_[num_terms_].coef = coef;
	terms_[num_terms_].exp = exp;

	num_terms_++;
}

float SparsePolynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	for(int i=0; i<this->num_terms_; i++)
	{
		temp += this->terms_[i].coef * powf(x,this->terms_[i].exp);
	}
	
	return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly)
{
	// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
	// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

	// 간단한 방법 (메모리를 더 사용하는 방법)
	// - 1. 최대 exp를 찾는다.
	// - 2. 필요한 크기의 Polynomial을 만든다. (Sparse 아님)
	// - 3. 더하면서 Polynomial에 업데이트 한다. 구조가 고정되어 있어서 쉽다.
	// - 4. Polynomial을 SparsePolynomial로 변환한다.

	SparsePolynomial temp;

	// TODO:
	/**
	 * solution 1
	 */
	{
	temp.num_terms_ = this->num_terms_ + poly.num_terms_;
	temp.capacity_ = this->capacity_ + poly.capacity_;
	temp.terms_ = new Term[temp.num_terms_+1];
	
	int max_exp = 0;

	for(int i=0; i<this->num_terms_; i++)
	{
		if( max_exp < this->terms_[i].exp ) max_exp = this->terms_[i].exp;
	}
	for(int i=0; i<poly.num_terms_; i++)
	{
		if( max_exp < poly.terms_[i].exp ) max_exp = poly.terms_[i].exp;
	}

	// first , assign p1 terms
	for(int i=0; i<this->num_terms_; i++)
	{
		temp.terms_[i].coef = this->terms_[i].coef;
		temp.terms_[i].exp = this->terms_[i].exp;
	}

	// second assign p2 terms
	int last_i_index = 0;
	int last_j_index = 0;

	for(int i=0; i<temp.num_terms_; i++)
	{
		for(int j=0; j<poly.num_terms_; j++)
		{
			if ( poly.terms_[j].exp == temp.terms_[i].exp )
			{
				if( i>0 && temp.terms_[i].exp!=0 )
				{
					temp.terms_[i].coef += poly.terms_[j].coef;
					last_i_index = i;
					last_j_index = j;
					cout << " each i " << i << " each j ?? " << j << endl;
				}
				else if ( i==0 && temp.terms_[i].exp==0 )
				{
					temp.terms_[i].coef += poly.terms_[j].coef;
					cout << " each i " << i << " each j ?? " << j << endl;
				}
			}
		}
	}

	cout << "last_i_index " << last_i_index << endl;
	cout << "last_j_index " << last_j_index << endl;

	int diffs_array_size = 0;
	int *exp_diffs_array = new int [diffs_array_size];
	float *coef_diffs_array = new float [diffs_array_size];

	for(int i=0; i<poly.num_terms_; i++)
	{
		int exist_count = 0;
		for(int j=0; j<temp.num_terms_; j++)
		{
			if ( temp.terms_[j].exp == poly.terms_[i].exp )
			{
				exist_count++;
			}
		}

		if(exist_count>0)
		{
		}
		else
		{
			diffs_array_size++;
			exp_diffs_array[diffs_array_size-1] = poly.terms_[i].exp;
			coef_diffs_array[diffs_array_size-1] = poly.terms_[i].coef;
		}
	}

	for(int k=0; k<diffs_array_size; k++)
	{
		cout << "exp_diffs_array[k] ?? " << exp_diffs_array[k] << endl;
		int break_i = 0;
		for(int i=0; i<temp.num_terms_; i++)
		{
			if ( temp.terms_[i].exp > exp_diffs_array[k] )
			{
				// cout << "diffs_array[k] ?? " << diffs_array[k] << endl;
				break_i = i;
				break;
			}
			else if ( temp.terms_[i].exp < exp_diffs_array[k] )
			{

			}
		}
		cout << "break_i ? " << break_i << endl;

		if ( break_i > 0 )
		{
			for( int p=temp.num_terms_-1; p>0 ; p-- )
			{
				temp.terms_[break_i+p].coef = temp.terms_[break_i+p-1].coef;
				temp.terms_[break_i+p].exp = temp.terms_[break_i+p-1].exp;
			}

			temp.terms_[break_i].exp = exp_diffs_array[k];
			temp.terms_[break_i].coef = coef_diffs_array[k];
		}
		else if ( break_i == 0 )
		{
			temp.terms_[this->num_terms_+k].exp = exp_diffs_array[k];
			temp.terms_[this->num_terms_+k].coef = coef_diffs_array[k];
		}
	}
	} // solution 1 end
	
	/**
	 * solution 2
	 */
	{
		
	}
	return temp;
}

void SparsePolynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < num_terms_; i++)
	{
		// 0이 아닌 항들만 골라서 출력할 필요가 없음

		if (!is_first)
			cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

		cout << terms_[i].coef;

		if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

		is_first = false;
	}

	cout << endl;
}
