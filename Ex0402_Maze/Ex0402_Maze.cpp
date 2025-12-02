#include <iostream>
#include <cstring>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;
char direct = 'r';

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;
	
	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

void RecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return;
	}
	// 방문했던 적이 없고 ('X'가 아니고)
	// 벽도 아닌 경우 ('1'도 아닌 경우)
	else if (mark!='X' && mark!='1')
	{
		//'X' 표시
		maze[p.row][p.col] = mark!='S' ? 'X' : 'S';

		//if path not exists in bottom
		if( maze[p.row+1][p.col] != '0' )
		{
			// cout << endl;
			// //select direction
			// for(int i=0; i<kNumCols; i++)
			// {
			// 	cout << " : " << maze[p.row][i];
			// }
			// cout << endl;
			maze[p.row][p.col] = mark!='S' ? 'X' : 'S';
			
			//옆으로 이동 : right
			if(p.col<kNumCols-2)
			{
				maze[p.row][p.col] = 'X';
				int new_col = p.col+1;
				RecurMaze({p.row,new_col});
			}
			//옆으로 이동 : left
			// else if(p.col>0 && direct=='l')
			// {
			// 	cout << " left mark ? " << mark << endl;
			// 	maze[p.row][p.col] = 'X';
			// 	int new_col = p.col-1;
			// 	RecurMaze({p.row,new_col});
			// }			
			//bakward to left
			else if(p.col==kNumCols-2)
			{
				// int new_row = p.row+1;
				// RecurMaze({new_row,1});
				//direct='l';
				cout << " left start row ? " << p.row << endl;
				//int new_col = p.col-1;
				RecurMaze({p.row,0});
			}
		}
		else if (maze[p.row+1][p.col] == '0')
		{
			//'X' 표시
			maze[p.row][p.col] = mark!='S' ? 'X' : 'S';

			int new_row = p.row+1;
			cout << " has a path in bottom " << new_row << endl;
			RecurMaze({new_row,p.col});
		}

	}
	// '1'
	else
	{
		//옆으로 이동
		if(p.col<kNumCols-2)
		{
			int new_col = p.col+1;
			RecurMaze({p.row,new_col});
		}
		//forward bottom
		else if(p.col==kNumCols-2)
		{
			int new_row = p.row+1;
			//cout << " new_row " << new_row << endl;
			RecurMaze({new_row,1});
		}
	}
}

//조기 종료가 가능한 버전
//int RecurMaze(Pos p)
//{
//	// TODO:
//}

void StackMaze()
{
	Stack<Pos> s;

	//Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;
	//s.Push(start); // s.Push({1, 1});

	for(int i=kNumRows-1; i>-1; --i)
	{
		for(int j=kNumCols-1; j>-1; --j)
		{
			const char mark = maze[i][j];

			if( mark=='0' )
			{
				Pos pos_top = { i-1 , j };
				Pos pos_bottom = { i+1 , j };
				Pos pos_right = { i , j+1 };
				Pos pos_left = { i , j-1 };

				const char mark_top = maze[pos_top.row][pos_top.col];
				const char mark_bottom = maze[pos_bottom.row][pos_bottom.col];
				const char mark_right = maze[pos_right.row][pos_right.col];
				const char mark_left = maze[pos_left.row][pos_left.col];
				
				//if(mark_top=='0' || mark_bottom=='0' || mark_right=='0' || mark_left=='0')
				{
					s.Push(pos_top);
					s.Push(pos_bottom);
					s.Push(pos_right);
					s.Push(pos_left);
				}

			}
		}
	}
	
	cout << " s capacity_ " << s.Size() << endl;
	s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		
		const char mark = maze[p.row][p.col];
		
		//const bool bool_found_g = mark == 'G';

		if (mark == 'G')
		{
			cout << "Found! G" << endl;
			cout << "index : s.getTopPos()%4 " << s.getTopPos()%4 << endl;
				if((s.getTopPos()%4) == 3)
				{
				//top
					// mark original pos to X
					if ( maze[p.row+1][p.col] != '1' ) maze[p.row+1][p.col] = 'X';
					// top pos
					//maze[p.row][p.col] = 'X';
				}
				else if((s.getTopPos()%4) == 2)
				{
					//bottom
					// mark original pos to X
					if ( maze[p.row-1][p.col] != '1' ) maze[p.row-1][p.col] = 'X';
					// bottom pos
					//maze[p.row][p.col] = 'X';
				}
				else if((s.getTopPos()%4) == 1)
				{
					//right
					if ( maze[p.row][p.col-1] != '1' ) maze[p.row][p.col-1] = 'X';
					//maze[p.row][p.col] = 'X';
				}
				else if((s.getTopPos()%4) == 0)
				{
					//left
					if ( maze[p.row][p.col+1] != '1' ) maze[p.row][p.col+1] = 'X';
					//maze[p.row][p.col] = 'X';
				}			
			break;
		}
		// TODO :
		else if (mark != 'G')
		{
			if((s.getTopPos()%4) == 3)
			{
				//top
				if(mark=='0')
				{
					// mark original pos to X
					if ( maze[p.row+1][p.col] != '1' ) maze[p.row+1][p.col] = 'X';
					// top pos
					maze[p.row][p.col] = 'X';
				}
			}
			else if((s.getTopPos()%4) == 2)
			{
				//bottom
				if(mark=='0')
				{
					// mark original pos to X
					if ( maze[p.row-1][p.col] != '1' ) maze[p.row-1][p.col] = 'X';
					// bottom pos
					maze[p.row][p.col] = 'X';
				}
			}
			else if((s.getTopPos()%4) == 1)
			{
				//right
				if(mark=='0')
				{
					if ( maze[p.row][p.col-1] != '1' ) maze[p.row][p.col-1] = 'X';
					maze[p.row][p.col] = 'X';
				}
			}
			else if((s.getTopPos()%4) == 0)
			{
				//left
				if(mark=='0')
				{
					if ( maze[p.row][p.col+1] != '1' ) maze[p.row][p.col+1] = 'X';
					maze[p.row][p.col] = 'X';
				}
			}
		}

	s.Pop();

	}
}

int main()
{
	PrintMaze();

	RecurMaze({ 1, 1 });

	//StackMaze();

	PrintMaze();

	return 0;
}

