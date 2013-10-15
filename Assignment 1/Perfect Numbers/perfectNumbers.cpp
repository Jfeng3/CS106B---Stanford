/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "lexicon.h"
#include "simpio.h"

using namespace std;

Vector <int> divisors;

bool isPerfect(int n);

int main() {
    
        for (int i = 1; i < 10000; i++){
        bool p = isPerfect(i);
        if(p){
            cout << i << endl;
        }
    
    }return 0;
}

bool isPerfect(int n){
//    divisors.clear();
    int sum = 0;
    for (int i = 1; i < n; i++){
        if (n%i== 0){
            divisors.add(i);
        }
    }
    for (int i = 0; i < divisors.size(); i++){
        sum += divisors.get(i);
}
    if (sum == n){
        return true;
    } else {
        return false;
    }
}
