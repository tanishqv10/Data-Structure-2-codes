//============================================================================
// Name        : binary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

//recursive binary tree

class treenode{
	char data[10];
	treenode *left;
	treenode *right;
	friend class tree;
};
class stack{
	int top;
	treenode *data[30];
	public:
	stack(){
		top=-1;
	}

	void push(treenode *temp);
	treenode *pop();
	int empty();
	friend class tree;
};

void stack::push(treenode* temp)
{
	top++;
	data[top]= temp;
}
treenode* stack::pop()
{
	treenode* curr;
	curr = data[top];
	top--;
	return curr;
}
int stack::empty()
{
	if(top==-1)
		return 1;
	return 0;
}

class queue
{
	int front,rear;
	treenode *que[30];
public:
	queue()
{
		front=-1;
		rear=-1;
}
	int isempty()
	{
		if(front==rear)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	void enq(treenode* temp)
	{
		rear++;
		que[rear]=temp;
	}
	treenode* deq()
	{
		treenode *t;
		front++;
		t=que[front];
		return t;
	}
};

class tree{
	treenode *root;
public:
	tree()
	{
		root=NULL;
	}
	void create_r();
	void create_r(treenode *);
	void pre_btree();
	void pre_btree(treenode *);
	void in_btree();
	void in_btree(treenode *);
	void post_btree();
	void post_btree(treenode *);
	//non-recursive
	void create_nr();
	void preorder();
	void inorder();
	void postorder();
	void bfs();
};

//recursive binary tree

void tree::create_r(){
	 	if(root==NULL)
	 	{
	 		root=new treenode();
	 		cout<<"enter the data: "<<endl;
	 		cin>>root->data;
	 		root->left=root->right=NULL;
	 	}
	 	create_r(root);
};

void tree::create_r(treenode *temp)
{
	char ch;
	treenode *curr;
	cout<<"Do you add node on left side of root(y/Y)?"<<temp->data<<endl;
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		curr=new treenode();
		cout<<"enter the data: "<<endl;
		cin>>curr->data;
		curr->left=curr->right=NULL;
		if(temp->left==NULL)
		{
			temp->left=curr;
		}
		create_r(temp->left);
	}
	cout<<"Do you add node on right side of root(y/Y)?"<<temp->data<<endl;
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		curr=new treenode();
		cout<<"enter the data: "<<endl;
		cin>>curr->data;
		curr->left=curr->right=NULL;
		if(temp->right==NULL)
		{
			temp->right=curr;
		}
		create_r(temp->right);
	}
};

void tree::pre_btree(){
	pre_btree(root);
	cout<<endl;
};

void tree::pre_btree(treenode *temp)
{
	if(temp!=NULL)
	{
		cout<<temp->data<<"\t";
		pre_btree(temp->left);
		pre_btree(temp->right);
	}
};

void tree::in_btree(){
	in_btree(root);
	cout<<endl;
};

void tree::in_btree(treenode *temp)
{
	if(temp!=NULL)
	{
		in_btree(temp->left);
		cout<<temp->data<<"\t";
		in_btree(temp->right);
	}
};

void tree::post_btree(){
	post_btree(root);
	cout<<endl;
};

void tree::post_btree(treenode *temp)
{
	if(temp!=NULL)
	{
		post_btree(temp->left);
		post_btree(temp->right);
		cout<<temp->data<<"\t";
	}
};

//non-recursive binary tree


void tree::create_nr()
{
	treenode* curr;
	treenode* temp;
	int flag=0;
	char ch,c;
 	root=new treenode();
 	cout<<"Enter the data for root: "<<endl;
 	cin>>root->data;
	do
	{
 		temp=root;
 		flag=0;
 		curr= new treenode();
 		cout<<"Enter data for node: "<<endl;
 		cin>>curr->data;
 		curr->left=curr->right=NULL;
 		while(flag==0)
 		{
 			cout<<"Where do you want to add data(l/L for left and r/R for right)? "<<temp->data<<endl;
 			cin>>ch;

 			if(ch=='l' || ch=='L')
 			{
 				if(temp->left==NULL)
 				{
 					temp->left=curr;
 					flag=1;
 				}
 				temp=temp->left;
 			}
 			else
 			{
 				if(ch=='r' || ch=='R')
 				{
 					if(temp->right==NULL)
 					{
 						temp->right=curr;
 						flag=1;
 					}
 					temp=temp->right;
 				}
			}
 		}  //end of while
 		cout<<"Do you want to continue?(y for yes) "<<endl;
 		cin>>c;
	}while(c=='y');
}

void tree::inorder()
{
	stack st;
	treenode* temp=root;
	while(1)
	{
		while(temp!=NULL)
		{
			st.push(temp);
			temp=temp->left;
		}
		if(st.empty())
		{
			break;
		}
		temp=st.pop();
		cout<<temp->data<<"\t";
		temp=temp->right;
	}
	cout<<"\n";
}

