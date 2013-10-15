
/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */


 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
using namespace std;



/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */



void welcome();
void giveInstructions();
void getChoices();
Grid <char> shuffleRegularBoard(int number);
Grid <char> shuffleBigBoard(int number);
void playGame();
Grid <char> setUpCustomWordConfigurationsRegularBoard(int number);
Grid <char> setUpCustomWordConfigurationsBigBoard(int number);
char getRandomLetter(string word);
void humansTurn(Grid <char> lettersUsed, int number,  Set <string> &wordsAlreadyEntered);
Set <string>  computersTurn(Grid <char> lettersUsed, int number);
bool wordCanBeFormed(string word,int index, const Grid <char> lettersUsed, int number, Vector <Vector <int> > & numbersUsedInHighlighting, string currentWord);
bool isAdjacent( char previous, int rows, int cols,  Grid <char> lettersUsed, int number);
bool isAdjacentToPreviousRowAndColumn(int rows, int cols, int previousRows, int previousCols,  Grid <char> lettersUsed, int number);
Vector<Vector<int> > findRowAndColumn(char ch, const Grid <char> lettersUsed);
Vector <string> howManyWordsCanBeFormed (string solution, Vector <Vector <int> > nextLetters, Lexicon lex, Grid <char> lettersUsed, Vector <Vector <int> > & alreadyUsedRowsAndColumns, Vector <string> & listOfWords, int number);
 void printAnswers(Set<string> finalAnswer,const Set <string> wordsAlreadyEntered);
bool wordContained (string word, Vector <string> words );


// Computers turn

Vector <Vector <int> > findNextPossibleLetters (int rows, int cols, Lexicon lexicon,  Grid <char> lettersUsed, Vector <Vector <int> >& alreadyUsedRowsAndColumns, int number);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    while(true){
    cout << "Do you need instructions : ";
    string line = getLine();
        cout << endl;
        if (line == "Y" || line == "Yes" || line =="yes" || line == "y"){
        giveInstructions();
        break;
        }
    if (line == "N" || line == "No" || line== "n" || line== "no")
            break;
    if ( line !="N" &&  line != "No" && line !="no" && line != "n" &&
        line !="Y" &&  line != "Yes" && line !="yes" && line != "y")
        cout << "Please enter yes or no"<< endl;
    }
    
    getChoices();
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */



void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* In this function, the user has to make 2 choices
   1 - Whether ot play standard Boggle or big boggle
   2 - Whether to force the board configuration or not
 */
void getChoices(){
    Grid <char> usedLetters;
    int boardSize;
    while(true){
    cout << "You can choose standard Boggle (4 x 4 grid)  or Big Boggle (5 x 5)" << endl;
    cout << "Would you like Big Boggle: ";
    string choice = getLine();
    cout << endl << endl;
        
    if ( choice == "Y" ||  choice == "Yes" || choice =="yes" || choice == "y"){
        drawBoard(5,5);
        boardSize = 5;
        
        
            }     
    else if (choice == "n" ||  choice == "No" || choice =="no" || choice == "n"){
        drawBoard(4,4);
        boardSize = 4;
        
    }
       else if ( choice !="N" &&  choice != "No" && choice !="no" && choice != "n"
                 && choice !="Y" && choice != "Yes" && choice !="yes" && choice != "y"){
            cout << "Please enter yes or no" << endl;
           continue;
        }
        
        cout << "I will give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working." << endl;
    
        while(true) {
    
    
    cout << "Do you want to force the board configuration: ";
    string force = getLine();
    cout << endl << endl;
             if ( force !="N" &&  force != "No" && force !="no" && force != "n" &&
                 force !="Y" &&  force != "Yes" && force !="yes" && force != "y"){
                 cout << "Please enter yes or no" << endl;
                 continue;
             }
    if (force =="N" ||  force == "No" || force =="no" || force== "n"){
        if (boardSize == 4){
            usedLetters = shuffleRegularBoard(4);
            break;
        }
        else {
             usedLetters = shuffleBigBoard(5);
            break;
        }
    }
     else if (force =="Y" ||  force == "Yes" || force =="yes" || force == "y"){
         if (boardSize == 4) {
              usedLetters =  setUpCustomWordConfigurationsRegularBoard(4);
              break;
         }
         else {
                usedLetters = setUpCustomWordConfigurationsBigBoard(5);
                break;
         }
     }          
        }
    cout << "Okay, take all the time you want and find all the words you can. Signal that you are finished by entering an empty line. ";

     Set <string> wordsAlreadyEntered;
    
    humansTurn(usedLetters, boardSize, wordsAlreadyEntered);
    Set <string> finalAnswer = computersTurn(usedLetters, boardSize );
    printAnswers(finalAnswer,wordsAlreadyEntered);
        string lastChoice;
        while(true){
    cout << "Do you want to play the game again ";
    lastChoice = getLine();
            cout << endl;
     
        if ( lastChoice !="N" &&  lastChoice != "No" && lastChoice !="no" && lastChoice != "n" &&
                lastChoice !="Y" &&  lastChoice != "Yes" && lastChoice !="yes" && lastChoice != "y")
            cout << "Please answer yes or no" << endl;
            cout << endl;
        if (lastChoice =="N" ||  lastChoice == "No" || lastChoice =="no" || lastChoice == "n" ||
           lastChoice =="Y" ||  lastChoice == "Yes" || lastChoice =="yes" || lastChoice == "y" )
            break;
         
        }

    }
}


