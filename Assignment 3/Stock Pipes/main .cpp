/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
//#include "console.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

int cutStock(Vector <int> & requests, int stocklength);
//int calculatePipesNeeded(Vector <int> & requests,Vector <int> & results,
//                         int stocklength, int count);

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

bool TryStockLength(Vector<int>& values, int numStock, int currentIndex, Vector<int>& stockSizes, int stockLength) {
    
    if (currentIndex == values.size())
        return true;
    
    int currentValue = values.get(currentIndex);
    
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

    
 
    
    
    
    
