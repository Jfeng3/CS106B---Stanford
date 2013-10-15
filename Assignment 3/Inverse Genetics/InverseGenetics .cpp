/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
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

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    
      findAllWords( protein, codons, "");
   
}

void findAllWords(string protein,Map<char, Set<string> >& codons,string solution)
   
{
//    int count = 0;
    if (protein == "")
    {   
        cout<<solution<< endl;
//         count++;
    
        
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