void printAnswers(Set <string>finalAnswer, const Set <string> wordsAlreadyEntered){
    
    foreach(string word in finalAnswer){
        if (!wordsAlreadyEntered.contains(word))
        recordWordForPlayer(word, COMPUTER);
    }
        
        
}
    

// If the player wants to choose the letters on the 16 cubes, this function does that

Grid <char> setUpCustomWordConfigurationsRegularBoard(int boardSize){
    
    string wordUsed;
    

    Grid <char> lettersUsedInGame(boardSize,boardSize);
    
    int product = boardSize*boardSize;
    string word;
    cout << "Enter a 16 character string to identify which letters you want on the cubes." << endl;
    cout<< "The first 4 letters are the cubes on the top row from right to left, the next 4" << endl;
    cout <<"letters are the second row and so on" << endl;
    while(true){
        cout << "Enter the string: ";
        
    word = getLine();
        wordUsed = toUpperCase(word);
    cout << endl << endl;
    if (wordUsed.length() == product)
        break;
    if (wordUsed.length() != product)
        cout << "String must include 16 characters! Try again" << endl;
    }
    
    Vector <char> possibleLetters;
    for (int i = 0; i < wordUsed.length(); i++){
        possibleLetters.add( wordUsed[i]);
    }
    int num = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            labelCube(i, j, wordUsed[num]);
            lettersUsedInGame.set(i,j,wordUsed[num]);
            num++;
            
            
        }
    
    } return lettersUsedInGame;
}
    
// If the player chooses the big board and wants to choose the letters on the cubes, this function does that

Grid <char> setUpCustomWordConfigurationsBigBoard(int boardSize){
    string wordUsed;
            Grid <char> lettersUsedInGame(boardSize,boardSize);
    
    int product = boardSize*boardSize;
        string word;
        cout << "Enter a 25 character string to identify which letters you want on the cubes." << endl;
        cout<< "The first 5 letters are the cubes on the top row from right to left, the next 5" << endl;
        cout <<"letters are the second row and so on" << endl;
        while(true){
            cout << "Enter the string: ";
            
            word = getLine();
             wordUsed = toUpperCase(word);
            cout << endl << endl;
            if (wordUsed.length() == product)
                break;
            if (wordUsed.length() != product)
                cout << "String must include 25 characters! Try again" << endl;
        }
        
        Vector <char> possibleLetters;
        for (int i = 0; i < wordUsed.length(); i++){
            possibleLetters.add( wordUsed[i]);
        }
        int num = 0;
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                labelCube(i, j, wordUsed[num]);
                lettersUsedInGame.set(i,j,wordUsed[num]);
                num++;
                
                
            }
        }

    
    return lettersUsedInGame;
    
}

// This function is used to get a random letter given a string of six letters

char getRandomLetter(string word){
    
    int n = randomInteger(0, word.length() - 1);
    char c = word[n];
    return c;
}


// This function assigns 16 letters to the 16 cubes

