// BLG 252E - Homework 2
// Can Yılmaz Altıniğne - 150130132

#ifndef usedFunctions_h
#define usedFunctions_h

// I use These two functions for reading input and displaying results they are not member of any class

// DISPLAY RESULTS FUNCTION

void displayResults(HetList & playerOne, HetList & playerTwo, string playerOneCards, string playerTwoCards){
    
    int resPlayer1[3] = {0};        // array of integers to keep total win, tie and loss for player1
    int resPlayer2[3] = {0};        // array of integers to keep total win, tie and loss for player1
    
    cout << "Player1: " << playerOneCards << endl;  // String that getInput function read and reverse for player1
    cout << "Player2: " << playerTwoCards << endl;  // String that getInput function read and reverse for player1
    
    cout << "Score1:  ";            // Call print function in HetList to print results for player 1
    playerOne.print(resPlayer1);    // print function's other mission is to take integer array to set total win, tie, loss for players
    
    cout << endl << "Score2:  ";       // Call print function in HetList to print scores for player 2
    playerTwo.print(resPlayer2);
    
    // Print total wins, ties and losses for players
    
    cout << endl <<"Total Score1:  " << "Lose: " << resPlayer1[Lose] << " Tie: " << resPlayer1[Tie] << " Win: " << resPlayer1[Win] << endl;
    cout << "Total Score2:  " << "Lose: " << resPlayer2[Lose] << " Tie: " << resPlayer2[Tie] << " Win: " << resPlayer2[Win] << endl;
    
    if (resPlayer1[Win] > resPlayer2[Win]) {            // Compare total wins for players and determine the winner
        cout << "Winner: Player1" << endl;
    } else if(resPlayer1[Win] == resPlayer2[Win]){
        cout << "Tie Game !" << endl;
    } else {
        cout << "Winner: Player2" << endl;
    }
}

//  GET INPUT FROM FILE FUNCTION

string getInput(ifstream & file, HetList & player){
    
    int a = 0;
    
    string line;
    getline(file,line);                     // Read the line from text file
    string returnLine = line;               // I use returnLine string to return read line from file, in the end of the program as you can see above
    reverse(line.begin(), line.end());      // Display results function takes this string to print player's deck.
                                            // I reversed the string because I want to keep the order of cards as in the text file
    while (line[a] != '\0') {               // Because my insert to List function inserts new elements to head so i reversed string and first card in the text
                                            // becomes the head of the list
        if (line[a] == ' ') {               // Skip spaces
            
            a++;
            
        } else {
            
            Base * add;                     // add pointer
            
            switch (line[a]) {
                case 'B':
                    add = new Blue();       // if the char is B new element is blue
                    player.insert(add);     // insert it to list
                    break;
                    
                case 'D':
                    add = new DarkRed();    // if the char is D new element is blue
                    player.insert(add);     // insert it to list
                    break;
                    
                case 'G':
                    add = new Green();      // if the char is G new element is blue
                    player.insert(add);     // insert it to list
                    break;
                    
                case 'R':
                    add = new Red();        // if the char is R new element is blue
                    player.insert(add);     // insert it to list
                    break;
            }
            
            a++;
        }
    }
    
    return returnLine;
}

#endif