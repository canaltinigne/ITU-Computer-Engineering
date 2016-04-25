// BLG 252E - Homework 2
// Can Yılmaz Altıniğne - 150130132

#ifndef baseClass_h
#define baseClass_h

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>        // Just For Reverse function

using namespace std;

enum outcome {
    Lose,
    Tie,
    Win
};

class Base {                    // Abstract Base Class
    
    friend class HetList;       // HetList is friend to use next pointer
    outcome result;
    Base * next;                // To hold next member in the list
    char card;                  // To understand which card it is
    
public:
    Base(Base * ptr, char x): next(ptr), card(x){};
    virtual ~Base(){};
    
    virtual void compare(Base *) = 0;       // Pure virtual function
    
    char getCard() const{                   // To get card's kind
        return card;
    }
    
    void setResult(outcome x){              // To set outcome (W,T,L)
        result = x;
    }
    
    int getResult() const{              // To get result
        return result;
    }
    
    Base * getNext() const{             // To get next pointer
        return next;
    }
};

#endif 