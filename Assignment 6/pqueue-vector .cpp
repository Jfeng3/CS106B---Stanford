/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"


// Constructor

VectorPriorityQueue::VectorPriorityQueue() {
	arr = new string[20];
    numAllocated = 20;
    numUsed = 0;
}

// Destructor

VectorPriorityQueue::~VectorPriorityQueue() {
	delete[] arr;
}

int VectorPriorityQueue::size() {
	
	return numUsed;
}

bool VectorPriorityQueue::isEmpty() {
	
    if (numUsed == 0)
	  return true;
    else
     return false;
}

void VectorPriorityQueue::enqueue(string value) {
	if (numUsed == numAllocated)
        doubleCapacity();
     
    arr[numUsed++] = value;
}


// Need to find the minimum element in the array
string VectorPriorityQueue::peek() {
    string value;
    if (isEmpty())
        error ("Queue is Empty");
      

    string min = arr[0];

    for (int i = 1; i < numUsed; i++){
        if (compareStrings(min, arr[i]) < 0)
            min = arr[i];
        
    }

    return min;
}

// This function first finds the minimum element and its index and then
//removes it using the RemoveAt function

string VectorPriorityQueue::dequeueMin() {
    if (isEmpty())
        error ("Queue is Empty");
    
    string min = arr[0];
    int number = 0;
    for (int i = 1; i < numUsed; i++){
        if (compareStrings(min, arr[i]) < 0){
            min = arr[i];
           number = i;
    }
    }

	removeAt(number);
	return min;
}

void VectorPriorityQueue:: doubleCapacity(){
    string * bigger = new string[numAllocated*2];
    for (int i = 0; i < numUsed; i++)
        bigger[i] = arr[i];
       
    delete[] arr;
    arr = bigger;
    numAllocated*=2;
    
}

// This function compares two strings

int VectorPriorityQueue:: compareStrings(string one, string two){
    int size = min(one.size(), two.size());
    for (int i = 0; i < size; i++){
        if (two[i] < one [i]) return -1;
        if (two[i] > one [i]) return 1;
    }
    return 1;
}

// This function removes an element at index number from the array

void VectorPriorityQueue:: removeAt(int number){
    
    if (number < 0 || number >= size())
        error ("Out of bounds");
    if (numUsed == numAllocated)
        doubleCapacity();
    
    if (size() > 2 && number!= numUsed) {
    for (int i = number; i <= size() - 2; i++)
        arr[i] = arr[i + 1];
    
        numUsed--;
    }
  //  special case for size  = 1 and number is the same as numUsed
     else if(size () == 1 || number == numUsed){
        numUsed--;
    }
  // special case for size  = 2
     else if (size() == 2 && number!= numUsed){
        for (int i = number; i < size() - 1; i++)
            arr[i] = arr[i + 1];
        
        numUsed--;
    }
    
    
    
    
    
}
   
    
    
    


