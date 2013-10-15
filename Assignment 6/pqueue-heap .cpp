/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	arr = new string[20];
    numAllocated = 20;
    numUsed = 0;
    
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {
	return numUsed;
}

bool HeapPriorityQueue::isEmpty() {
	if (numUsed == 0)
        return true;
    
    return false;
	
	
}

void HeapPriorityQueue::enqueue(string value) {

	if (numUsed == numAllocated)
        doubleCapacity();
    if (size() == 0)
        arr[numUsed++] = value;
    else {
        arr[numUsed] = value;
       
        FindMin (numUsed);    //Recursive function
        numUsed++;
        
        
    }
}

// Just need to look at the first element of the array

string HeapPriorityQueue::peek() {
    if (isEmpty())
        error ("Queue is empty");
    
	string nameValue = arr[0];
	
	return nameValue;
}

// 2 steps
// 1 - Swap the first and last element (and remove the last element)
// 2 - Use a recurive function to accurately place the first element in order

string HeapPriorityQueue::dequeueMin() {
    string value = "";
	if (isEmpty())
        error ("Queue is empty");
    
     value = arr[0];
    
    Swap(0, numUsed - 1);
    arr[numUsed - 1] = "";
    numUsed--;
    
  
    Readjust(0);    // Recursive function
	
	return value;
}

// This function compares two strings

int HeapPriorityQueue:: compareStrings(string one, string two){
    int size = min(one.size(), two.size());
    if (one.size() == 0 && two.size() != 0)
        return -1;
    if (two.size() == 0 && one.size() != 0)
        return 1;
        
    
    for (int i = 0; i < size; i++){
        if (two[i] < one [i]) return -1;
        if (two[i] > one [i]) return 1;
    }
    return 1;
}

void HeapPriorityQueue:: Swap(int one , int  two){
    string  temp =  arr[one];
    arr[one] = arr [two];
    arr[two] = temp;
    
}

void HeapPriorityQueue:: doubleCapacity(){
    string * bigger = new string[numAllocated*2];
    for (int i = 0; i < numUsed; i++)
        bigger[i] = arr[i];
    
    delete[] arr;
    arr = bigger;
    numAllocated*=2;
    
}

// Recursive function to find the smallest element

void HeapPriorityQueue::FindMin( int number){

    string parent = "";
    string value = arr[number];
    
    //Base Case
    if (number == 0)
        return;
    
    //Recursive case
    
    if (number % 2 == 0 ) {
        parent = arr[(number/2) - 1];
        if (compareStrings(parent, value)< 0)
            Swap( (number/2) - 1 , number);
        number =  (number/2) - 1;
    }
    else if ( number % 2 != 0){
        parent = arr[number / 2];
        if (compareStrings(parent, value)< 0)
            Swap( number/2, number);
        number = number/2;
    }
    

    FindMin(number);
    
}

// Recursive function to readjust after swapping the first and last elements

void HeapPriorityQueue::Readjust (int number){
    
    int child2 = (2*number) + 2;
    int child1 = (2*number) + 1;
    // 2 base cases
    //1 - If the parent node is a leaf node
    //2 - If parent string is less than both children strings
   
    
    if ((child2 > numUsed && child1 > numUsed) ||
        
        (compareStrings(arr[child1], arr[number]) < 0
                                                   
         && compareStrings(arr[child2], arr[number]) < 0)){
            
            return;
        }
    
    // Recursive cases
    
    if (compareStrings(arr[child1], arr[child2]) < 0 ){
      
        // if child2 is less than child1
        
        if(compareStrings(arr[number], arr[child2]) < 0 && child2 < numUsed ){
            
            Swap(number, child2);
            Readjust(child2);
        }
    }
    else {
        
        // if child1 is less than child2
        
        if (compareStrings(arr[number], arr[child1]) < 0 && child1 < numUsed){
            
            Swap (number, child1);
            Readjust (child1);
        }
        
    }
    
            
    
    
}


