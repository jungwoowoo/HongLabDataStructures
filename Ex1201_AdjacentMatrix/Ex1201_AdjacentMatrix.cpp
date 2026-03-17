#include <iostream>
#include <cassert>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph
{
public:
	struct Vertex // Node
	{
		T item = T();
	};

	AdjMatGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		matrix_ = new int* [max_vertices_];
		for (int r = 0; r < max_vertices_; r++) {
			matrix_[r] = new int[max_vertices_];
			for (int c = 0; c < max_vertices_; c++)
				matrix_[r][c] = 0;
		}

		vertices_ = new Vertex[max_vertices_];

		n_ = 0;
	}

	~AdjMatGraph()
	{
		delete[] vertices_;

		for (int i = 0; i < max_vertices_; i++)
			delete[] matrix_[i];
		delete[] matrix_;

		if (visited_)
			delete[] visited_;
	}

	void PrintMatrix()
	{
		using namespace std;
		if (n_)
			for (int r = 0; r < n_; r++) {
				for (int c = 0; c < n_; c++)
					cout << matrix_[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		// TODO:
		matrix_[u][v] = 1;
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
	}

	// recursive
	void DepthFirstTraversal(int v) // v는 인덱스
	{
		cout << v << " -> " << flush;		
		// TODO:
		int visited_count = 0;

		for(int i=0; i<max_vertices_; i++)
		{
			//cout << boolalpha;
			//cout << " ?? " << visited_[i] << flush;
			if(visited_[i]==true) visited_count++;
		}

		//cout << endl;

		//cout << "visited_count=" << visited_count << " max_vertices_=" << max_vertices_ << endl;

		if(visited_count==max_vertices_) return;
		else
		{
			visited_[v] = true;

			for(int i=0; i<=max_vertices_; i++)
			{
				//cout << boolalpha;
				//cout << " i " << i << " visited_[i]?? " << visited_[i] << " matrix_[v][i]?? " << matrix_[v][i] << endl;
				if(matrix_[v][i]==1 && visited_[i]==false)
				//if(matrix_[v][i]==1)
				{
					//cout << i << " will be visited " << flush;
					visited_[i] = true;
					DepthFirstTraversal(i);
				}
			}
		}
	}

	//
	void IterDFT()
	{
		// TODO:

		ResetVisited();
		Stack<T> stacks;

		int start = 0;
		stacks.Push(start);
		visited_[start] = true;

		while(!stacks.IsEmpty())
		{
			//stacks.Pop();
			int stacks_top = stacks.Top();
			stacks.Pop();

			for( int e = max_vertices_-1; e>=0; e--)
			{
				if( matrix_[stacks_top][e] == 1 && visited_[e] == false )
				{
					stacks.Push(e);
					visited_[e] = true;
				}
			}
			
			cout << stacks_top << " Stack : " << flush;

			stacks.Print();
		}		
		
	}


	/**
	 * 
	 * 	
	 * 0 Queue :1 2
		1 Queue :2 3 4
		2 Queue :3 4
		3 Queue :4 6
		4 Queue :6
		6 Queue :5
		5 Queue :
	*/
	
	void BreadthFirstTraversal()
	{
		int v = 0; // 0번에서 시작

		Queue<int> q(8);

		ResetVisited();

		// TODO:
		
		visited_[v] = true;
		q.Enqueue(v);

		while(!q.IsEmpty())
		{
			int visited_index = q.Front();

			for(int i=0; i<=max_vertices_; i++)
			{
				//cout << boolalpha;
				//cout << " i " << i << " visited_[i]?? " << visited_[i] << " matrix_[v][i]?? " << matrix_[v][i] << endl;
				if(matrix_[visited_index][i]==1 && visited_[i]==false)
				//if(matrix_[v][i]==1)
				{
					//cout << i << " will be visited " << flush;
					visited_[i] = true;
					q.Enqueue(i);
				}
			}

			cout << visited_index << " Queue : " << flush;

			q.Dequeue();			

			q.Print();

			cout << endl;
		}


		//visited_index = q.Front();

	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화
	}

private:
	int** matrix_ = nullptr;
	Vertex* vertices_ = nullptr;
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity

	bool* visited_ = nullptr;
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	/*
	// 위키피디아 버전
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);
	g.InsertEdge(3, 0);	g.InsertEdge(0, 3);
	g.InsertEdge(4, 0);	g.InsertEdge(0, 4);
	*/

	// 강의 영상 버전
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.PrintMatrix();

	// g.DepthFirstTraversal();
	// g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}