// BLG 252E - Homework 2
// Can Yılmaz Altıniğne - 150130132

#include "baseClass.h"
#include "moveClasses.h"
#include "hetlist.h"
#include "usedFunctions.h"

int main() {
    
    ifstream inputFile;
    inputFile.open("deck.txt");             // Open file
    inputFile.seekg(0);                     // Take the cursor to beginning
    
    HetList player1, player2;               // Two lists for 2 players

    string player1line = getInput(inputFile,player1);       // get line from file for 2 players, add the cards player's list and return
    string player2line = getInput(inputFile,player2);       // the read line to use it in the display results function
    
    player1.traverser(player2.getHead());                       // Compare two lists
    displayResults(player1, player2, player1line, player2line); // Display Results
    
    inputFile.close();                                  
    return 0;
}