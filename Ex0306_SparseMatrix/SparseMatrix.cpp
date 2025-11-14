#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	// TODO:
	num_rows_ = num_rows;
	num_cols_ = num_cols;
	num_terms_ = capacity;
	terms_ = new MatrixTerm[num_terms_];

}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	// TODO:
	num_rows_ = b.num_rows_;
	num_cols_ = b.num_cols_;
	num_terms_ = b.capacity_;
	terms_ = new MatrixTerm[num_terms_];
}

SparseMatrix::~SparseMatrix()
{
	// TODO:
	delete[] terms_;

}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장

	// TODO:
	assert ( capacity_ < num_terms_ );

	terms_[capacity_].row = row;
	terms_[capacity_].col = col;
	terms_[capacity_].value = value;

	capacity_++;
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// TODO: key = col + num_cols * row;

	float exist_value = 0.0f;
	for(int i=0; i<num_terms_; i++)
	{
		if( terms_[i].row == row && terms_[i].col == col )
		{
			exist_value = terms_[i].value;
			break;
		}
	}
	
	return exist_value;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for(int i=0; i<num_terms_; i++)
	{
		temp.terms_[i].col = terms_[i].row;
		temp.terms_[i].row = terms_[i].col;
		temp.terms_[i].value = terms_[i].value;
	}

	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
