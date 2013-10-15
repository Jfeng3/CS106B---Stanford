/*
 
 This is the solution for Assignment 1 Problem 4
 
 This program is for the Soundex algorithm. 
 A Soundex algorithm produces code for a surname based on the way it sounds, rather than how it is spelled. 
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "string.h"
#include "strlib.h"

using namespace std;


/* Here are the codes for converting letters
 Number     Letter
 0     -    a, e, i , o, u, h, w, y
 1     -    b, f, p, v
 2     -    c, g, j, k, q, s, x, z
 3     -    d, t
 4     -    m, n
 5     -    l
 6     -    r
 */

// functions present in this program
string convertToNumbers(string name);

int main(){

    

    while (true){
        cout << "Enter Surname: " ;
        string name = getLine();
        if (name == "") break;
        string numbersName = convertToNumbers(name);
        cout<< "Soundex Code for " << name << "is " <<  numbersName << endl;
        
        
    } 
return 0;
}

// This function conevrts a string based on the Soundex algorithm

string convertToNumbers(string name){
    string result = "";
    
    for (int i = 0; i < name.size(); i++){
        
        string s =  integerToString(0);
        result.insert(i, s);

    }
     
    for (int i = 0; i< name.size(); i++){
        if (i == 0){
            toupper(name[i]);
            result[i] = name[i];
        } else if (name[i] == 'a' || name[i] == 'e' || name[i] == 'i' || name[i] == 'o' ||
                name[i] == 'u' || name[i] == 'h' || name[i] == 'w' || name[i] == 'y'){
            string s =  integerToString(0);
            result.replace(i, 1, s);
            
            
        } else if (name[i] == 'b' || name[i] == 'f' || name[i] == 'p' || name[i] == 'v'){
            string s =  integerToString(1);
           result.replace(i, 1, s);

           
            
        } else if (name[i] == 'c' || name[i] == 'g' || name[i] == 'j' || name[i] == 'k'
                   || name[i] == 'q' || name[i] == 's' || name[i] == 'x' || name[i] == 'z'){
            string s =  integerToString(2);
            result.replace(i, 1, s);
            
        } else if (name[i] == 'd' || name[i] == 't'){
            string s =  integerToString(3);
            result.replace(i, 1, s);

            
        } else if ( name[i] == 'm' || name[i] == 'n'){
            string s =  integerToString(4);
            result.replace(i, 1, s);


            
        } else if (name[i] == 'l'){
            string s =  integerToString(5);
            result.replace(i, 1, s);

            
        } else if ( name[i] == 'r'){
            string s =  integerToString(6);
            result.replace(i, 1, s);

            
        }
    }
       // remove any consecutive integers
    for (int k = 1; k < result.size(); k++){
        if (result[k] == result[k + 1]){
            result.erase(k,1);
        }
    }
      
       // remove any zeroes
    for (int j = 1; j < result.size(); j++ ){
        if (result[j] == '0') {
            result.erase(j, 1);
    
        }
    }
       // check if length is 4, if not add zeroes
        
        if (result.size() ==  1){
            string s =  integerToString(0);
            
            result = result + s + s + s;
            
        }else if (result.size() ==  2) {
            string s =  integerToString(0);
            result  = result + s + s;
            
        }else if (result.size() ==  3){
            string s =  integerToString(0);
            result = result + s;
            
        } else if (result.size() >= 4){
            name.erase(5);
        }
    return result;

    
}





