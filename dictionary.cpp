//============================================================================
// Name        : dictionary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <cstring>
using namespace std;

class node {
	string data, meaning;
	node *left;
	node *right;
	node *parent;
	friend class tree;
	friend class queue;
};

class queue {
    int rear, front;
    node *data2[100];			// we are assuming 100 to be max length of tree
    public:
        queue();
        int isEmpty();
        int isFull();
        void enqueue(node*);
        node* dequeue();
};

// inits queue
queue :: queue() {
    front = -1;
    rear = -1;
}

// returns 1 if queue is empty
int queue :: isEmpty() {
    if(front == rear)
        return 1;
    else
        return 0;
}

// returns 1 if queue is full
int queue :: isFull() {
    if(rear == 99)
        return 1;
    else
        return 0;
}

// pushes a node to end of queue
void queue :: enqueue(node *a) {
    if(isFull() != 1) {
        rear++;
        data2[rear] = a;
    }
}

// pops a node from front of queue
node* queue :: dequeue() {
    if(isEmpty() != 1) {
        front++;
        node* temp = data2[front];
        return temp;
    }
    return NULL;
}

class tree {
	node *root;
	public:
		tree(int);
		void insert();
		void create();
		void breadthfirst();
		node* search(int);
		node* search_r(string, node *);
		node* search_nr(string);
		void del();
		void mirror(int);
		void mirror_r(node*);
		void mirror_nr();
		void copy(tree*);
		node* copy_r(node*, node*);
		void equals();
		int equality(node*, node*);
};

// initalizing a new tree
tree :: tree(int clone) {			// if clone is set, wont ask for root as it will be copied
	if(clone == 0) {
		root = new node();
		cout<<"Please enter the dataword of the root node ?"<<endl;
		getline(cin, root->data);
		cout<<"Please enter the meaning of this word ?"<<endl;
		getline(cin, root->meaning);
		root->left = root->right = root->parent = NULL;			// we need parent for deletion
	} else {
		root = NULL;		// we dont need to ask for root if cloning since it will be copied
	}
}

// insert a single node to a tree
void tree :: insert() {
	node *curr = new node();
	cin.ignore();
	cout<<"Please enter the dataword of this node ?"<<endl;
	getline(cin, curr->data);		// getline allows us to take strings with spaces
	cout<<"Please enter the meaning of this word ?"<<endl;
	getline(cin, curr->meaning);
	curr->left = curr->right = NULL;
	node *temp = root;		// for traversal
	int flag = 0;
	while(flag == 0) {
		if(curr->data > temp->data) {
			if(temp->right == NULL) {
				curr->parent = temp;
				temp->right = curr;
				flag = 1;
			} else {
				temp = temp-> right;
			}
		} else {						// otherwise we go left
			if(temp->left == NULL) {
				curr->parent = temp;
				temp->left = curr;
				flag = 1;
			} else {
				temp = temp-> left;
			}
		}
	}
}

// this creates a new tree
void tree :: create() {
	char choice = 'y';
	cout<<endl;
	do {
		insert();			// this is simply a loop to call insert since insert does not require user input
		cout<<"\nWould you like to continue ?"<<endl;
		cin>>choice;
	} while (tolower(choice) == 'y');
}

// breadthfirst traversal non recursive
void tree :: breadthfirst() {
    node *temp = root;
    queue q;
    q.enqueue(temp);
    while(q.isEmpty() != 1) {
        temp = q.dequeue();
        cout<<temp->data<<" : "<<temp->meaning<<endl;		// will print key as well as meaning
        if(temp->left != NULL)
            q.enqueue(temp->left);		// if left subtree present, push into queue
        if(temp->right != NULL)
            q.enqueue(temp->right);		// if right subtree present, push into queue
    }
}

// contanier to search for a key in dict
node* tree :: search(int recursive) {		// if recursive is 1, will be recursive
	string temp;
	cin.ignore();
	cout<<"\nEnter the keyword to search for ?"<<endl;
	getline(cin, temp);
	if(recursive == 1)
		return search_r(temp, root);
	else
		return search_nr(temp);
}

// recursive search
node* tree :: search_r(string key, node *temp) {
	node *f = NULL;
	if(temp != NULL) {
		if(key == temp->data) {
			cout<<"Match Found >\t"<<temp->data<<" : "<<temp->meaning<<endl;
			return temp;
		} else if (key < temp->data) {
			f = search_r(key, temp->left);		// if search string is less than root then we go left
		} else {
			f = search_r(key, temp->right);		// else we go right
		}
	}
	return f;		// we return the result if found
}

