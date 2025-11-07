#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	// TODO:
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
	int matrix_size = num_rows * num_cols;

	this->values_ = new float [matrix_size];
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	// TODO:
	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;
	int matrix_size = b.num_rows_ * b.num_cols_;

	this->values_ = new float [matrix_size];

	cout << "when constructor by value matrix_size " << matrix_size << endl;
	memcpy( this->values_ , b.values_ , sizeof(b.values_[0]) * matrix_size );
	
}

Matrix::~Matrix()
{
	// TODO:
	delete this->values_;
}

void Matrix::SetValue(int row, int col, float value)
{
	// values_[TODO] = value;
	// this->num_rows_ : 3
	// this->num_cols_ : 4
	int matrix_index = row*this->num_cols_ + col;
	this->values_[matrix_index] = value;
	
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	int matrix_index = row*this->num_cols_ + col;
	float value = this->values_[matrix_index];
	return value;
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의
	// 3 x 4 matrix -> 4 x 3 matrix

	// TODO:
	int new_matrix_rows = num_cols_;
	int new_matrix_cols = num_rows_;

	for(int i=0; i<new_matrix_rows; i++)
	{
		for(int j=0; j<new_matrix_cols; j++)
		{
			temp.SetValue(i,j,this->GetValue(j,i));
		}
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);

	for( int row_index=0; row_index<num_rows_; row_index++ )
	{
		for( int col_index=0; col_index<num_cols_; col_index++ )
		{
			int matrix_index = row_index*this->num_cols_ + col_index;
			float value_origin = this->values_[matrix_index];
			float value_b = b.values_[matrix_index];
			temp.values_[matrix_index] = value_origin + value_b;
		}
	}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