Grid<char> shuffleRegularBoard (int boardSize){
    
// I use the grid to store what is displayed in the 16 cubes. I pass the grid as a parameter
// to the human and computer turns
    Grid <char> lettersUsedInGame(boardSize,boardSize);
    
    // code for shuufling the cubes. First step is to create a vector from the const array
    Vector <string> possibleStrings;
    
    int product = boardSize*boardSize;
   

    for (int i = 0; i < product; i++){
        string value = STANDARD_CUBES[i];
        possibleStrings.add(value);
    }

    // code for shuffling the vector by randomly swapping elements of the vector
    for (int i = 0; i < possibleStrings.size(); i++ ){
        int index = randomInteger(0, possibleStrings.size() - 1);

        string temp = possibleStrings.get(i);
        possibleStrings.set(i, possibleStrings.get(index));
        possibleStrings.set(index, temp);
        
    }
    
 // code for placing the string in each cube, I use int num to access elements of the vector
    int num = 0;
  for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
          char ch = getRandomLetter(possibleStrings.get(num));
          labelCube(i, j, ch);
            lettersUsedInGame.set(i,j,ch);
         num++;
        
    }
  } return lettersUsedInGame;
}


// This function assigns 25 letters to the 25 cubes

Grid <char> shuffleBigBoard (int boardSize){
    
    // I use the grid to store what is displayed in the 25 cubes. I pass the grid as a parameter
    // to the human and computer turns
 
    Grid <char> lettersUsedInGame(boardSize,boardSize);
    
    int product = boardSize*boardSize;

    
//  First step is to create a vector from the const array
    Vector <string> possibleStrings;
    for (int i = 0; i < product; i++){
        string value = BIG_BOGGLE_CUBES[i];
        possibleStrings.add(value);
    }
    
    // code for shuffling the vector by randomly swapping elements of the vector
    for (int i = 0; i < possibleStrings.size(); i++ ){
        int index = randomInteger(0, possibleStrings.size() - 1);
        
        string temp = possibleStrings.get(i);
        possibleStrings.set(i, possibleStrings.get(index));
        possibleStrings.set(index, temp);
        
    }
    // code for placing the string in each cube, I use int num to access elements of the vector
    int num = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            char ch = getRandomLetter(possibleStrings.get(num));
            labelCube(i, j, ch);
            lettersUsedInGame.set(i,j,ch);
            num++;
            
        }
    } return lettersUsedInGame;

    
}
    

// This fuction is for the humans turn

void humansTurn(const Grid <char> lettersUsed, int boardSize,  Set <string> & wordsAlreadyEntered) {
    string enteredWord;
    Lexicon wordList("EnglishWords.dat");
   string currentWord = "";
    
    
    
    while (true){
        cout << "Enter a word: ";
    
        string wordToCheck = getLine();
        enteredWord = toUpperCase(wordToCheck);
        Vector <Vector <int> > numbersUsedInHighlighting;
        if (enteredWord == "") break;
        if (enteredWord.length() >= 4 ){
              if (wordList.contains(enteredWord) && !wordsAlreadyEntered.contains(enteredWord) && wordCanBeFormed(enteredWord,0, lettersUsed, boardSize, numbersUsedInHighlighting,currentWord)){
            recordWordForPlayer(enteredWord, HUMAN);
                  for (int i = 0; i < numbersUsedInHighlighting.size(); i++){
                      Vector<int> goods = numbersUsedInHighlighting.get(i);
                      int rows = goods.get(0);
                      int cols = goods.get(1);
                      highlightCube(rows, cols, true);
                  }
                  
                  pause(800);
                  
                  for (int i = 0; i < numbersUsedInHighlighting.size(); i++){
                      Vector<int> goods = numbersUsedInHighlighting.get(i);
                      int rows = goods.get(0);
                      int cols = goods.get(1);
                      highlightCube(rows, cols, false);
                  }
                
                  
            wordsAlreadyEntered.add(enteredWord);
              } else {
                  if (wordsAlreadyEntered.contains(enteredWord)){
                      cout << "You've already guessed that" << endl;
                      
                  } else 
                  cout << "You cant make that word" << endl;
              }
        }
        else {
                cout << "I am sorry, but we have standards." << endl;
                cout << "That word does not meet our minimum requirement." << endl;
            }
        
    }
}

