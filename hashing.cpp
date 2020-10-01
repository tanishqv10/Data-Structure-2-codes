//============================================================================
// Name        : hashing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <string.h>
using namespace std;

#define MAX 10

int hashFunction(int, int);

int hashFunction(int key, int limit)
{
	return key % limit;
}

class Student
{
	int roll_no;
	char grade;
	string name;
	int chain;
	public:
		Student();
		friend class HashTable;
};

// initialize to defaults
Student::Student()
{
	roll_no = -1;
	grade = 'F';		// start by failing
	name = "";
	chain = -1;
}

class HashTable
{
	int size;
	int total;
	bool chaining;		// if chaining is enabled
	Student **all = NULL;
	public:
		HashTable(int, int);
		void create(int);
		void linearProbeNRep(Student*);
		void linearProbeRep(Student*);
		void linearChainingNRep(Student*);
		void search(int);
		void searchLinearProbe(int);
		void searchChain(int);
		void dispStud(Student*);
		void display();
};

// asks user for total no. of records
HashTable::HashTable(int s, int t)
{
	size = s;				// table size
	total = t;				// number of students
	all = new Student*[s];
	for (int i=0; i<s; i++)
	{
		all[i] = NULL;
	}
}

// creates an instance of student and passes to probe function
void HashTable::create(int choice)
{
	if(choice == 2)
	{
		chaining = true;
	}
	else
	{
		chaining = false;
	}
	for(int i=0; i<total; i++)
	{
		cout<<"\nStudent #"<<i+1<<endl;
		Student *s = new Student();			//allocating space here
		cout<<"Enter your Roll no:\t";
		cin>>s->roll_no;
		cin.ignore();					// to remove newline from feed
		cout<<"Enter your Grade:\t";
		cin>>s->grade;
		s->grade = toupper(s->grade);		// grades are mostly in upper character
		cin.ignore();
		cout<<"Enter your Name:\t";
		getline(cin, s->name);
		if(choice == 0)
		{
			linearProbeNRep(s);
		}
		else if(choice == 1)
		{
			linearProbeRep(s);
		}
		else
		{
			linearChainingNRep(s);
		}
	}
}

// linear probing, with non replacement of conflicting hash value
void HashTable::linearProbeNRep(Student *s)
{
	int pos = hashFunction(s->roll_no, size);
	int i;
	if(all[pos] == NULL)
	{
		all[pos] = s;			// we set to null for this
	}
	else
	{
		i = hashFunction(pos+1, size);
		while (i != pos)
		{
			if (all[i] == NULL)
			{
				all[i] = s;
				break;
			}
			i = hashFunction(i+1, size);
		}
		if (i == pos)
		{		//if there is not an empty slot
			cout<<"\nThe Hash Table is Full"<<endl; 	// if total > size
		}
	}
}

// linear probing, with replacement of conflicting hash values
void HashTable::linearProbeRep(Student *s)
{
	int pos = hashFunction(s->roll_no, size);
	int i;
	if (all[pos] == NULL)
	{
		cout<<"Entered null"<<pos<<endl;
		all[pos] = s;			// if we found an empty slot
	}
	else
	{
		Student *temp = s;
		if(pos != (all[pos]->roll_no) % size)
		{		// if the value is in table and is not matching with its own hash value
			temp = all[pos];		// we will backup present value
			all[pos] = s;
		}
		i = hashFunction(pos+1, size);
		while(i != pos)
		{
			if (all[i] == NULL)
			{
				cout<<"We place non-null here"<<i<<endl;
				all[i] = temp;		//this place in an empty spot
				break;
			}
			i = hashFunction(i+1, size);
		}
		if(i == pos)
		{
			cout<<"Hash Table is Full"<<endl;
		}
	}
}

//linear probing in addition to chaining
void HashTable::linearChainingNRep(Student *s)
{
	int pos = hashFunction(s->roll_no, size);
	int i;
	if(all[pos] == NULL)
	{
		all[pos] = s;
	}
	else
	{
		i = hashFunction(pos+1, size);
		while (i != pos)
		{
			if(all[i] == NULL)
			{
				all[pos]->chain = i;			// previous one links to this
				all[i] = s;
				break;
			}
			i = hashFunction(i+1, size);
		}
		if(i==pos)
		{		//if there is an empty slot
			cout<<"Hash Table is Full"<<endl; 	// if total > size
		}
	}
}

// decides which search to use
void HashTable::search(int key)
{
	if (chaining == true)
	{
		searchLinearProbe(key);
	}
	else
	{
		searchChain(key);
	}
}

// search for an element by its key
void HashTable::searchLinearProbe(int key)
{
	int loc = hashFunction(key, size);
	int i;
	if (all[loc] != NULL && all[loc]->roll_no== key)
	{
		dispStud(all[loc]);
	}
	else
	{
		i = hashFunction(loc+1, size);
		while(i!= loc)
		{
			if (all[i] != NULL && all[i]->roll_no== key)
			{
				dispStud(all[i]);
				break;
			}
			i = hashFunction(i+1, size);
		}
		if(i==loc)
		{
			cout<<"The student is not in our records"<<endl;
		}
	}
}

