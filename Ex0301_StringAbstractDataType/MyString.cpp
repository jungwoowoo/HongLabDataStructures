#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	for(int i=0; init[i]!='\0'; i++)
	{
		size_++;
	}
	
	// 메모리 할당
	str_ = new char[size_+1];

	// 데이터 복사 , include null character '\0'
	for(int i=0; i<size_+1; i++)
	{
		str_[i] = init[i];
	}
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사

	// alloc new memory as new size
	size_ = str.size_;
	
	// 메모리 할당 , include null character '\0'
	str_ = new char[size_+1];

	// 데이터 복사 , include null character '\0'
	for(int i=0; i<size_+1; i++)
	{
		str_[i] = str.str_[i];
	}	
}

MyString::~MyString()
{	
	// 메모리 해제
	str_ = nullptr;
	//delete []str_;

}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	if ( this->size_ == str.size_ )
	{
		int same_count=0;
		for( int i=0; i<this->size_; i++)
		{
			if(this->str_[i]==str.str_[i]) same_count++;
			else return false;
		}

		if(same_count==this->size_) return true;
	}

	return false;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사

}

// // 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp;
	temp.size_ = num;
	temp.str_ = new char[temp.size_];
	// TODO:
	for(int i=0; i<num; i++)
	{
		temp.str_[i] = this->str_[start+i];
	}
	return temp;
}

MyString MyString::Concat(MyString app_str)
{
	MyString temp;

	// TODO: 
	// this->str_ : concat source
	// app_str.str_ : concat target
	temp.size_ = this->size_ + app_str.size_; // exclude each null characters
	temp.str_ = new char[temp.size_];	

	for( int i=0; i<temp.size_; i++ )
	{
		if ( i < this->size_ )
		{
			temp.str_[i] = this->str_[i];
		}
		else if ( i >= this->size_)
		{
			temp.str_[i] = app_str.str_[i-app_str.size_-1];
		}
	}
	return temp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	MyString temp;
	// TODO:
	temp.size_ = this->size_ + t.size_;
	temp.str_ = new char[temp.size_];

	for(int i=0; i<temp.size_; i++)
	{
		if( i>=start && i<t.size_+start )
		{
			temp.str_[i] = t.str_[i-start];
		}
		else
		{
			if ( i >= start+t.size_ ) temp.str_[i] = this->str_[i-t.size_];
			else if ( i < start+t.size_ ) temp.str_[i] = this->str_[i];
			
		}
	}
	return temp;
}

int MyString::Find(MyString pat)
{
	//TODO:
	//cout << "pat.size_ ? " << pat.size_ << endl;

	int size_s = 0;
	char *temp_s = new char[size_s];
	for(int i=0; i<size_+1; i++)
	{
		if( int(str_[i])!=32 )
		{
			temp_s[size_s] = str_[i];
			size_s++;
		}
		else if( int(str_[i])==32 ) // white space
		{
			int same_count = 0;
			for( int j=0; j<pat.size_; j++)
			{
				if( temp_s[j] == pat.str_[j] ) same_count++;
			}

			if( same_count == pat.size_ ) return i-size_s;		

			size_s = 0;

			cout << endl;
		}

		if ( int(str_[i]) == 0 )
		{
			int result_index = -1;

			int same_count = 0;
			int last_index = 0;
			for(int j=0; j<size_s; j++)
			{
				for(int k=0; k<pat.size_; k++)
				{
					if( temp_s[j] == pat.str_[k] )
					{
						same_count++;
						last_index = j;
					}
				}
			}

			if( same_count == pat.size_ ) result_index = last_index-pat.size_+1;

			if ( result_index < 0)
			{
				int same_count = 0;
				for( int j=0; j<pat.size_; j++)
				{
					if( temp_s[j] == pat.str_[j] ) same_count++;
				}

				if( same_count == pat.size_ ) result_index = i-size_s;			

				size_s = 0;

				cout << endl;
			}

			return result_index;

		}
		
	}
	
	delete []temp_s;

	return -1;
}

void MyString::Print()
{
	cout << "size_ Print " << size_ << endl;
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}

