/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 This program refers to problem 5 of Assignment 1
 */

#include <iostream>
#include "console.h"
#include <string>
#include <fstream>
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include "set.h"
#include "tokenscanner.h"



using namespace std;


Vector <int> histogram;
// functions used  in this program

//Vector <int> createHistogram(ifsstream &in);
void createHistogram(ifstream &inputFile,Vector<int>& localHist);
void printHistogram(const Vector<int>& localHist);
string numberToPrint(int num);

int main()

{
    

    Vector <int> hist;
    ifstream inputFile;
    cout<< "Enter file name: ";
    string s = getLine();
    inputFile.open(s.c_str());
    if (inputFile.fail())
        cout<<"file didnt open";

    createHistogram(inputFile, hist);
    printHistogram(hist);
    return 0;
}



//Vector<int> createHistogram(ifsstream &in)

void createHistogram(ifstream &inputFile, Vector<int>& localHist) {
    for (int i = 0; i < 10; i++){
        histogram.add(0);
    }
    while(true){
        int num;
        inputFile >> num;
        if (inputFile.fail()) break;
        if (num > 0 || num <= 9){
            
           histogram.set(0, num);
        }if (num > 10 || num <= 19){
            
            histogram.set(1, num);
        }if (num > 20 || num <= 29){
            
            histogram.set(2, num);
        }if (num > 30 || num <= 39){
            
            histogram.set(3, num);
        }if (num > 40 || num <= 49){
            
            histogram.set(4, num);
        }if (num > 50 || num <= 59){
            
            histogram.set(5, num);
        }if (num > 60 || num <= 69){
            
            histogram.set(6, num);
        }if (num > 70 || num <= 79){
            
           histogram.set(7, num);
        }if (num > 80 || num <= 89){
            
            histogram.set(8, num);
        }if (num > 90 || num <= 99){
            
            histogram.set(9, num);
        }
        
    }// return histogram;
    
}

// This function prints the histogram

void  printHistogram(const Vector<int>& localHist){
    for  (int i = 1; i < 11; i++){
     int value = histogram[i];
     string label = "";
        switch(i){
            case 1: label = "0 - 9"; break;
            case 2: label = "10 - 19"; break;
            case 3: label = "20 - 29"; break;
            case 4: label = "30 - 39"; break;
            case 5: label = "40 - 49"; break;
            case 6: label = "50 - 59"; break;
            case 7: label = "60 - 69"; break;
            case 8: label = "70 - 79"; break;
            case 9: label = "80 - 89"; break;
            case 10: label = "90 - 99"; break;
        }

        string useful = numberToPrint(value);
        cout<< label << useful << endl;
    
    
    
    }
}
string numberToPrint(int num){
    string stars = "";
    for (int i = 0; i < num; i++){
        stars += "X";
    }return stars;
 
}


    
