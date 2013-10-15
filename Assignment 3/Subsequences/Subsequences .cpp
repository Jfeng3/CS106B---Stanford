/*
 * File: Subsequences.cpp
 * ----------------------
 * This is the solution for the subsequences problem. 
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);


int main() {
    while(true) {
    string result;
    cout << "Enter a string: ";
    string text = getLine();
    cout << "Enter a string: ";
    string subsequence = getLine();
    bool p = isSubsequence(text, subsequence);
    if (p) result = "yes";
    else result = "no";
        cout << result << endl;
    
    return 0;
    }
}
        
// Recursive function

bool isSubsequence(string text, string subsequence){
    
    // base case
    
    if (subsequence.length() == 0) return true;   
    int m = 0;
    
    // recursive case
        
    if ( (m = text.find(subsequence[0])) == string:: npos){
        return false;
    } else
       return isSubsequence(text.substr(m), subsequence.substr(1));
    
}