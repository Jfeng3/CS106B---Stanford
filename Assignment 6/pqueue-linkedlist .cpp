/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"



LinkedListPriorityQueue::LinkedListPriorityQueue() {
	 list = NULL;
    number = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    Deallocate (list);
}

int LinkedListPriorityQueue::size() {
	return number;
}

bool LinkedListPriorityQueue::isEmpty() {
	if(list == NULL)
	return true;
    else
        return false;
}

void LinkedListPriorityQueue::enqueue(string value) {
	newOne = new Entry;
    newOne -> name = value;
    newOne -> next = NULL;
    number++;
    
// Use a recursive function to insert an element in order
    InsertSorted(list, newOne);
}

// returns the first element

string LinkedListPriorityQueue::peek() {
    
    if (isEmpty())
        error ("Queue is empty");
    
         return list -> name;
    

}
// First step is to find the minimum and then splice it out

string LinkedListPriorityQueue::dequeueMin() {
    
    if (isEmpty())
        error ("Queue is empty");
    
	Entry * old;
    string value = list -> name;
    old = list;
    list = list -> next;
    delete old;
    number --;
	
	return value;
}

// This function compares two strings

int LinkedListPriorityQueue:: compareStrings( string one, string two){
    int size = min(one.size(), two.size());
    for (int i = 0; i < size; i++){
        if (two[i] < one [i]) return -1;
        if (two[i] > one [i]) return 1;
    }
    return 1;
}

// Recursive function to insert incoming element in order

void LinkedListPriorityQueue::InsertSorted(Entry * &list,  Entry *newOne){
    
    //Base case
    
    if(list==NULL || (compareStrings(list -> name, newOne -> name) < 0)){
        
        newOne -> next = list;
        list = newOne;
        
    } else
        InsertSorted(list -> next, newOne);      // Recursive Case
    
}

// Recursive funtion to deallocate all the memory used

void LinkedListPriorityQueue:: Deallocate (Entry * & list){
    
    if (list != NULL){
        Deallocate (list -> next);
        delete list;
    }
}




