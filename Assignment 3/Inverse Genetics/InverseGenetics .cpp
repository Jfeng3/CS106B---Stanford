/*
 * This is the solution for th einverse Genetics problem 
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "queue.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */


void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void listAllPossibilities(string protein, Queue <Set<string> > database, Map<char, Set<string> >& codons);
void printAcids(Queue<Set<string> >  database);

void findAllWords(string protein,Map<char, Set<string> >& codons,string solution);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
    string protein = "FI";
     listAllRNAStrandsFor(protein , codons);
    return 0;
}


Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;
    
    /* The current codon / protein combination. */
    string codon;
    char protein;
    
    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
    
    return result;
}

//Wrapper function for the recursive function findAllWords

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    
      findAllWords( protein, codons, "");
   
}

// Recursive function

void findAllWords(string protein,Map<char, Set<string> >& codons,string solution)
   
{
 
    // base function
    
    if (protein == "")
    {   
        cout<<solution<< endl;
        return;
    }
    
    string save = protein;
    Set<string> currentSet = codons.get(protein[0]);
    foreach(string s in currentSet)
    {
    
        solution = solution + s;
        findAllWords(protein.erase(0,1),codons,solution);
        solution.erase(solution.length() - 3, 3);
        protein = save;
    }
}