void tree::preorder()
{
	stack st;
	treenode* temp=root;
	while(1)
	{
		while(temp!=NULL)
		{
			cout<<temp->data<<"\t";
			st.push(temp);
			temp=temp->left;
		}
		if(st.empty())
		{
			break;
		}
		temp=st.pop();
		temp=temp->right;
	}
	cout<<"\n";
}

void tree::postorder()
{
	stack st;
	treenode* temp=root;
	while(1)
	{
		while(temp!=NULL)
		{
			st.push(temp);
			temp=temp->left;
		}
		if(st.data[st.top]->right==NULL)
		{
			temp=st.pop();
			cout<<temp->data<<"\t";
		}
		while(!st.empty() && st.data[st.top]->right==temp)
		{
			temp=st.pop();
			cout<<temp->data<<"\t";
		}
		if(st.empty())
		{
			break;
		}
		temp=st.data[st.top]->right;
	}
}

//breadth first traversal

void tree::bfs()
{
	queue q;
	treenode *temp;
	temp=root;
	q.enq(temp);
	while(!q.isempty())
	{
		temp=q.deq();
		cout<<temp->data<<"\t";
		if(temp->left!=NULL)
		{
			q.enq(temp->left);
		}
		if(temp->right!=NULL)
		{
			q.enq(temp->right);
		}
	}
}

int main() {
	tree t;
	int n;
	cout<<"Enter choice:"<<endl;
	do{
		cout<<"1.Enter to create binary tree using recursive function"<<endl<<"2.Display recursive binary tree"<<endl<<"3.Enter to create binary tree using non recursive"<<endl<<"4.Display non recursive binary tree "<<endl<<"5.Display bfs "<<endl;
		cin>>n;
		switch(n)
		{
		case 1:t.create_r();
			break;
		case 2:cout<<"preorder display of binary tree is:"<<endl;
			t.pre_btree();
			cout<<"inorder display of binary tree is:"<<endl;
			t.in_btree();
			cout<<"postorder display of binary tree is:"<<endl;
			t.post_btree();
			cout<<endl;
			break;
		case 3:t.create_nr();
			break;
		case 4:cout<<"preorder display of binary tree is:"<<endl;
			t.preorder();
			cout<<"inorder display of binary tree is:"<<endl;
			t.inorder();
			cout<<"postorder display of binary tree is:"<<endl;
			t.postorder();
			cout<<endl;
			break;
		case 5:cout<<"BFS Display is: "<<endl;
			t.bfs();
			cout<<endl;
			break;
		default:cout<<"Wrong choice!!"<<endl;
		}
	}while(n<6);
	return 0;
}


//output
/*
 * Enter choice:
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
1
enter the data:
1
Do you add node on left side of root(y/Y)?1
y
enter the data:
2
Do you add node on left side of root(y/Y)?2
y
enter the data:
3
Do you add node on left side of root(y/Y)?3
n
Do you add node on right side of root(y/Y)?3
n
Do you add node on right side of root(y/Y)?2
n
Do you add node on right side of root(y/Y)?1
y
enter the data:
4
Do you add node on left side of root(y/Y)?4
n
Do you add node on right side of root(y/Y)?4
y
enter the data:
5
Do you add node on left side of root(y/Y)?5
n
Do you add node on right side of root(y/Y)?5
n
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
2
preorder display of binary tree is:
1	2	3	4	5
inorder display of binary tree is:
3	2	1	4	5
postorder display of binary tree is:
3	2	5	4	1

1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
5
BFS Display is:
1	2	4	3	5
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
3
Enter the data for root:
10
Enter data for node:
20
Where do you want to add data(l/L for left and r/R for right)? 10
l
Do you want to continue?(y for yes)
y
Enter data for node:
30
Where do you want to add data(l/L for left and r/R for right)? 10
r
Do you want to continue?(y for yes)
y
Enter data for node:
40
Where do you want to add data(l/L for left and r/R for right)? 10
l
Where do you want to add data(l/L for left and r/R for right)? 20
l
Do you want to continue?(y for yes)
y
Enter data for node:
50
Where do you want to add data(l/L for left and r/R for right)? 10
r
Where do you want to add data(l/L for left and r/R for right)? 30
r
Do you want to continue?(y for yes)
n
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
4
preorder display of binary tree is:
10	20	40	30	50
inorder display of binary tree is:
40	20	10	30	50
postorder display of binary tree is:
40	20	50	30	10
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
5
BFS Display is:
10	20	30	40	50
1.Enter to create binary tree using recursive function
2.Display recursive binary tree
3.Enter to create binary tree using non recursive
4.Display non recursive binary tree
5.Display bfs
 */

