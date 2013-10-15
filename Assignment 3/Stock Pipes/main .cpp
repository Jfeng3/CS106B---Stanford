/*
 * File: main.cpp
 * --------------
 * This is the solution for Assignment 3 problem 6. 
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

// funstions used in the program

int cutStock(Vector <int> & requests, int stocklength);


bool TryStockLength(Vector<int>& values, int numStock, int currentIndex, Vector<int>& stockSizes, int stockLength);



int main() {
    cout << "Enter a number:";
    int stocklength = getInteger();
    Vector <int> values;
    
    
    int numStock = 0;
    bool finished = false;
    while(!finished)
    {
        numStock++;
        Vector<int> stockSizes(numStock, 0);
        for (int i=0;i<numStock;i++)
            stockSizes.set(i, 0);
        finished = TryStockLength(values,numStock,0,stockSizes,stocklength);
        
    }
    
    cout << numStock;
    return 0;
}


// Recursive function

bool TryStockLength(Vector<int>& values, int numStock, int currentIndex, Vector<int>& stockSizes, int stockLength) {
    
    int currentValue = values.get(currentIndex);
    
    // base case
    
    if (currentIndex == values.size())
        return true;
    
    // recursive case

    for(int i=0;i<numStock;i++)
    {
        int currentStockSize = stockSizes.get(i);
        if (currentStockSize + currentValue <= stockLength)
        {
            stockSizes.set(i,currentStockSize + currentValue);
            bool feasable = TryStockLength(values,numStock,currentIndex+1,stockSizes,stockLength);
            if (feasable)
                return true;
            stockSizes.set(i,currentStockSize);
        }
    }
    return false;
    
    
}

    
 
    
    
    
    
