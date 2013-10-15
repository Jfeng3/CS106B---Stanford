/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
//#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);
//bool isSubstring(string text, string subsequence);

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
        


bool isSubsequence(string text, string subsequence){
    if (subsequence.length() == 0) return true;   // base case
    int m = 0;
        
    if ( (m = text.find(subsequence[0])) == string:: npos){
        return false;
    } else
       return isSubsequence(text.substr(m), subsequence.substr(1));
    
}