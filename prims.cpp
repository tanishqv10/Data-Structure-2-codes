//============================================================================
// Name        : prims.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
using namespace std;

#define dm 10
#define in 99999

class graph
{
	int n;
	int wt;
	int cost_mat[dm][dm];
	int adj_mat[dm][dm];
	int parent_arr[dm];
public:
	void create();
	void dis_adj_mat();
	void dis_cost_mat();
	void prims_algo();
	int prims_algo(int st);
};

void graph::create()
{
	int st;
	int dt;
	char ch;
	int tem;
	cout<<"Enter the number of vertices:"<<endl;
	cin>>n;
	int cou=n;
	do
	{
		cout<<"Enter the starting vertex: "<<endl;
		cin>>st;
		cout<<"Enter the destination vertex: "<<endl;
		cin>>dt;
		cout<<"Enter the cost of edge: "<<st<<" and "<<dt<<" ";
		cin>>tem;
		cost_mat[st-1][dt-1]=cost_mat[dt-1][st-1]=tem;
		adj_mat[st-1][dt-1]=adj_mat[dt-1][st-1]=1;
		cou--;
		cout<<"Enter y/Y if you want to add new edge: ";
		cin>>ch;
	}
	while((ch=='y'||ch=='Y')&&cou>0);

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(adj_mat[i][j]!=1)
			{
				cost_mat[i][j]=cost_mat[j][i]=in;
				adj_mat[i][j]=adj_mat[j][i]=0;
			}
		}
	}
	cout<<"GRAPH CREATION COMPLETE!!!\n";
}

void graph::dis_adj_mat()
{
	cout<<"ADJACENCY MATRIX: \n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<adj_mat[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

void graph::dis_cost_mat()
{
	cout<<"COST MATRIX: \n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<cost_mat[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

void graph::prims_algo()
{
	int k;
	int res_cost;
	cout<<"Vertices present in graph\n";
	for(int i=0;i<n;i++)
	{
		cout<<(i+1)<<"\t";
	}
	cout<<"\n";
	cout<<"Enter the starting vertex: >";
	cin>>k;
	res_cost=prims_algo(k);
	cout<<"Cost of minimum spanning tree="<<res_cost<<"\n";
}

int graph::prims_algo(int st)
{
	int near[n];
	int min;
	int ver[n-1][n-1];
	int min_cost;
	int c,d;
	for(int i=0;i<n;i++)
	{
		near[i]=0;
	}
	near[st]=-1;
	for(int i=0;i<n;i++)
	{
		if(i!=st)
		{
			near[i]=st;
		}
	}

	d=0;
	min_cost=0;
	for(int i=1;i<n;i++)
	{
		min=in;
		for(int j=0;j<n;j++)
		{
			if(near[j]!=-1&&cost_mat[j][near[j]]<min)
			{
				c=j;
				min=cost_mat[j][near[j]];
			}
		}
		ver[d][0]=c;
		ver[d][1]=near[c];
		d++;
		min_cost=min_cost+cost_mat[c][near[c]];
		near[c]=-1;
		for(int j=0;j<n;j++)
		{
			if(near[j]!=-1&&cost_mat[j][near[j]]>cost_mat[j][c])
			{
				near[j]=c;
			}
		}
	}

	return min_cost;
}

int main()
{
	graph gp;
	int ch;
	do{
		cout<<"Enter choice: "<<endl;
		cout<<"1. Enter to create\n2. Enter to display adjacency matrix\n3. Enter to display cost matrix\n4. Enter for prims algorithm"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:gp.create();
				break;
			case 2:gp.dis_adj_mat();
				break;
			case 3:gp.dis_cost_mat();
				break;
			case 4:gp.prims_algo();
				break;
			default:cout<<"Wrong Choice!!"<<endl;
		}
	}while(ch<5);
	return 0;
}


/*

OUTPUT:
Enter choice:
1. Enter to create
2. Enter to display adjacency matrix
3. Enter to display cost matrix
4. Enter for prims algorithm
1
Enter the number of vertices:
5
Enter the starting vertex:
3
Enter the destination vertex:
1
Enter the cost of edge: 3 and 1 7
Enter y/Y if you want to add new edge: y
Enter the starting vertex:
2
Enter the destination vertex:
1
Enter the cost of edge: 2 and 1 2
Enter y/Y if you want to add new edge: y
Enter the starting vertex:
1
Enter the destination vertex:
4
Enter the cost of edge: 1 and 4 1
Enter y/Y if you want to add new edge: y
Enter the starting vertex:
4
Enter the destination vertex:
5
Enter the cost of edge: 4 and 5 3
Enter y/Y if you want to add new edge: n
GRAPH CREATION COMPLETE!!!
Enter choice:
1. Enter to create
2. Enter to display adjacency matrix
3. Enter to display cost matrix
4. Enter for prims algorithm
2
ADJACENCY MATRIX:
0	1	1	1	0
1	0	0	0	0
1	0	0	0	0
1	0	0	0	1
0	0	0	1	0
Enter choice:
1. Enter to create
2. Enter to display adjacency matrix
3. Enter to display cost matrix
4. Enter for prims algorithm
3
COST MATRIX:
99999	2	7	1	99999
2	99999	99999	99999	99999
7	99999	99999	99999	99999
1	99999	99999	99999	3
99999	99999	99999	3	99999
Enter choice:
1. Enter to create
2. Enter to display adjacency matrix
3. Enter to display cost matrix
4. Enter for prims algorithm
4
Vertices present in graph
1	2	3	4	5
Enter the starting vertex: >4
Cost of minimum spanning tree=13
Enter choice:
1. Enter to create
2. Enter to display adjacency matrix
3. Enter to display cost matrix
4. Enter for prims algorithm

*/