// recursive function
/* for each letter(except the first and last) there are 3 ways I confirm that letter can be present
 1 - I first check the adjacent letter using the isAdjacent Fuction
 2 - I check the next letter using using the isAdjacent Fuction
 3 - I then check if the currentLetters row and column is adjacent to the previous letters 
   row and column using the isAdjacentToPreviousRowAndColumn

 For the first letter, i only check the next letter using the IsAdjacent function
 
 For the last letter, 
 1 - I check the previous letter using the IsAdjacent function and 
 2 - I check if the currentLetters row and column is adjacent to the previous letters
 row and column using the isAdjacentToPreviousRowAndColumn


*/
bool wordCanBeFormed(string word,int index, const Grid <char> lettersUsed, int boardSize,Vector <Vector <int> > & numbersUsedInHighlighting, string currentWord ){
    
    Lexicon lexicon("EnglishWords.dat");

    
    // base case
    if ( index > word.length() - 1)
        
        return lexicon.contains(word);
        
            
// beginning of the recursive case
    
    string result = "";
   

    char c = word[index];
    char nextLetter = word[index + 1];
    char previousLetter = word[index - 1];
    result = result = c;
   
    Vector <Vector <int> > rowsAndColumns = findRowAndColumn(c, lettersUsed);
    
    if (rowsAndColumns.isEmpty()) return false;
    int rows;
    int cols;


    
    for (int i = 0; i < rowsAndColumns.size(); i++ ){
        Vector <int> numbers = rowsAndColumns.get(i);
        rows = numbers.get(0);
        cols =  numbers.get(1);
        

        if (index == word.length() - 1){
            if (isAdjacent(previousLetter, rows, cols, lettersUsed, boardSize)){
                Vector<int> numbers;
                int mine = currentWord.length() - 1;
                numbers = numbersUsedInHighlighting.get(mine);
                int previousRows = numbers.get(0);
                int previousColumns = numbers.get(1);
                if (isAdjacentToPreviousRowAndColumn(rows, cols ,previousRows,previousColumns, lettersUsed, boardSize )){
                   Vector <int> numbersToBeHighlighted;
                   numbersToBeHighlighted.add(rows);
                   numbersToBeHighlighted.add(cols);
                   numbersUsedInHighlighting.add(numbersToBeHighlighted);
                   currentWord += c;
                    if (wordCanBeFormed(word, index + 1, lettersUsed, boardSize, numbersUsedInHighlighting, currentWord)) return true;
                    else {    
                
                        numbersUsedInHighlighting.remove(currentWord.length() - 1);
                        currentWord.erase(currentWord.length() - 1);
                    }
            }
          }
        }
        if (index != 0 && index!= word.length() - 1) {
            if (isAdjacent( previousLetter, rows, cols, lettersUsed, boardSize))
                if (isAdjacent( nextLetter, rows, cols, lettersUsed, boardSize)){
                    Vector<int> numbers;
                    int mine = currentWord.length() - 1;
                    numbers = numbersUsedInHighlighting.get(mine);
                    int previousRows = numbers.get(0);
                    int previousColumns = numbers.get(1);
                    if (isAdjacentToPreviousRowAndColumn(rows, cols ,previousRows,previousColumns, lettersUsed, boardSize )){
                      Vector <int> numbersToBeHighlighted;
                      numbersToBeHighlighted.add(rows);
                      numbersToBeHighlighted.add(cols);
                      numbersUsedInHighlighting.add(numbersToBeHighlighted);
                       currentWord += c;
                        if (wordCanBeFormed(word, index + 1, lettersUsed, boardSize, numbersUsedInHighlighting, currentWord)) return true;
                        else {
                            numbersUsedInHighlighting.remove(currentWord.length() - 1);
                            currentWord.erase(currentWord.length() - 1);
                        }
                    
                 
            }
          }
        }
        if (index == 0){
            
            if (isAdjacent(nextLetter, rows, cols, lettersUsed, boardSize)){
                if (!lexicon.containsPrefix(result)) return false;

                Vector <int> numbersToBeHighlighted;
               numbersToBeHighlighted.add(rows);
                numbersToBeHighlighted.add(cols);
                numbersUsedInHighlighting. add(numbersToBeHighlighted);
                currentWord += c;
                return  wordCanBeFormed(word, index + 1, lettersUsed, boardSize, numbersUsedInHighlighting, currentWord);
            }
        }
    }return false;

    
    }

