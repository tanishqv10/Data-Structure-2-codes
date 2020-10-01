//============================================================================
// Name        : heap.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <string.h>
using namespace std;

#define MAX 50

class Node
{
	int score;
	public:
		Node();
		friend class Heap;
};

Node::Node()
{
	score = 0;
}

class Heap
{
	Node *max_heap[MAX] = {NULL};		// used two heaps
	Node *min_heap[MAX] = {NULL};
	Node *minRoot, *maxRoot;
	public:
		Heap();
		void create();
		void insert();
		void getTop();
		void display();
		void min_reheap_up();
		void max_reheap_up();
		void min_reheap_down();
		void max_reheap_down();
		void heap_sort();
};

// initialize heap
Heap::Heap()
{
	minRoot = new Node();
	min_heap[minRoot->score] = minRoot; 	//
	minRoot->score++;
	maxRoot = new Node();
	max_heap[maxRoot->score] = maxRoot;
	maxRoot->score++;	//points to next available index in heap
}

// repeatedly call insert
void Heap::create()
{
	cout<<"\nEnter the marks of each student: "<<endl;
	char ch = 'y';
	int i = 0;
	while(ch =='y')
	{
		cout<<"Student: "<<i+1<<" > ";
		insert();
		i++;
		cout<<"Do you want to add more? \t";
		cin>>ch;
		ch = tolower(ch);
	}
}

// inserts a node to min tree and max tree
void Heap::insert()
{
	Node *n = new Node();
	cout<<"Enter marks: "<<endl;
	cin>>n->score;
	min_heap[minRoot->score] = n;
	minRoot->score++;
	min_reheap_up();				// re heapify
	max_heap[maxRoot->score] = n;
	maxRoot->score++;
	max_reheap_up();
}

// finds out the top of heap, which is min or max
void Heap::getTop()
{
	cout<<"The minimum marks is : "<<min_heap[1]->score<<endl;
	cout<<"The maximum marks is : "<<max_heap[1]->score<<endl;
}


// prints all data in heap
void Heap :: display() {
	cout<<"The Current Min-Heap is:\t";
	for(int i=1; i<minRoot->score; i++)
	{
		cout<<min_heap[i]->score<<" ";
	}
	cout<<endl;
	cout<<"The Current Max-Heap is:\t";
	for(int i=1; i<maxRoot->score; i++)
	{
		cout<<max_heap[i]->score<<" ";
	}
	cout<<endl;
}

// heapify from bottom, after insertion
void Heap::min_reheap_up()
{
	Node *temp;
	int i = minRoot->score - 1;
	while(i > 1 && min_heap[i]->score < min_heap[i/2]->score)
	{
		temp = min_heap[i];
		min_heap[i] = min_heap[i/2];
		min_heap[i/2] = temp;
		i = i / 2;
	}
}

// heapify from bottom, after insertion
void Heap::max_reheap_up()
{
	Node *temp;
	int i = maxRoot->score - 1;
	while(i > 1 && max_heap[i]->score > max_heap[i/2]->score)
	{
		temp = max_heap[i];
		max_heap[i] = max_heap[i/2];
		max_heap[i/2] = temp;
		i = i / 2;
	}
}

// heapify from top, after deletion
void Heap::min_reheap_down()
{
	int i = 1;
	Node *temp;
	while (2*i <= minRoot->score - 1)
	{
		int j = 2*i;
		if (j < minRoot->score-1 && min_heap[j+1]->score < min_heap[j]->score)
		{
			j++;
		}
		if (min_heap[i]->score <= min_heap[j]->score)
		{
			break;
		}
		else
		{							//if parent is greater than child then swap
			temp = min_heap[i];
			min_heap[i] = min_heap[j];
			min_heap[j] = temp;
			i = j;
		}
	}
}

// heapify from top, after deletion
void Heap::max_reheap_down()
{
	int i = 1;
	Node *temp;
	while (2*i <= maxRoot->score - 1)
	{
		int j = 2*i;
		if (j < maxRoot->score-1 && max_heap[j+1]->score > max_heap[j]->score)
		{
			j++;
		}
		if (max_heap[i]->score >= max_heap[j]->score)
		{
			break;
		}
		else
		{
			temp = max_heap[i];
			max_heap[i] = max_heap[j];
			max_heap[j] = temp;
			i = j;
		}
	}
}

// sorts both heaps using heapify(reheapbottom)
void Heap::heap_sort()
{
	cout<<"Heap Sorting: "<<endl;
	cout<<"Ascending order of items using min-heap: "<<endl;
	Node *n;
	while(minRoot->score > 1)
	{
		n = min_heap[1];
		cout<<n->score<<" ";
		min_heap[1] = min_heap[minRoot->score - 1];
		min_heap[minRoot->score - 1] = n;
		minRoot->score--;
		min_reheap_down();
	}
	cout<<endl;
	cout<<"Descending order of items using max-heap: "<<endl;
	while(maxRoot->score > 1)
	{
		n = max_heap[1];
		cout<<n->score<<" ";
		max_heap[1] = max_heap[maxRoot->score - 1];
		max_heap[maxRoot->score - 1] = n;
		maxRoot->score--;
		max_reheap_down();
	}
	cout<<endl;
}

int main()
{
	Heap h;
	int choice = 10;
	while(choice != 0)
	{
		cout<<"Enter your choice:\n1. Enter Record\n2. Enter to Insert a new record.\n3. Enter to Find out max and min marks\n4. Enter to Display marks as Heap\n5. Enter to Sort using Heapsort\n6. Exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				h.create();
				break;
			case 2:
				h.insert();
				break;
			case 3:
				h.getTop();
				break;
			case 4:
				h.display();
				break;
			case 5:
				h.heap_sort();
				break;
			case 6:
				cout<<"EXIT!!"<<endl;
				choice = 0;
				break;
			default:
				cout<<"Wrong choice!!"<<endl;
				break;
		}
	}
	return 0;
}


/**	OUTPUT

Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
1

Enter the marks of each student:
Student: 1 > Enter marks:
20
Do you want to add more? 	y
Student: 2 > Enter marks:
33
Do you want to add more? 	y
Student: 3 > Enter marks:
60
Do you want to add more? 	y
Student: 4 > Enter marks:
45
Do you want to add more? 	y
Student: 5 > Enter marks:
55
Do you want to add more? 	n
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
4
The Current Min-Heap is:	20 33 60 45 55
The Current Max-Heap is:	60 55 33 20 45
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
2
Enter marks:
5
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
3
The minimum marks is : 5
The maximum marks is : 60
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
4
The Current Min-Heap is:	5 33 20 45 55 60
The Current Max-Heap is:	60 55 33 20 45 5
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit
5
Heap Sorting:
Ascending order of items using min-heap:
5 20 33 45 55 60
Descending order of items using max-heap:
60 55 45 33 20 5
Enter your choice:
1. Enter Record
2. Enter to Insert a new record.
3. Enter to Find out max and min marks
4. Enter to Display marks as Heap
5. Enter to Sort using Heapsort
6. Exit

*/