// non recursive search
node* tree :: search_nr(string key) {
	node *flag = NULL;
	node *temp = root;
	while(flag == NULL) {
		if (key == temp->data) {
			cout<<"Match Found >\t"<<temp->data<<" : "<<temp->meaning<<endl;
			flag = temp;
			break;
		} else if (key > temp->data) {
			if(temp->right == NULL)
				break;
			temp = temp->right;
		} else {
			if(temp->left == NULL)
				break;
			temp = temp->left;
		}
	}
	return flag;		// NULL is returned if not found
}

// deletion of a node
void tree :: del() {
	node *curr, *temp, *parent, *alter;
	curr = search(0);			// we use non recursive search to find the node we want to delete, this is why search returns node
	if(curr == NULL) {
		cout<<"\nCannot delete what does not exist."<<endl;
		if(curr == root) {
			if (curr->right == NULL)
				root = root->left;
			else if (curr->left == NULL)
				root = root->right;
			else if (curr->right != NULL && curr->left != NULL) {
				temp = curr->left;
				root = curr->right;
				alter = curr->right;
				while(alter->left != NULL) {
					alter = alter->left;
				}
				alter->left = temp;
			}
		} else {
			parent = curr->parent;
			if(curr->left == NULL && curr->right == NULL) {
				if(parent->left == curr)
					parent->left = NULL;
				else
					parent->right = NULL;
			} else if (curr->left == NULL) {
				if(parent->left == curr)
					parent->left = curr->right;
				else
					parent->right = curr->right;
			} else if (curr->right == NULL) {
				if(parent->left == curr)
					parent->left = curr->left;
				else
					parent->right = curr->left;
			} else {
				alter = curr->right;
				temp = curr->left;
				while(alter->left != NULL) {
					alter = alter->left;
				}
				alter->left = temp;
				if(parent->left == curr)
					parent->left = curr->right;
				else
					parent->right = curr->right;
			}
		}
		curr->left = curr->right = NULL;
		delete curr;
	}
}

// container for mirroring a tree
void tree :: mirror(int recursive) {
	cout<<"\nThe tree before mirror is :"<<endl;
	breadthfirst();
	if(recursive == 1)
		mirror_r(root);		// if recursive is set to 1
	else
		mirror_nr();
	cout<<"The tree after mirror is :"<<endl;
	breadthfirst();
}

// recursive mirroring
void tree :: mirror_r(node *curr) {
	node *temp;
	if(curr != NULL) {
		mirror_r(curr->left);
		mirror_r(curr->right);

		temp = curr->left;
		curr->left = curr->right;
		curr->right = temp;
	}
}

// non recursive mirroring
void tree :: mirror_nr() {
	node *curr = root;
    queue q;
    q.enqueue(curr);
    while(q.isEmpty() != 1) {
        curr = q.dequeue();
        node *temp = curr->left;
        curr->left = curr-> right;
        curr->right = temp;
        if(curr->left != NULL)
            q.enqueue(curr->left);
        if(curr->right != NULL)
            q.enqueue(curr->right);
    }
}

// recursive copying container
void tree :: copy(tree *dupe) {
    dupe->root = copy_r(root, NULL);
}

// copying a tree
node* tree :: copy_r(node *root, node *parent) {
    if(root == NULL) return NULL;
    node *newnode = new node();
    newnode->data = root->data;
    newnode->meaning = root->meaning;
    newnode->parent = parent;
    newnode->left = copy_r(root->left, newnode);
    newnode->right = copy_r(root->right, newnode);
    return newnode;
}

// checks if two trees are equal, requires user input for 2nd tree
void tree :: equals() {
    cout<<"\nPlease enter a new tree to check equality with base"<<endl;
    cin.ignore();
    tree b2(0);		// by passing in 0 we ensure root input is required
    b2.create();
    int check = equality(root, b2.root);
    if(check == 1)
        cout<<"The tree you entered is equal to base"<<endl;
    else
        cout<<"The tree does not match"<<endl;
}