// This function returns the row and column of the desired letter
    
    Vector<Vector<int> > findRowAndColumn(char ch,  Grid <char>  lettersUsed){
        Vector<Vector<int> >rowsAndColumns;
        int rows;
        int cols;
        for (int i = 0; i < lettersUsed.numRows();i++){
            for (int j = 0; j < lettersUsed.numCols(); j++){
                char chars = lettersUsed.get(i, j);
                
                if (chars == ch){
                    Vector<int> numbers;
                    rows = i;
                    cols = j;
                    numbers.add(i);
                    numbers.add(j);
                    rowsAndColumns.add(numbers);

                }
            }
        }return rowsAndColumns;
    }


// This function checks if the rows and columns of the previous letter is adjacent to row and column
// of the next letter

bool isAdjacentToPreviousRowAndColumn(int rows, int cols, int previousRows, int previousCols, const Grid <char> lettersUsed, int boardSize){
    
    bool upperRightCorner = false;
    bool upperMiddleCorner = false;
    bool upperLeftCorner = false;
    bool leftSide = false;
    bool rightSide= false;
    bool bottomRightCorner= false;
    bool bottomMiddleCorner= false;
    bool bottomLeftCorner= false;
    
    //Upper right Corner
    int rowlengthURC = previousRows  - 1;
    int colslengthURC = previousCols + 1;
    
    if  (rowlengthURC < boardSize && rowlengthURC >= 0 && colslengthURC < boardSize && colslengthURC >= 0){
    
    if (rowlengthURC == rows && colslengthURC == cols)
        upperRightCorner = true;
    }
    
    // upper middle corner
    int rowlengthUMC = previousRows  - 1;
    int colslengthUMC = previousCols;
    
    if  (rowlengthUMC < boardSize && rowlengthUMC >= 0 && colslengthUMC < boardSize && colslengthUMC >= 0){
    
    
    if (rowlengthUMC == rows && colslengthUMC == cols)
        upperMiddleCorner = true;
    }
    
    // upper left Corner
    int rowlengthULC = previousRows  - 1;
    int colslengthULC = previousCols - 1;
    
    if  (rowlengthULC < boardSize && rowlengthULC >= 0 && colslengthULC < boardSize && colslengthULC >= 0){
        
    if (rowlengthULC == rows && colslengthULC == cols)
        upperLeftCorner = true;
    }
    
    // left side
    
    int rowsLeftSide = previousRows;
    int colsLeftSide = previousCols - 1;
    
    if  (rowsLeftSide  < boardSize && rowsLeftSide  >= 0 && colsLeftSide < boardSize && colsLeftSide >= 0){
    
    if (rowsLeftSide == rows && colsLeftSide == cols)
        leftSide = true;
    }
    //right side
    int rowsRightSide = previousRows;
    int colsRightSide = previousCols + 1;
    
    if  (rowsRightSide  < boardSize && rowsRightSide   >= 0 && colsRightSide < boardSize && colsRightSide >= 0){
    
    if (rowsRightSide == rows && colsRightSide == cols)
        rightSide = true;
    }
    
    //bottom right corner
    
    int rowsBottomRight = previousRows + 1;
    int colsBottomRight = previousCols + 1;
    
    if  (rowsBottomRight  < boardSize && rowsBottomRight >= 0 && colsBottomRight < boardSize && colsBottomRight >= 0){
    
    if (rowsBottomRight == rows && colsBottomRight== cols)
        bottomRightCorner = true;
    
    }
    
    // bottom Middle Corner
    
    int rowsBottomMiddle = previousRows + 1;
    int colsBottomMiddle = previousCols;
    if  (rowsBottomMiddle  < boardSize && rowsBottomMiddle >= 0 && colsBottomMiddle < boardSize && colsBottomMiddle >= 0){
    
    if (rowsBottomMiddle == rows && colsBottomMiddle== cols)
        bottomMiddleCorner = true;
    
    }
    // bottom Left Corner
    
    int rowsBottomLeft = previousRows + 1;
    int colsBottomLeft = previousCols - 1;
    
    if  (rowsBottomLeft  < boardSize && rowsBottomLeft >= 0 && colsBottomLeft < boardSize && colsBottomLeft >= 0){
    
    if (rowsBottomLeft == rows && colsBottomLeft== cols)
        bottomLeftCorner = true;
    }
    
    return upperRightCorner || upperMiddleCorner || upperLeftCorner || leftSide || rightSide ||
    bottomRightCorner || bottomMiddleCorner || bottomLeftCorner;
}



