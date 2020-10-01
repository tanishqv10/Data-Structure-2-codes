//============================================================================
// Name        : thread.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
using namespace std;

class tbtnode{
        char data[20];
        bool rbit;
        bool lbit;
        tbtnode *right;
        tbtnode *left;
        friend class tbt;
};

class tbt
{
        tbtnode *head;
        tbtnode *root;
        public:tbt()
        {
        	root=NULL;
        }
        void create();
        void inorder();
        tbtnode* insuccr(tbtnode *temp);
        void preorder();
};


void tbt::create()
{
        tbtnode *curr,*temp;
        char ch,c;
        head=new tbtnode();
        root=new tbtnode();
        cout<<"Enter data in root: "<<endl;
        cin>>root->data;
        head->lbit=0;
        head->rbit=0;
        head->left=root;
        head->right=head;
        root->left=root->right=head;
        root->lbit=root->rbit=1;
        do{
                int flag=0;
                temp=root;
                curr=new tbtnode();
                cout<<"Enter current data: "<<endl;
                cin>>curr->data;
                while(flag==0)
                {
                        cout<<"Enter choice for left and right(l/r) : "<<endl;
                        cin>>ch;
                        if(ch=='l'||ch=='L')
                        {
                                if(temp->lbit==1)
                                {
                                        curr->right=temp;
                                        curr->left=temp->left;
                                        temp->left=curr;
                                        temp->lbit=0;
                                        curr->lbit=curr->rbit=1;
                                        flag=1;
                                }
                                else
                                {
                                        temp=temp->left;
                                }
                        }
                        else
                        {
							if(ch=='r'||ch=='R')
							{
									if(temp->rbit==1)
									{
											curr->left=temp;
											curr->right=temp->right;
											temp->right=curr;
											temp->rbit=0;
											curr->lbit=curr->rbit=1;
											flag=1;
									}
									else
									{
											temp=temp->right;
									}
							}
                        }

                }
                cout<<"Do you want to continue?(y/n): "<<endl;
                cin>>c;
        }while(c=='y'||c=='Y');
}

void tbt::inorder()
{
    tbtnode *temp;
	temp=head;
        while(1)
        {
                temp=insuccr(temp);
                if(temp==head)
                {
                        break;
                }
                cout<<temp->data<<"\t";
        }
}

tbtnode* tbt::insuccr(tbtnode *temp)
{
    tbtnode* x;
	x=temp->right;
    if(temp->rbit==0)
    {
    	while(x->lbit==0)
        {
    		x=x->left;
        }
    }
    return x;
}

void tbt::preorder()
{
	tbtnode *temp;
	temp=head->left;
	while(temp!=head)
	{
		cout<<temp->data<<"\t";
		while(temp->lbit==0)
		{
			temp=temp->left;
			cout<<temp->data<<"\t";
		}
		while(temp->rbit==1)
		{
			temp=temp->right;
		}
		temp=temp->right;
	}
}

int main()
{
    tbt t;
    int n;
    do{
    	cout<<"Enter your choice"<<endl;
    	cout<<"1. Enter to create tbt \n2. Enter for inorder display \n3. Enter for preorder display "<<endl;
    	cin>>n;
    	switch(n)
    	{
    	case 1: t.create();
    		break;
    	case 2: cout<<"Inorder display is: "<<endl;
    		t.inorder();
    		cout<<endl;
    		break;
    	case 3: cout<<"Preorder display is: "<<endl;
    		t.preorder();
    		cout<<endl;
    		break;
    	default: cout<<"Wrong choice!!"<<endl;
    	}
    }while(n<5);

    return 0;
}


//OUTPUT:-

/*
 * Enter your choice
1. Enter to create tbt
2. Enter for inorder display
3. Enter for preorder display
1
Enter data in root:
10
Enter current data:
20
Enter choice for left and right(l/r) :
l
Do you want to continue?(y/n):
y
Enter current data:
30
Enter choice for left and right(l/r) :
l
Enter choice for left and right(l/r) :
l
Do you want to continue?(y/n):
y
Enter current data:
40
Enter choice for left and right(l/r) :
r
Do you want to continue?(y/n):
y
Enter current data:
50
Enter choice for left and right(l/r) :
r
Enter choice for left and right(l/r) :
r
Do you want to continue?(y/n):
y
Enter current data:
60
Enter choice for left and right(l/r) :
r
Enter choice for left and right(l/r) :
l
Do you want to continue?(y/n):
n
Enter your choice
1. Enter to create tbt
2. Enter for inorder display
3. Enter for preorder display
2
Inorder display is:
30	20	10	60	40	50
Enter your choice
1. Enter to create tbt
2. Enter for inorder display
3. Enter for preorder display
3
Preorder display is:
10	20	30	40	60	50
Enter your choice
1. Enter to create tbt
2. Enter for inorder display
3. Enter for preorder display
 */
