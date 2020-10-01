//============================================================================
// Name        : skew.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

class treenode
{
    char data[50];
    treenode *left;
    treenode *right;
    friend class tree;
};

class tree
{
    treenode *root;
    public:
    tree()
    {
    root=NULL;
    }
    void create_r();
    void create_r(treenode *);
    void right_driver();
    void right_side(treenode *);
    void right_side_view(treenode *,int , int *);
    void left_driver();
    void left_side(treenode *);
    void left_side_view(treenode *,int , int *);
};

void tree::create_r()
{
    root=new treenode;
    cout<<"Enter the data for the root node:"<<endl;
    cin>>root->data;
    root->left=root->right=NULL;
    create_r(root);
}
void tree::create_r(treenode *temp)
{
    char r,l;
    treenode *curr;
    cout<<"You want to add to left side of node "<<temp->data<<"?"<<endl<<"Enter (Y/y) for yes and (N/n) for no"<<endl;
    cin>>l;
    if(l=='y' || l=='Y')
    {
        curr=new treenode;
        cout<<"Enter the data for node:"<<endl;
        cin>>curr->data;
        curr->left=curr->right=NULL;
        temp->left=curr;
        create_r(curr);
    }
    cout<<"You want to add to right side of node "<<temp->data<<"?"<<endl<<"Enter (Y/y) for yes and (N/n) for no:"<<endl;
    cin>>r;
    if(r=='y' || r=='Y')
    {
        curr=new treenode;
        cout<<"Enter the data for node:"<<endl;
        cin>>curr->data;
        curr->left=curr->right=NULL;
        temp->right=curr;
        create_r(curr);
    }
}

void tree::right_driver()
{
    right_side(root);
}

void tree::right_side(treenode *root)
{
    int max = 0;
    right_side_view(root, 1, &max);
}

void tree::right_side_view(treenode *root, int level, int *max)
{
    if (root == NULL) return;
    if (*max < level)
    {
        cout << root->data << "\t";
        *max = level;
    }
    right_side_view(root->right, level + 1, max);
    right_side_view(root->left, level + 1, max);
}

void tree::left_driver()
{
    left_side(root);
}

void tree::left_side(treenode *root)
{
    int max= 0;
    left_side_view(root, 1, &max);
}

void tree::left_side_view(treenode *root, int level, int *max)
{
    if (root == NULL) return;
    if (*max < level)
    {
        cout << root->data << "\t";
        *max = level;
    }
    left_side_view(root->right, level + 1, max);
    left_side_view(root->left, level + 1, max);
}

int main()
{
	char ch1,ch;
	tree bt;
	do
	{
		bt.create_r();
		cout<<"You are standing on which side? "<<endl;
		cin>>ch;
		if(ch=='r'|| ch=='R')
		{
			bt.right_driver();
		}
		else
		{
			bt.left_driver();
		}
		cout<<endl;
		cout<<"Do you want to continue (Y/y)"<<endl;
		cin>>ch1;
	}while(ch1=='Y'|| ch1=='y');

	return 0;
}

/* OUTPUT
 * Enter the data for the root node:
1
You want to add to left side of node 1?
Enter (Y/y) for yes and (N/n) for no
y
Enter the data for node:
100
You want to add to left side of node 100?
Enter (Y/y) for yes and (N/n) for no
n
You want to add to right side of node 100?
Enter (Y/y) for yes and (N/n) for no:
y
Enter the data for node:
200
You want to add to left side of node 200?
Enter (Y/y) for yes and (N/n) for no
y
Enter the data for node:
300
You want to add to left side of node 300?
Enter (Y/y) for yes and (N/n) for no
y
Enter the data for node:
400
You want to add to left side of node 400?
Enter (Y/y) for yes and (N/n) for no
n
You want to add to right side of node 400?
Enter (Y/y) for yes and (N/n) for no:
n
You want to add to right side of node 300?
Enter (Y/y) for yes and (N/n) for no:
n
You want to add to right side of node 200?
Enter (Y/y) for yes and (N/n) for no:
n
You want to add to right side of node 1?
Enter (Y/y) for yes and (N/n) for no:
y
Enter the data for node:
500
You want to add to left side of node 500?
Enter (Y/y) for yes and (N/n) for no
n
You want to add to right side of node 500?
Enter (Y/y) for yes and (N/n) for no:
y
Enter the data for node:
600
You want to add to left side of node 600?
Enter (Y/y) for yes and (N/n) for no
n
You want to add to right side of node 600?
Enter (Y/y) for yes and (N/n) for no:
n
You are standing on which side?
r
1	500	600	300	400
Do you want to continue (Y/y)
n
 */