//returns true if any of the adjoining rows and columns contains the character chs
    bool isAdjacent(char chs, int rows, int cols, const Grid <char> lettersUsed, int boardSize){
        
        bool upperRightCorner = false;
        bool upperMiddleCorner = false;
        bool upperLeftCorner = false;
        bool leftSide = false;
        bool rightSide= false;
        bool bottomRightCorner= false;
        bool bottomMiddleCorner= false;
        bool bottomLeftCorner= false;
        
        //Upper right Corner
        int rowlengthURC = rows  - 1;
        int colslengthURC = cols + 1;
        
        
        if  (rowlengthURC < boardSize && rowlengthURC >= 0 && colslengthURC < boardSize && colslengthURC >= 0){
            
            if (lettersUsed.get(rowlengthURC ,colslengthURC) == chs)
            upperRightCorner = true;
        }
        // upper middle corner
        int rowlengthUMC = rows  - 1;
        int colslengthUMC = cols;
        if  (rowlengthUMC < boardSize && rowlengthUMC >= 0 && colslengthUMC < boardSize && colslengthUMC >= 0){
            
           if (lettersUsed.get(rowlengthUMC, colslengthUMC) == chs)
            upperMiddleCorner = true;
        }
        // upper left Corner
        int rowlengthULC = rows  - 1;
        int colslengthULC = cols - 1;
        if  (rowlengthULC < boardSize && rowlengthULC >= 0 && colslengthULC < boardSize && colslengthULC >= 0){
            
            if (lettersUsed.get(rowlengthULC, colslengthULC) == chs)
            upperLeftCorner = true;
        }
        // left side
        int rowsLeftSide = rows;
        int colsLeftSide = cols - 1;
        if  (rowsLeftSide  < boardSize && rowsLeftSide  >= 0 && colsLeftSide < boardSize && colsLeftSide >= 0){
            
            if (lettersUsed.get(rowsLeftSide, colsLeftSide) == chs)
            leftSide = true;
        }
        //right side
        int rowsRightSide = rows;
        int colsRightSide = cols + 1;
        if  (rowsRightSide  < boardSize && rowsRightSide   >= 0 && colsRightSide < boardSize && colsRightSide >= 0){
            
        if (lettersUsed.get(rowsRightSide , colsRightSide) == chs)
            rightSide = true;
        }
        //bottom right corner
        
        int rowsBottomRight = rows + 1;
        int colsBottomRight = cols + 1;
        if  (rowsBottomRight  < boardSize && rowsBottomRight >= 0 && colsBottomRight < boardSize && colsBottomRight >= 0){
            
        if (lettersUsed.get(rowsBottomRight , colsBottomRight) == chs)
            bottomRightCorner = true;
        }
        // bottom Middle Corner
        
        int rowsBottomMiddle = rows + 1;
        int colsBottomMiddle = cols;
        if  (rowsBottomMiddle  < boardSize && rowsBottomMiddle >= 0 && colsBottomMiddle < boardSize && colsBottomMiddle >= 0){
           
        if (lettersUsed.get(rowsBottomMiddle , colsBottomMiddle) == chs)
            bottomMiddleCorner = true;
        }
        // bottom Left Corner
        
        int rowsBottomLeft = rows + 1;
        int colsBottomLeft = cols - 1;
        if  (rowsBottomLeft  < boardSize && rowsBottomLeft >= 0 && colsBottomLeft < boardSize && colsBottomLeft >= 0){
            
        if (lettersUsed.get(rowsBottomLeft , colsBottomLeft) == chs)
            bottomLeftCorner = true;
        }
                    
        
    return upperRightCorner || upperMiddleCorner || upperLeftCorner || leftSide || rightSide ||
        bottomRightCorner || bottomMiddleCorner || bottomLeftCorner;
        
        
}

