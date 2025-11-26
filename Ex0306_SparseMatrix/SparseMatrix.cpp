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
	// {
	// 	int key = (row*num_cols_)+col;
	// 	cout << " key when SetValue " << key << endl; 
	// 	/**
	// 	 * without key
	// 	 */
	// 	if (capacity_>=0 && capacity_<num_terms_-1)
	// 	{
	// 		terms_[capacity_].row = row;
	// 		terms_[capacity_].col = col;
	// 		terms_[capacity_].value = value;
	// 	}
	// 	else if (capacity_ == num_terms_-1)
	// 	{
	// 		terms_[capacity_].row = row;
	// 		terms_[capacity_].col = col;
	// 		terms_[capacity_].value = value;
	// 		int current_row = 0;
	// 		int current_col = 0;
	// 		float current_val = 0.0f;

	// 		cout << " last index inserted and sort will be start !" << endl;
	// 		for(int i=0; i<num_terms_; i++)
	// 		{
	// 			current_row = terms_[i].row;
	// 			current_col = terms_[i].col;
	// 			current_val = terms_[i].value;
	// 			for(int j=i+1; j<num_terms_; j++)
	// 			{
	// 				if(current_row > terms_[j].row)
	// 				{
	// 					terms_[j-1].row = terms_[j].row;
	// 					terms_[j-1].col = terms_[j].col;
	// 					terms_[j-1].value = terms_[j].value;

	// 					terms_[j].row = current_row;
	// 					terms_[j].col = current_col;
	// 					terms_[j].value = current_val;
	// 				}
	// 			}
	// 		}

	// 		for(int i=0; i<num_terms_; i++)
	// 		{
	// 			current_row = terms_[i].row;
	// 			current_col = terms_[i].col;
	// 			current_val = terms_[i].value;
	// 			for(int j=i+1; j<num_terms_; j++)
	// 			{
	// 				if(current_row == terms_[j].row)
	// 				{
	// 					if(current_col > terms_[j].col)
	// 					{
	// 						terms_[j-1].row = terms_[j].row;
	// 						terms_[j-1].col = terms_[j].col;
	// 						terms_[j-1].value = terms_[j].value;

	// 						terms_[j].row = current_row;
	// 						terms_[j].col = current_col;
	// 						terms_[j].value = current_val;
	// 					}
	// 				}
	// 			}
	// 		}
			
	// 		for(int i=0; i<num_terms_; i++)
	// 		{
	// 			current_row = terms_[i].row;
	// 			current_col = terms_[i].col;
	// 			current_val = terms_[i].value;
	// 			for(int j=i+1; j<num_terms_; j++)
	// 			{
	// 				if(current_row == terms_[j].row)
	// 				{
	// 					if(current_col == terms_[j].col)
	// 					{
	// 						if(current_val > terms_[j].value)
	// 						{
	// 							terms_[j-1].row = terms_[j].row;
	// 							terms_[j-1].col = terms_[j].col;
	// 							terms_[j-1].value = terms_[j].value;

	// 							terms_[j].row = current_row;
	// 							terms_[j].col = current_col;
	// 							terms_[j].value = current_val;
	// 						}
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// 	capacity_++;
	// }

	{
		/**
		 * SetValue(int row, int col, float value)
		 * with key
		 */
		// int key = (row*num_cols_)+col;

		int key = (row*num_cols_)+col;
		
		if (capacity_>=0 && capacity_<num_terms_-1)
		{
			terms_[capacity_].row = row;
			terms_[capacity_].col = col;
			terms_[capacity_].value = value;

			cout << " capacity_ " << capacity_ << endl;
		}
		else if( capacity_ == num_terms_-1 )
		{
			terms_[capacity_].row = row;
			terms_[capacity_].col = col;
			terms_[capacity_].value = value;

			cout << " capacity_ " << capacity_ << endl;

			for(int i=0; i<num_terms_; i++)
			{
				int temp_key = terms_[i].row*num_cols_+terms_[i].col;
				int temp_row = terms_[i].row;
				int temp_col = terms_[i].col;
				float temp_value = terms_[i].value;

				for(int j=i-1; temp_key < terms_[j].row*num_cols_+terms_[j].col; --j)
				{	
					if(j>-1)
					{
						terms_[j+1].row = terms_[j].row;
						terms_[j+1].col = terms_[j].col;
						terms_[j+1].value = terms_[j].value;

						terms_[j].row = temp_row;
						terms_[j].col = temp_col;
						terms_[j].value = temp_value;
					}

				}
			}
		}

		capacity_++;

	}
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