// compares two trees BFS and returns 1 if same
int tree :: equality(node *a, node *b) {
    node *curr1 = a;
    node *curr2 = b;
    if(curr1 == NULL && curr2 != NULL)
        return 0;
    if(curr2 == NULL && curr1 != NULL)
        return 0;
    queue q1, q2;
    q1.enqueue(curr1);
    q2.enqueue(curr2);
    while(q1.isEmpty() != 1) {
        curr1 = q1.dequeue();
        curr2 = q2.dequeue();
        if(curr1->data != curr2->data || curr1->meaning != curr2->meaning)
            return 0;
        if(curr1->left != NULL) {
            if(curr2->left == NULL)
                return 0;
            q1.enqueue(curr1->left);
            q2.enqueue(curr2->left);
        }
        if(curr1->right != NULL) {
            if(curr2->right == NULL)
                return 0;
            q1.enqueue(curr1->right);
            q2.enqueue(curr2->right);
        }
    }
    return 1;
}

int main() {
	cout<<"This program performs various operations on binary search tree.\n"<<endl;
    int choice = 0;
    tree b1(0);
    tree *b2;
    node *result;
    do {
    	cout<<"\nPlease enter your choice:\n1. Create a tree\n2. Insert a node\n3. Display via BFS\n4. Search Recursively\n5. Search Non-Recursively\n6. Delete a node\n7. Mirror Recursively\n8. Mirror Non-Recursively\n9. Clone the tree\n10. Check if two trees are equal"<<endl;
    	cin>>choice;
    	switch(choice) {
    		case 1:
    			b1.create();
    			break;
    		case 2:
    			b1.insert();
    			break;
    		case 3:
    		    cout<<"\nContents of the dictionary are :"<<endl;
    			b1.breadthfirst();
    			break;
    		case 4:
    			result = b1.search(1);
    			if(result == NULL)
    				cout<<"We could not find such a keyword"<<endl;
    			break;
    		case 5:
    			result = b1.search(0);
    			if(result == NULL)
    				cout<<"We could not find such a keyword"<<endl;
    			break;
    		case 6:
    			b1.del();
    			break;
    		case 7:
    			b1.mirror(1);
    			break;
    		case 8:
    			b1.mirror(0);
    			break;
    		case 9:
    			b2 = new tree(1);			// this means no root initialization
    			b1.copy(b2);
    			cout<<"\nThe cloned tree is :"<<endl;
    			b2->breadthfirst();
    			break;
            case 10:
                b1.equals();
                break;
    		default:
    			cout<<"\nWrong Choice !!! Please try again"<<endl;
    			break;
    	}
    } while (choice != 0);
    return 0;
}


/*	OUTPUT

This program performs various operations on binary search tree.

Please enter the keyword of the root node ?
one
Please enter the meaning of this word ?
1

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
1

Please enter the keyword of this node ?
two
Please enter the meaning of this word ?
2

Would you like to continue ?
y
Please enter the keyword of this node ?
three
Please enter the meaning of this word ?
3

Would you like to continue ?
y
Please enter the keyword of this node ?
four
Please enter the meaning of this word ?
4

Would you like to continue ?
n

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
2
Please enter the keyword of this node ?
zero
Please enter the meaning of this word ?
0

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
3

Contents of the dictionary are :
one : 1
three : 3
two : 2
zero : 0
four : 4

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
4

Enter the keyword to search for ?
zero
Match Found >   zero : 0

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
5

Enter the keyword to search for ?
two
Match Found >   two : 2

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
6

Enter the keyword to search for ?
zero
Match Found >   zero : 0

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
3

Contents of the dictionary are :
one : 1
three : 3
two : 2
four : 4

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
7

The tree before mirror is :
one : 1
three : 3
two : 2
four : 4
The tree after mirror is :
one : 1
two : 2
three : 3
four : 4

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
8

The tree before mirror is :
one : 1
two : 2
three : 3
four : 4
The tree after mirror is :
one : 1
three : 3
two : 2
four : 4

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
9

The cloned tree is :
one : 1
three : 3
two : 2
four : 4

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal
10

Please enter a new tree to check equality with base
Please enter the keyword of the root node ?
two
Please enter the meaning of this word ?
2


Please enter the keyword of this node ?
three
Please enter the meaning of this word ?
3

Would you like to continue ?
n
The tree does not match

Please enter your choice:
1. Create a tree
2. Insert a node
3. Display via BFS
4. Search Recursively
5. Search Non-Recursively
6. Delete a node
7. Mirror Recursively
8. Mirror Non-Recursively
9. Clone the tree
10. Check if two trees are equal


*/

