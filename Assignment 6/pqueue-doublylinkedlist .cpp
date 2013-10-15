/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	list = NULL;
    number = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Deallocate (list);
}

int DoublyLinkedListPriorityQueue::size() {
	return number;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	if(list == NULL)
        return true;
    else
        return false;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	newOne = new Entry;
    newOne -> name = value;
    number++;
    newOne -> next = list;
     newOne -> previous = NULL;
    list = newOne;
    if (size() != 1){
        
        newOne -> next -> previous = list;
        
    }
    
    
}
// need to first find the minimum

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty())
        error ("Queue is empty");
    
    // finding the minimum
    Entry *min, * curr;
    
    min = list;
    for ( curr = list -> next; curr != NULL; curr = curr -> next){
        if (compareStrings(min -> name, curr -> name) < 0){
            min = curr;
        }
    }
    
	
	return min -> name;
}

// First step is to find the minimum and then splice it out

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (isEmpty())
        error ("Queue is empty");
    
    // finding the minimum
    Entry *min, * curr;
    
    min = list;
    for ( curr = list -> next; curr != NULL; curr = curr -> next){
        if (compareStrings(min -> name, curr -> name) < 0){
            min = curr;
        }
    }
    string nameValue = min -> name;
    
    // splicing out the min element and readjusting the pointers
    
     // special case if min is the last element
    if (min -> next == NULL && size() != 1){
        min -> previous -> next = NULL;
        min -> previous = NULL;
        delete min;
        number--;
        
    }
    // special case if min is the first element
    else if (min -> previous == NULL && size() != 1){
        min -> next -> previous = NULL;
        list = list -> next;
        delete min;
        number--;
        
    }
    // special case if size is 1
    else if (size() == 1){
        list = NULL;
        delete min;
        number--;
    }
    // for all other cases
    else {
    min -> next -> previous = min -> previous;
    min -> previous -> next = min -> next;
        min -> next = NULL;
        min -> previous = NULL;
        delete min;
        number--;
    }
    
    
    return nameValue;
}

// This function deallocates all the used memory

void DoublyLinkedListPriorityQueue:: Deallocate (Entry * & list){
    
    if (list != NULL){
        Deallocate (list -> next);
        delete list;
    }
}

// This function compares two strings
int DoublyLinkedListPriorityQueue:: compareStrings(string one, string two){
    int size = min(one.size(), two.size());
    for (int i = 0; i < size; i++){
        if (two[i] < one [i]) return -1;
        if (two[i] > one [i]) return 1;
    }
    return 1;
}


