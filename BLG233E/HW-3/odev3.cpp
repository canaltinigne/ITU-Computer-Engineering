/*
 * @Author
 * Student Name: Can Yılmaz Altıniğne * Student ID : 150130132
 * Date: 12 / 12 / 2015
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

struct Unshuffled{          // This is for the card array that I shuffle they do not need next pointer so I created this struct.
    char type;
    char val[3];
};

struct Card{                // This is for the cards in queue. I use char array for value because of they have numbers or characters.
    char type;
    char val[3];
    Card * next;
};

//  ---------- STACK AND STACK FUNCTIONS -------------

struct Stack{
    Card *head;
    void create();
    void close();
    void push(Unshuffled);
    Unshuffled pop();
    bool isempty();
};

void Stack::create(){
    head=NULL;
}

void Stack::close(){
    Card *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}

void Stack::push(Unshuffled newdata){
    Card *newnode = new Card;
    newnode->type = newdata.type;
    strcpy(newnode->val, newdata.val);
    newnode->next = head;
    head = newnode;
}

Unshuffled Stack::pop(){
    
    Unshuffled temp = {'0',"0"};
    
    if (isempty())
        return temp;
    
    Card *topnode = head;
    head = head->next;
    temp.type = topnode->type;
    strcpy(temp.val, topnode->val);
    
    delete topnode;
    return temp;
}

bool Stack::isempty(){
    return (head == NULL);
}

// ----------------------------------------------------------------

// -------------- QUEUE & QUEUE FUNCTIONS ----------------

struct Queue {
    Card *front;
    Card *back;
    void create();
    void close();
    void enqueue(Unshuffled);
    Unshuffled dequeue();
    bool isempty();
};

void Queue::create(){
    front = NULL; back = NULL;
}

void Queue::close(){
    
    Card *p;
    while (front) {
        p = front;
        front = front->next;
        delete p;
    }
}

void Queue::enqueue(Unshuffled newdata){
    
    Card *newnode = new Card;
    newnode->type = newdata.type;
    strcpy(newnode->val,newdata.val);
    newnode->next = NULL;
    
    if ( isempty() ) {
        back = newnode;
        front = back;
    }
    else {
        back->next = newnode;
        back = newnode;
    }
}

bool Queue::isempty() {
    return front == NULL;
}

Unshuffled Queue::dequeue() {
    
    Unshuffled temp = {'0',"0"};
    Card *topnode;
    topnode = front;
    temp.type = topnode->type;
    strcpy(temp.val, topnode->val);
    front = front->next;
    delete topnode;
    return temp;
}

// -------------------------------------------------------------

// Initializing of the deck is here in an array

Unshuffled unshuffledDeck[52] = { {'H',"A"},{'H',"2"},{'H',"3"},{'H',"4"},{'H',"5"},{'H',"6"},{'H',"7"},{'H',"8"},{'H',"9"},{'H',"10"},{'H',"J"},{'H',"Q"},{'H',"K"},
    {'D',"A"},{'D',"2"},{'D',"3"},{'D',"4"},{'D',"5"},{'D',"6"},{'D',"7"},{'D',"8"},{'D',"9"},{'D',"10"},{'D',"J"},{'D',"Q"},{'D',"K"},
    {'C',"A"},{'C',"2"},{'C',"3"},{'C',"4"},{'C',"5"},{'C',"6"},{'C',"7"},{'C',"8"},{'C',"9"},{'C',"10"},{'C',"J"},{'C',"Q"},{'C',"K"},
    {'S',"A"},{'S',"2"},{'S',"3"},{'S',"4"},{'S',"5"},{'S',"6"},{'S',"7"},{'S',"8"},{'S',"9"},{'S',"10"},{'S',"J"},{'S',"Q"},{'S',"K"} };


int fortunesOrder = 1;    // Global variable for counting 13's
int fortuneSum = 0;     // Global variable for sum of the values at the end
int limitVal = 0;       // Global variable to be used for calling recursive shuffle and recursive assign functions

Queue shuffledDeck;         // Queue for Shuffled Deck
Stack temporarySpace;       // Stack for temporary Space
Queue specialSpace;         // Queue for Special Space
ofstream outputFile;        // Output text file

void swapDeck(){                    // Randomly Swaping two cards function
    int a = rand() % 52;
    int b = rand() % 52;
    
    Unshuffled temp = unshuffledDeck[a];
    unshuffledDeck[a] = unshuffledDeck[b];
    unshuffledDeck[b] = temp;
}

void recursiveShuffle(int i){       // Recursive Shuffle Function
    if (i == 200) {                 // Limit is 200. 200 times random 2 cards are switched places in unshuffledDeck array.
        return;
    } else {
        swapDeck();                     // swapDeck() function is called
        recursiveShuffle(++limitVal);   // Recursion
    }
}

void recursiveAssign(int i){            // Recursive assign function to assign cards
    if (i == 52) {                      // from unshuffled deck to queue of shuffledDeck
        return;
    } else {
        shuffledDeck.enqueue(unshuffledDeck[i]);
        recursiveAssign(++limitVal);
    }
}

void recursiveThirteenth(int i){                    // Recursive function to count 13's
    if (shuffledDeck.front != NULL) {               // If there are cards in shuffled deck the function works
        Unshuffled temp;                            // Unshuffled variable which does not have next pointer
        temp = shuffledDeck.dequeue();              // The first element from queue is dequeued and temp is
        int order;                                  // initialized as dequeued element
        bool akqj = false;                          // Is card one of A, K, Q or J ? value variable is for order of card.
        
        if (strcmp(temp.val, "A") == 0) {           // If dequeued card is A. Its order is 1 and akqj is true.
            order = 1;
            akqj = true;
        } else if (strcmp(temp.val, "J") == 0) {    // If dequeued card is J. Its order is 11 and akqj is true.
            order = 11;
            akqj = true;
        } else if (strcmp(temp.val, "Q") == 0) {    // If dequeued card is Q. Its order is 12 and akqj is true.
            order = 12;
            akqj = true;
        } else if (strcmp(temp.val, "K") == 0) {    // If dequeued card is K. Its order is 13 and akqj is true.
            order = 13;
            akqj = true;
        } else {                    // Else card's order is its value.
            order = atoi(temp.val);
        }
        
        if (order == i) {               // If order equals to card's value which the function takes "fortunesOrder 1 to 13"
            
            specialSpace.enqueue(temp);     // Enqueue the card to special space
            outputFile << endl << i << ":" << temp.type << ":" << temp.val << ":match";     // Write in text file the card and match
            
            if (akqj == true) {             // If card is one of the A K Q or J. Increase the global variable for sum by 10
                fortuneSum += 10;
            } else {                        // Else increase the sum by its value
                fortuneSum += order;
            }
            
            fortunesOrder = 1;          // Make the global fortunesOrder 1.
                                                    // Because the counting ends as the order and value card was found.
            while (temporarySpace.head != NULL) {       // Until there are no cards in tempSpace
                shuffledDeck.enqueue(temporarySpace.pop());     // Enqueue them to shuffledDeck queue.
            }
            
            recursiveThirteenth(fortunesOrder);         // Call the counting 13s function from 1
            
        } else {                        // If the order does not equal to cards value
            temporarySpace.push(temp);      // Push them to temporarySpace
            outputFile << endl << i << ":" << temp.type << ":" << temp.val << ":unmatch";     // Write in text file the card and unmatch
            ++fortunesOrder;        // Increase global fortunesOrder value
            
            if (fortunesOrder == 14) {      // If fortunesOrder equals to 14 which means the function has been called 13 times
                temporarySpace.close();     // it means card was not found in that 13, so clean the temporary space and call
                fortunesOrder = 1;          // the counting 13s function from 1 to look at next 13 cards.
            }
            
            recursiveThirteenth(fortunesOrder);     // Calling
        }
    }
    
    return;
}

int main() {
    
    srand((unsigned int)time(NULL));
    
    outputFile.open("output.txt");
    
    recursiveShuffle(limitVal);     // Shuffle the cards, global limitVal is 0 already.
    
    shuffledDeck.create();          // Queues and Stacks were created
    temporarySpace.create();
    specialSpace.create();
    
    limitVal = 0;           // After recursiveShuffle limitVal is 200 and we make it 0 to use it to call recursiveAssign
    
    recursiveAssign(limitVal);      // The cards in array are being assigned to shuffled Deck Queue
    
    int y = 0;
    
    Card * traverse = shuffledDeck.front;
    
    outputFile << "Shuffled Deck:" << endl;     // Writing shuffled deck to text file
    
    while (traverse != NULL) {
        outputFile << ++y << ":" << traverse->type << ":" << traverse->val << endl;
        traverse = traverse->next;
    }
    
    outputFile << endl << "Fortune-telling steps:";     // Writing fortune telling steps to textfile
    
    recursiveThirteenth(fortunesOrder);             // This function counts 13s make all operations of stacks and queues
                                                    // fortunesOrder starts from 1.
    Card * ptr = specialSpace.front;
    
    outputFile << endl << endl << "Fortune Results:" << endl;       // Writing fortune results to text file
    
    while (ptr != NULL) {
        outputFile << ptr->type << " " << ptr->val << endl;
        ptr = ptr->next;
    }
    
    outputFile << endl << "Sum: " << fortuneSum;            // Writing Sum to text file by using global sum variable.
    
    if (fortuneSum >= 50) {
        outputFile << endl << "Your wish will come true !";
    } else {
        outputFile << endl << "Bad luck ! Your wish won't come true !";
    }
    
    cout << "Output file has been created. Program exits......." << endl;
    
    shuffledDeck.close();                       // Closing stacks and queues.
    temporarySpace.close();
    specialSpace.close();
    outputFile.close();
    
    return 0;
}



