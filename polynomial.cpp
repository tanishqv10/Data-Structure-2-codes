//============================================================================
// Name        : polynomial.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<math.h>
using namespace std;
class node
{
	int exp,coe;
	node *next;
	friend class poly;
};

class poly
{
	node *h;
public:
	poly()
	{
		h=new node();
		h->coe=0;
		h->exp=-1;
		h->next=h;
	}
	void create_poly();
	void display_poly();
	void sort();
	void reverse();
	void add_poly(poly,poly);
	void eval_poly(poly,int);
};

void poly::create_poly()
	{
		node *ptr;
		node *last;
		char ch;
		last=h;
		do
		{
			ptr=new node();
			cout<<"Enter the exponent of the term"<<endl;
			cin>>ptr->exp;
			cout<<"Enter the Coefficient of the term"<<endl;
			cin>>ptr->coe;
			last->next=ptr;
			ptr->next=h;
			last=ptr;
			cout<<"Do you want to enter a new term(Y/y)? "<<endl;
			cin>>ch;
		}while(ch=='y'||ch=='Y');
	};

void poly::sort()
{
    node *curr=h;
	node *index=NULL;
	int temp1,temp2;
	if(h==NULL)
	{
        cout<<"Linked List is empty"<<endl;
    }
    else
    {
        do{
            index=curr->next;
            while(index!=h)
            {
                if(curr->exp>index->exp)
                {
                    temp1 =curr->exp;
                    temp2 =curr->coe;
                    curr->exp= index->exp;
                    curr->coe= index-> coe;
                    index->exp = temp1;
                    index->coe = temp2;
                }
                index=index->next;
            }
            curr=curr->next;
        }while(curr->next!=h);
    }
}

void poly::reverse()
{
    node* prev1,*curr1,*next;
    prev1=NULL;
    curr1=h;
    while(curr1)
    {
        next=curr1->next;
        curr1->next=prev1;
        prev1=curr1;
        curr1=next;
    }
    h=prev1;
}

void poly::display_poly()
{
	node *temp;
	temp=h->next;
	cout<<"Polynomial is: "<<endl;
	do
	{
		cout<<temp->coe<<"x^"<<temp->exp;
		if(temp->next!= h)
		{
			cout<<"+";
		}
		temp=temp->next;
	}while(temp->exp!=(-1));
	cout<<endl;
};

void poly::add_poly(poly p1,poly p2)
{
	node *t1,*t2,*t3;
	node *ptr;
	t1=p1.h->next;
	t2=p2.h->next;
	t3=h;
	while(t1->exp!=(-1)||t2->exp!=(-1))
	{
		ptr=new node();
		if(t1->exp==t2->exp)
		{
			ptr->exp=t1->exp;
			ptr->coe=t1->coe+t2->coe;
			t3->next=ptr;
			t1=t1->next;
			t2=t2->next;
			t3=t3->next;
		}
		else if(t1->exp>t2->exp)
		{
			ptr->exp=t1->exp;
			ptr->coe=t1->coe;
			t3->next=ptr;
			t1=t1->next;
			t3=t3->next;
		}
		else
		{
			ptr->exp=t2->exp;
			ptr->coe=t2->coe;
			t3->next=ptr;
			t2=t2->next;
			t3=t3->next;
		}
	}
	t3->next=h;
};

void poly::eval_poly(poly p,int x)
{
	int sum;
	class node *t3;
	t3=p.h->next;
	while(t3!=h)
	{
		sum=sum+((t3->coe)*(pow(x,t3->exp)));
		t3=t3->next;
	}
	cout<<"Evaluated polynomial is : "<<sum<<endl;
}

int main()
{
	int ch,x;
	poly p,p1,p2,p3;
	do{
		cout<<"1.Enter to Create a Polynomial\n2.Enter for Addition of two Polynomials\n3.Enter to Evaluate the polynomial\n"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1: p.create_poly();
			        p.sort();
			        p.reverse();
					p.display_poly();
					break;
			case 2: cout<<"Enter the first polynomial: "<<endl;
					p1.create_poly();
			        p1.sort();
			        p1.reverse();
			        p1.display_poly();
			        cout<<"Enter the second polynomial: "<<endl;
					p2.create_poly();
					p2.sort();
					p2.reverse();
					p2.display_poly();
					p3.add_poly(p1,p2);
					cout<<"Addition of polynomials is: "<<endl;
					p3.display_poly();
					break;
			case 3: p.create_poly();
					p.sort();
					p.reverse();
					p.display_poly();
					cout<<"Enter the Value of x\n";
					cin>>x;
					p.eval_poly(p,x);
					break;
		}
	}while(ch<4);
	return 0;
}

//OUTPUT
/*
 * 1.Enter to Create a Polynomial
2.Enter for Addition of two Polynomials
3.Enter to Evaluate the polynomial

1
Enter the exponent of the term
3
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
5
Enter the Coefficient of the term
5
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
1
Enter the Coefficient of the term
3
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
6
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
n
Polynomial is:
2x^6+5x^5+2x^3+3x^1
1.Enter to Create a Polynomial
2.Enter for Addition of two Polynomials
3.Enter to Evaluate the polynomial

2
Enter the first polynomial:
Enter the exponent of the term
3
Enter the Coefficient of the term
3
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
6
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
5
Enter the Coefficient of the term
5
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
1
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
n
Polynomial is:
2x^6+5x^5+3x^3+2x^1
Enter the second polynomial:
Enter the exponent of the term
5
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
4
Enter the Coefficient of the term
4
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
6
Enter the Coefficient of the term
6
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
1
Enter the Coefficient of the term
3
Do you want to enter a new term(Y/y)?
n
Polynomial is:
6x^6+2x^5+4x^4+3x^1
Addition of polynomials is:
Polynomial is:
8x^6+7x^5+4x^4+3x^3+5x^1
1.Enter to Create a Polynomial
2.Enter for Addition of two Polynomials
3.Enter to Evaluate the polynomial

3
Enter the exponent of the term
4
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
5
Enter the Coefficient of the term
2
Do you want to enter a new term(Y/y)?
y
Enter the exponent of the term
1
Enter the Coefficient of the term
1
Do you want to enter a new term(Y/y)?
n
Polynomial is:
2x^5+2x^4+1x^1
Enter the Value of x
2
Evaluated polynomial is : 98
1.Enter to Create a Polynomial
2.Enter for Addition of two Polynomials
3.Enter to Evaluate the polynomial

 */