//COMPUTERS TURN STARTS HERE

Set <string> computersTurn(Grid <char> lettersUsed, int boardSize) {
    
    Lexicon wordDirectory("EnglishWords.dat");

    Set<string> allTheWords; // I use the set to check if any words have been repeated
    
    Vector <Vector <int> >alreadyUsedRowsAndColumns; // use this to hold the rows and columns that
                                                    // have already been used
    
    int rows;
    int cols;
    
    Vector <string> listOfWords;
    
    
    for (int i = 0; i < lettersUsed.numRows(); i++){
        for (int j = 0; j < lettersUsed.numCols(); j++){
            Vector <int> rowsAndColumns;
            string solution = "";
            char ch = lettersUsed.get(i, j);
            solution += ch;
            rows = i;
            cols = j;
            rowsAndColumns.add(i);
            rowsAndColumns.add(j);
            alreadyUsedRowsAndColumns.add(rowsAndColumns);
            Vector <Vector <int> > nextLetters = findNextPossibleLetters( rows, cols, wordDirectory, lettersUsed,  alreadyUsedRowsAndColumns, boardSize );
            
                // recursive funtion
            Vector <string> list = howManyWordsCanBeFormed( solution, nextLetters, wordDirectory,
                                                           lettersUsed,  alreadyUsedRowsAndColumns,
                                                        listOfWords, boardSize);
            //listOfPossibleWords.add(list);
            for(int k=0;k<list.size();k++)
            {
                string currentWord = list.get(k);
                if (!allTheWords.contains(currentWord))
                    allTheWords.add(currentWord);
            }
            alreadyUsedRowsAndColumns.remove(0);
                
            }
        }
    return allTheWords;
             }
    
    
    
    

// This function finds the next possible letters that can form words
    
Vector <Vector <int> > findNextPossibleLetters ( int rows, int cols, Lexicon lexicon,  Grid <char> lettersUsed, Vector <Vector <int> > & alreadyUsedRowsAndColumns, int boardSize) {
    
    Vector<Vector<int> >allPossibilities;
    
    
    Vector <int> numbersUsed;
        
        //Upper right Corner
        
        int rowlengthURC = rows  - 1;
        int colslengthURC = cols + 1;
        
        
        if  (rowlengthURC < boardSize && rowlengthURC >= 0 && colslengthURC < boardSize && colslengthURC >= 0){
        
              Vector <int> numbers;
              numbers.add( rowlengthURC);
                numbers.add(colslengthURC);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowlengthURC && count.get(1) == colslengthURC)
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        // upper middle corner
        int rowlengthUMC = rows  - 1;
        int colslengthUMC = cols;
        if  (rowlengthUMC < boardSize && rowlengthUMC >= 0 && colslengthUMC < boardSize && colslengthUMC >= 0){
            
            
            Vector <int> numbers;
                numbers.add( rowlengthUMC);
                numbers.add(colslengthUMC);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowlengthUMC && count.get(1) == colslengthUMC )
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        // upper left Corner
        int rowlengthULC = rows  - 1;
        int colslengthULC = cols - 1;
        if  (rowlengthULC < boardSize && rowlengthULC >= 0 && colslengthULC < boardSize && colslengthULC >= 0){
           
           
                Vector <int> numbers;
                numbers.add( rowlengthULC);
                numbers.add(colslengthULC);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowlengthULC && count.get(1) == colslengthULC)
                    numbers.clear();
        }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        // left side
        int rowsLeftSide = rows;
        int colsLeftSide = cols - 1;
        if  (rowsLeftSide  < boardSize && rowsLeftSide  >= 0 && colsLeftSide < boardSize && colsLeftSide >= 0){
            
           
              Vector <int> numbers;
               numbers.add( rowsLeftSide);
                numbers.add(colsLeftSide);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowsLeftSide && count.get(1) == colsLeftSide)
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        
        //right side
        int rowsRightSide = rows;
        int colsRightSide = cols + 1;
        if  (rowsRightSide  < boardSize && rowsRightSide   >= 0 && colsRightSide < boardSize && colsRightSide >= 0){
        
            Vector <int> numbers;
                numbers.add( rowsRightSide);
                numbers.add(colsRightSide);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowsRightSide && count.get(1) == colsRightSide)
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
            
        }
        
        //bottom right corner
        
        int rowsBottomRight = rows + 1;
        int colsBottomRight = cols + 1;
        if  (rowsBottomRight  < boardSize && rowsBottomRight >= 0 && colsBottomRight < boardSize && colsBottomRight >= 0){
           
            
            Vector <int> numbers;
                numbers.add( rowsBottomRight);
                numbers.add(colsBottomRight);
                
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowsBottomRight && count.get(1) == colsBottomRight)
                    numbers.clear();
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        // bottom Middle Corner
        
        int rowsBottomMiddle = rows + 1;
        int colsBottomMiddle = cols;
        if  (rowsBottomMiddle  < boardSize && rowsBottomMiddle >= 0 && colsBottomMiddle < boardSize && colsBottomMiddle >= 0){
            
            
            Vector <int> numbers;
                numbers.add( rowsBottomMiddle);
                numbers.add(colsBottomMiddle);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowsBottomMiddle && count.get(1) == colsBottomMiddle)
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }
        
        // bottom Left Corner
        
        int rowsBottomLeft = rows + 1;
        int colsBottomLeft = cols - 1;
        if  (rowsBottomLeft  < boardSize && rowsBottomLeft >= 0 && colsBottomLeft < boardSize && colsBottomLeft >= 0){
                       
                Vector <int> numbers;
                    numbers.add( rowsBottomLeft);
                    numbers.add(colsBottomLeft);
            for (int i = 0; i < alreadyUsedRowsAndColumns.size(); i++){
                Vector <int> count = alreadyUsedRowsAndColumns.get(i);
                if (count.get(0) == rowsBottomLeft && count.get(1) == colsBottomLeft)
                    numbers.clear();
                
            }
            if (numbers.size() != 0)
                allPossibilities.add(numbers);
        }return allPossibilities;
        
            } 
    


