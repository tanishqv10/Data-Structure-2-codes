//============================================================================
// Name        : sequence.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
using namespace std;

bool verify_sequence_of_bst(int sequence[], int length)
{
    if(sequence == NULL || length <= 0)
    {
        return false;
    }
    int root = sequence[length - 1];
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(sequence[i] > root)
            break;
    }
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(sequence[j] < root)
            return false;
    }
    bool left = true;
    if(i > 0)
    {
        left = verify_sequence_of_bst(sequence, i);
    }
    bool right = true;
    if(i < length - 1)
        right = verify_sequence_of_bst(sequence + i, length - i - 1);

    return (left && right);
}

int main()
{
    int arr[100];
    char ch;
    int i=0;
    do{
        cout<<"Enter the element "<<(i+1)<<" of array :"<<endl;
        cin>>arr[i];
        i++;
        cout<<"You want to enter more ?(Y/y)"<<endl;
        cin>>ch;
    }while(ch=='Y' || ch=='y');
    verify_sequence_of_bst(arr, (i+1))? cout<<"True" : cout<<"False";
    return 0;
}

/* OUTPUT
 * Enter the element 1 of array :
1
You want to enter more ?(Y/y)
y
Enter the element 2 of array :
3
You want to enter more ?(Y/y)
y
Enter the element 3 of array :
5
You want to enter more ?(Y/y)
n
True
 */
