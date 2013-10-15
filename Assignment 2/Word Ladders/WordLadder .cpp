/*
 * This is the solution for the word ladder problem.
 
   Word ladder allows us to get from starting word to the ending word by 
    just changing one letter each time. 
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include "set.h"


using namespace std;


string findPath(string firstWord, string lastWord);
Vector <string> findNextWord (string word, Set<string>& fullWordList);
string printVector(Vector <string>& lastList, string lastWord);

int main() {
    
     
    while (true){
        cout << "hello";
            cout << "Enter the starting word: " ;
    string startingWord = getLine();
    cout << "Enter the ending word: ";
    string endingWord = getLine();
    string result = findPath(startingWord, endingWord);
        cout << result << endl;
    
    }
    
    return 0;
}

string findPath(string firstWord, string lastWord){
 
    //I use fullWordList to keep track of all the words that have been used
    Set <string> fullWordList;
    
    string finalAnswer;
    Queue<Vector <string> > database;
    
    if (firstWord == lastWord) return lastWord;
    if (firstWord.length() != lastWord.length()) return "ladder not found";
    
    Vector <string> wordsDifferentByOneLetter = findNextWord(firstWord, fullWordList);
    
/* I am going to find words that are different from the first word by one letter and put all of them in the Queue of vectors.
    
*/    
    for (int i = 0; i <wordsDifferentByOneLetter.size(); i++){
        Vector<string> ladder;
        ladder.add(firstWord);
        ladder.add(wordsDifferentByOneLetter[i]);
        database.enqueue (ladder);
    }

/*  
    -  After the intial vector of queues have been created, I dequeue each vector, find the last word in the vector and check to see if the last word is the deired word. 
    - If not the desired word, I find all words different by one letter, create a new vector for each of the words, check to see if the word is the desired word and if not add it to the queue
    
 */

    while (!database.isEmpty()){
        
        Vector <string> list = database.dequeue();
        string value = list.get(list.size() - 1);
        if (value == lastWord)
           return printVector(list,lastWord );
            
    
           Vector <string> differentWords  = findNextWord(value, fullWordList);
        
        
        foreach(string word  in differentWords) {
            
            Vector <string> newLadder = list;
            newLadder. add(word);
            if (word == lastWord){
                finalAnswer = printVector(newLadder,lastWord );
                return finalAnswer;
            
            }
    
            database. enqueue (newLadder);
            
        }
        
    } return "ladder not found";
}
        

//  This function returns a vector of strings that are different from the passed in word by one letter
 
Vector <string> findNextWord(string word, Set<string>& fullWordList){
    
    Lexicon listOFWords("EnglishWords.dat");
    string result ;
    string good = word;
    Vector <string> allTheDifferentWords;

    
    for(int i = 0; i < word.length(); i++){
        
        for( char j = 'a'; j < 'z'; j++){
            
            result+= j;
            word.replace(i, 1, result);
            result.clear();
            
                        
            if (listOFWords.contains(word) && word!= good && !fullWordList.contains(word)){
                
        
                fullWordList.insert(word);
                allTheDifferentWords.add(word);
                
                
                
            }word = good;
            
        }
    } return allTheDifferentWords;
}

            
        
 // This function prints out the ladder after it has been found
    string printVector(Vector <string>& lastList, string lastWord){
        string result = "";
        string print = "Ladder found:  ";
        string arrow = " => ";
        
        for (int i = 0; i < lastList.size(); i++){
            if (i == 0){
            string firstWord = lastList.get(0) ;
            result = result + print + firstWord;
            }
            else if (i != 0){
                result = result + arrow + lastList.get(i);
                
            }
        } return result;
    }


bool wordContained (string word, Vector <string> words ){
    
    for (int i = 0; i < words.size(); i++){
        if (words.get(i) == word)
            return true;
        
    } return false;
    
}
    
 