// recursive function to find all possible letters given a letter and the possiblities of the next letter

Vector <string> howManyWordsCanBeFormed ( string solution, Vector <Vector <int> > nextLetters, Lexicon lex, Grid <char> lettersUsed,  Vector <Vector <int> > & alreadyUsedRowsAndColumns, Vector <string>& listOfWords, int boardSize){
    
    //Base case
    if (lex.contains(solution) && solution.length() >= 4 && !wordContained(solution,listOfWords)){
        listOfWords.add(solution);
        
        if (!lex.containsPrefix(solution))
            solution = solution.erase(0);
    }
    
    if(wordContained(solution, listOfWords) && !wordContained(solution,listOfWords) )
        solution.erase(0);
    
    // Recursive case
    
    
    for (int i = 0; i < nextLetters.size(); i++) {
        Vector <int> numbers = nextLetters.get(i);
        int rows = numbers.get(0);
        int cols = numbers.get(1);
        char chs = lettersUsed.get(rows,cols);
        
        solution += chs;
        if (lex.containsPrefix(solution) && solution.length() != 0){
            alreadyUsedRowsAndColumns.add(numbers);
        Vector <Vector <int> > lettersPossible = findNextPossibleLetters(rows, cols, lex, lettersUsed,  alreadyUsedRowsAndColumns, boardSize);
        Vector <string> beslist = howManyWordsCanBeFormed(solution, lettersPossible, lex,
                                                       lettersUsed,alreadyUsedRowsAndColumns,
                                                          listOfWords, boardSize);
            alreadyUsedRowsAndColumns.remove(alreadyUsedRowsAndColumns.size() - 1);
        }
        else if (lex.contains(solution) && solution.length() != 0 && !wordContained(solution,listOfWords)){
             listOfWords.add(solution);
        }
        solution.erase(solution.length() - 1,1);
      
        
    
    }
    
    return listOfWords;
    
}

// This function checks if the vector already contains the given word
    
bool wordContained (string word, Vector <string> words ){
    
    for (int i = 0; i < words.size(); i++){
        if (words.get(i) == word)
            return true;
        
    } return false;
    
}
    
    
    