//For searches via chain index
void HashTable::searchChain(int key)
{
	int loc = hashFunction(key, size);
	if (all[loc] != NULL && all[loc]->roll_no== key)
	{
		dispStud(all[loc]);
	}
	else
	{
		Student *temp = all[loc];
		while (temp != NULL)
		{
			if (temp->chain == -1)
			{
				temp = NULL;
			}
			else
			{
				temp = all[temp->chain];		//keep moving to next chain if there is one
				if (temp->roll_no== key)
				{
					dispStud(temp);
				}
			}
		}
		if (temp == NULL)
		{
			cout<<"The student is not in our records"<<endl;
		}
	}
}

//For display of individual student records
void HashTable::dispStud(Student *s)
{
	cout<<"\t"<<s->roll_no<<"\t"<<s->grade<<"\t"<<s->name;
	if(chaining == true)
	{
		cout<<s->chain;
	}
	cout<<endl;
}

//For display of all student records
void HashTable::display()
{
	cout<<"\nINDICES"<<"\tROLL_NO"<<"\tGRADE"<<"\tNAME"<<endl;
	if (chaining == true)
	{
		cout<<"\tCHAIN"<<endl;
	}
	for(int i=0;i<size;i++)
	{
		cout<<i;
		if (all[i] != NULL)
		{
			dispStud(all[i]);
		}
		else
		{
			cout<<endl;
		}
	}
}


int main() {
	int tot;
	cout<<"Enter the no. of students for record: "<<endl;
	cin>>tot;
	HashTable hash(MAX, tot);	//MAX -> table limit
	int ch,choice=10;
	cout<<"\nEnter the method to use:\n1. Enter for Linear Probing without Replacement\n2. Enter for Linear Probing with Replacement\n3. Enter for Chaining without Replacement"<<endl;
	cin>>ch;
	ch=(ch-1) % 3; 		// better than asking again
	while(choice!=0)
	{
		cout<<"\nEnter your choice:\n1. Enter to Create Hash Table\n2. Enter to Search for a record\n3. Enter to Display the table\n4. Exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				hash.create(ch);
				break;
			case 2:
				int sr;
				cout<<"Enter the roll no. you want to search"<<endl;
				cin>>sr;
				hash.search(sr);
				break;
			case 3:
				hash.display();
				break;
			case 4:
				cout<<"EXIT"<<endl;
				choice = 0;
				break;
			default:
				cout<<"Wrong choice !!"<<endl;
				break;
		}
	}
	return 0;
}


/**	OUTPUT
Enter the no. of students for record:
5

Enter the method to use:
1. Enter for Linear Probing without Replacement
2. Enter for Linear Probing with Replacement
3. Enter for Chaining without Replacement
1

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
1

Student #1
Enter your Roll no:	10
Enter your Grade:	a
Enter your Name:	ambika

Student #2
Enter your Roll no:	12
Enter your Grade:	b
Enter your Name:	ananya

Student #3
Enter your Roll no:	22
Enter your Grade:	a
Enter your Name:	mehal

Student #4
Enter your Roll no:	20
Enter your Grade:	a
Enter your Name:	gurleen

Student #5
Enter your Roll no:	2
Enter your Grade:	b
Enter your Name:	gargi

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
2
Enter the roll no. you want to search
10
	10	A	ambika

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
3

INDICES	ROLL_NO	GRADE	NAME
0	10	A	ambika
1	20	A	gurleen
2	12	B	ananya
3	22	A	mehal
4	2	B	gargi
5
6
7
8
9

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
4
EXIT

Enter the no. of students for record:
5

Enter the method to use:
1. Enter for Linear Probing without Replacement
2. Enter for Linear Probing with Replacement
3. Enter for Chaining without Replacement
2

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
1

Student #1
Enter your Roll no:	10
Enter your Grade:	a
Enter your Name:	ambika
Entered null0

Student #2
Enter your Roll no:	12
Enter your Grade:	b
Enter your Name:	ananya
Entered null2

Student #3
Enter your Roll no:	22
Enter your Grade:	a
Enter your Name:	mehal
We place non-null here3

Student #4
Enter your Roll no:	20
Enter your Grade:	a
Enter your Name:	gurleen
We place non-null here1

Student #5
Enter your Roll no:	2
Enter your Grade:	b
Enter your Name:	gargi
We place non-null here4

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
2
Enter the roll no. you want to search
10
	10	A	ambika

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
3

INDICES	ROLL_NO	GRADE	NAME
0	10	A	ambika
1	20	A	gurleen
2	12	B	ananya
3	22	A	mehal
4	2	B	gargi
5
6
7
8
9

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit

Enter the no. of students for record:
5

Enter the method to use:
1. Enter for Linear Probing without Replacement
2. Enter for Linear Probing with Replacement
3. Enter for Chaining without Replacement
3

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
1

Student #1
Enter your Roll no:	10
Enter your Grade:	a
Enter your Name:	ambika

Student #2
Enter your Roll no:	12
Enter your Grade:	b
Enter your Name:	ananya

Student #3
Enter your Roll no:	22
Enter your Grade:	a
Enter your Name:	mehal

Student #4
Enter your Roll no:	20
Enter your Grade:	a
Enter your Name:	gurleen

Student #5
Enter your Roll no:	2
Enter your Grade:	b
Enter your Name:	gargi

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
2
Enter the roll no. you want to search
10
	10	A	ambika1

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit
3

INDICES	ROLL_NO	GRADE	NAME
	CHAIN
0	10	A	ambika1
1	20	A	gurleen-1
2	12	B	ananya4
3	22	A	mehal-1
4	2	B	gargi-1
5
6
7
8
9

Enter your choice:
1. Enter to Create Hash Table
2. Enter to Search for a record
3. Enter to Display the table
4. Exit

*/
