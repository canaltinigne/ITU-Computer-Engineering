// BLG 252E - Homework 2
// Can Yılmaz Altıniğne - 150130132

#ifndef moveClasses_h
#define moveClasses_h

// ------------------------------ RED CLASS --------------------------------------

class Red: public Base {

public:
    
    Red(Base * ptr = NULL, char c = 'R'):Base(ptr,c){}      // Constructor for Red
    
    ~Red(){}
    
    void compare(Base *);

};

void Red::compare(Base *ptr){               // Compare Function for Red
    char otherCard = ptr->getCard();        // Get the other list's card in this order
    
    switch (otherCard) {                    // Compare two cards
        case 'R':
            setResult(Tie);                 // Set result for card in 1st player's list
            ptr->setResult(Tie);            // Set Result for card in 2nd player's list
            break;
            
        case 'D':                           // Other compare functions works in the sameway.
            setResult(Lose);
            ptr->setResult(Win);
            break;
            
        case 'B':
            setResult(Lose);
            ptr->setResult(Win);
            break;
            
        case 'G':
            setResult(Win);
            ptr->setResult(Lose);
            break;
    }
}

// ------------------------------------------------------------------------------------
// ************************************************************************************
// ------------------------------ BLUE CLASS ------------------------------------------

class Blue: public Base {

public:
    
    Blue():Base(NULL,'B'){}             // Constructor for Blue
    
    ~Blue(){}
    
    void compare(Base *);
};

void Blue::compare(Base *ptr){              // Compare Function for Blue
    
    char otherCard = ptr->getCard();
    
    switch (otherCard) {
        case 'R':
            setResult(Win);
            ptr->setResult(Lose);
            break;
            
        case 'D':
            setResult(Lose);
            ptr->setResult(Win);
            break;
            
        case 'B':
            setResult(Tie);
            ptr->setResult(Tie);
            break;
            
        case 'G':
            setResult(Lose);
            ptr->setResult(Win);
            break;
    }
}

// ------------------------------------------------------------------------------------
// ************************************************************************************
// ------------------------------ GREEN CLASS -----------------------------------------

class Green: public Base {

public:
    Green():Base(NULL,'G'){}        // Constructor for Green
    
    ~Green(){}
    
    void compare(Base *);
};

void Green::compare(Base *ptr){             // Compare Function for Green
    
    char otherCard = ptr->getCard();
    
    switch (otherCard) {
        case 'R':
            setResult(Lose);
            ptr->setResult(Win);
            break;
            
        case 'D':
            setResult(Win);
            ptr->setResult(Lose);
            break;
            
        case 'B':
            setResult(Win);
            ptr->setResult(Lose);
            break;
            
        case 'G':
            setResult(Tie);
            ptr->setResult(Tie);
            break;
    }
}

// ------------------------------------------------------------------------------------
// ************************************************************************************
// ------------------------------ DARK RED CLASS --------------------------------------

class DarkRed: public Red {

public:
    DarkRed():Red(NULL,'D'){}               // Constructor for DarkRed
    
    ~DarkRed(){}
    
    void compare(Base *);
};

void DarkRed::compare(Base *ptr){               // Compare Function for Dark Red
    
    char otherCard = ptr->getCard();
    
    switch (otherCard) {
        case 'R':
            setResult(Win);
            ptr->setResult(Lose);
            break;
            
        case 'D':
            setResult(Tie);
            ptr->setResult(Tie);
            break;
            
        case 'B':
            setResult(Win);
            ptr->setResult(Lose);
            break;
            
        case 'G':
            setResult(Lose);
            ptr->setResult(Win);
            break;
    }
}

// ------------------------------------------------------------------------------------

#endif
