/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"


using namespace std;

bool Solvable (int value, Vector<int> &squares);
bool IsPuzzleSolvable (int index, int value,  Vector<int> &squares);


int main() {
    
    
    cout<< "Enter a start value: ";
    int index = getInteger();
    Vector<int> squares;
    bool solvable = Solvable(index, squares);
    if (solvable)
        cout<<"Puzzle is solvab;le";
    return 0;
}

bool Solvable ( int index , Vector<int> &squares ) {
    int value = squares.get(index);
    return IsPuzzleSolvable(index, value, squares);
}

bool IsPuzzleSolvable (int index, int value, Vector<int> &squares) {
    
    int newValue;
    
    
    if (index == squares.size() - 1)   // Base case
        return true;
    
    if (index > squares.size() || index < 0)  // Base case
        return false;
    
    // recursive case
    for (int i = 0; i < 2; i++){
        if (i == 0){
             newValue = squares.get(index + value);
            if (IsPuzzleSolvable( index + value, newValue,  squares)) return true;
        }
        else{
            newValue = squares.get(index - value);
            if (IsPuzzleSolvable( index - value, newValue,  squares)) return true;
             
        }
        
        
    }
    return false;
    
}

    
    
