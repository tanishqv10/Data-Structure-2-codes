//============================================================================
// Name        : graph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

class gnode
{

	int vertex;
	gnode *next;
	friend class graph;
	friend class stack;
	friend class queue;
};

class stack
{
	public:
stack()
{
	int top=-1;
}
int empty()
{
	int top;
	if( top==-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void push(int temp)
{
	int top;
	int data[30];
	if( top!=29)
	{
		top++;
		data[top] =temp;
	}
}
int pop()
{
	int top;
	int data[30];
	int temp;
	temp=data[top];
	top--;
	return temp;
}
};
class queue
{
int rear,front;
int data2[30];
public:

queue()
{
	front=-1;
	rear=-1;
}
int isempty()
{
	if(front==rear)
	return 1;
	else
	return 0;
}
int isfull()
{
	if(rear==29)
	return 1;
	else
	return 0;
}
void enqueue(int a)
{
	if(isfull()!=1)
	{
		rear++;
		data2[rear]=a;
	}
}
int dequeue()
{
	if(isempty()!=1)
	{
		front++;
		int temp=data2[front];
		return temp;
	}
	return NULL;
}
};

class graph
{
	gnode *head[20];
	int n,i;
	int visited[20];
	public :
		graph()
		{
			for(i=0;i<20;i++)
			{
				head[i]=NULL;
			}
		}
		void create();
		void dfs();
		void dfs(int v);
		void dfs_nr(int v);
		void bfs(int v);
};

void graph :: create()
{
	cout<<"Enter the number of vertices: "<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		head[i]=new gnode();
		head[i]->vertex=i;
		head[i]->next=NULL;
	}
	gnode *temp;
	char ch;
	for(int i=0;i<n;i++)
	{
		temp=head[i];
		do
		{
			int v;
			cout<<"Enter the adjacent vertex of "<<i<<endl;
			cin>>v;
			if(v==i)
				cout<<"Self loops are not allowed"<<endl;
			else
			{
				gnode *curr=new gnode();
				curr->vertex=v;
				temp->next=curr;
				temp=curr;
				temp->next=NULL;
			}
			cout<<"Enter y/Y to continue or n/N to go to next vertex "<<endl;
			cin>>ch;
		}while(ch=='y'||ch=='Y');
	}
}

void graph :: dfs()
{
	int v;
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
	}
	cout<<"Enter the starting vertex for dfs: "<<endl;
	cin>>v;
	cout<<"DFS traversal of graph is: "<<endl;
	dfs(v);
}

void graph :: dfs(int v)
{
	cout<<v<<"  ";
	visited[v]=1;
	gnode *temp=head[v];
	while(temp!=NULL)
	{
		int w=temp->vertex;
		if(!visited[w])
		dfs(w);
		temp=temp->next;
	}
}

void graph :: dfs_nr(int v)
{
	stack st;
	for(int i=0;i<n;i++)
		visited[i]=0;
	st.push(v);
	do
	{
		v=st.pop();
		if(!visited[v])
		{
		cout<<v<<"  ";
		visited[v]=1;
		}
		label : gnode *temp=head[v];
		while(temp!=NULL)
		{
		int w=temp->vertex;
		if(!visited[w])
		{
		st.push(w);
		cout<<w<<"  ";
		v=w;
		visited[w]=1;
		goto label;
		}
		temp=temp->next;
		}
	}while(st.empty()!=1);
}

void graph :: bfs(int v)
{
	for(int i=0;i<n;i++)
		visited[i]=0;
	queue q;
	q.enqueue(v);
	visited[v]=1;
	while(!q.isempty())
	{
		v=q.dequeue();
		cout<<v<<"  ";
		gnode *temp=head[v];
		while(temp!=NULL)
		{
			int w=temp->vertex;
			if(!visited[w])
			{
				q.enqueue(w);
				visited[w]=1;
			}
			temp=temp->next;
		}
	}
}

int main()
{
	int v,ch;
	graph t1;
	while(1)
	{
		cout<<"1.Enter to create graph\n2.Enter for recursive traversal of graph\n3.Enter for non recursive traversal of graph\n4.Enter for BFS traversal of graph"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:t1.create();
				break;
			case 2:t1.dfs();
					cout<<endl;
					break;
			case 3:cout<<"Enter the starting vertex for non-recursive DFS: "<<endl;
					cin>>v;
					cout<<"DFS traversal of graph is: "<<endl;
					t1.dfs_nr(v);
					cout<<endl;
					break;
			case 4:
				cout<<"Enter the starting vertex for BFS: "<<endl;
				cin>>v;
				cout<<"BFS traversal of graph is: "<<endl;
				t1.bfs(v);
				cout<<endl;
				break;
			default:cout<<"Wrong choice!!"<<endl;
		}
	}
	return 0;
}



/*
1.Enter to create graph
2.Enter for recursive traversal of graph
3.Enter for non recursive traversal of graph
4.Enter for BFS traversal of graph
1
Enter the number of vertices:
5
Enter the adjacent vertex of 0
1
Enter y/Y to continue or n/N to go to next vertex
y
Enter the adjacent vertex of 0
2
Enter y/Y to continue or n/N to go to next vertex
n
Enter the adjacent vertex of 1
2
Enter y/Y to continue or n/N to go to next vertex
n
Enter the adjacent vertex of 2
0
Enter y/Y to continue or n/N to go to next vertex
y
Enter the adjacent vertex of 2
3
Enter y/Y to continue or n/N to go to next vertex
n
Enter the adjacent vertex of 3
4
Enter y/Y to continue or n/N to go to next vertex
n
Enter the adjacent vertex of 4
4
Self loops are not allowed
Enter y/Y to continue or n/N to go to next vertex
n
1.Enter to create graph
2.Enter for recursive traversal of graph
3.Enter for non recursive traversal of graph
4.Enter for BFS traversal of graph
2
Enter the starting vertex for dfs:
2
DFS traversal of graph is:
2  0  1  3  4
1.Enter to create graph
2.Enter for recursive traversal of graph
3.Enter for non recursive traversal of graph
4.Enter for BFS traversal of graph
3
Enter the starting vertex for non-recursive DFS:
2
DFS traversal of graph is:
2  0  1  3  4
1.Enter to create graph
2.Enter for recursive traversal of graph
3.Enter for non recursive traversal of graph
4.Enter for BFS traversal of graph
4
Enter the starting vertex for BFS:
2
BFS traversal of graph is:
2  0  3  1  4
1.Enter to create graph
2.Enter for recursive traversal of graph
3.Enter for non recursive traversal of graph
4.Enter for BFS traversal of graph

*/
