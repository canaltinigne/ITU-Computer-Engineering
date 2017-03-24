//  Analysis of Algorithms I - HW 4
//  Can Yılmaz Altıniğne - 150130132

#ifndef hashtab_h
#define hashtab_h

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

#define ll long long                    // typing long long everytime is too long

class myHash {
    
    std::string * myHashTable;
    int totalEntries;
    
public:
    
    ll _tableSize;
    int collision;
    
    myHash(ll tableSize);
    ~myHash();
    
    //  INSERT, RETRIEVE, REMOVE & HASH FUNCTION
    
    void insert(std::string s);
    ll hashFunc(std::string s);
    bool retrieve(std::string s, bool);
    bool remove(std::string s);
    
    //  ADDED FUNCTIONS FOR PRINTING HASH TABLE & TAKING INPUT FROM FILE AND SPLIT IT BY ':'
    
    void print_list(std::ofstream&);
    
    static void split_command(std::string command, std::string * arr){
        std::stringstream ss_command(command);
        std::string ss_partition;
        
        int a = 0;
        
        while(getline(ss_command, ss_partition, ':')) arr[a++] = ss_partition;          // SPLIT LINE INTO TWO PARTS BEFORE ':' -command-, AFTER ':' -key-
    }
};

myHash::myHash(ll tableSize){
    
    _tableSize = tableSize;                         // INITIALIZE HASH TABLE
    totalEntries = 0;
    collision = 0;
    
    myHashTable = new std::string[_tableSize];
    
    for (ll a = 0; a < _tableSize; a++) myHashTable[a] = "?";           // '?' IS PUT IN EMPTY SPACES -what are we living for-
}

myHash::~myHash(){
    delete [] myHashTable;
}

void myHash::print_list(std::ofstream& output){
    for (ll a = 0; a < _tableSize; a++) output << a << ":" << myHashTable[a] << std::endl;
}

bool myHash::retrieve(std::string s, bool generate_correction){
    
    ll index = hashFunc(s);                         // CALCULATE INDEX OF KEY
    ll i = 0, position;                             // I IS 0 INITIALLY
    ll collision_before_operation = collision;      // COLLISION NUMBER BEFORE OPERATIONS, WE NEED TO SEE HOW MANY COLLISIONS OCCURED IN THIS OPERATION
    position = index;                               // POSITION IS THE RESULT OF HASH FUNCTION
    std::string temp = s;
    
    while (myHashTable[position] != "?") {          // UNTIL WE SEE EMPTY SPACE IN THE POSITION KEEP GOING
        
        if (myHashTable[position] != s) {           // IF THE STRING IN THAT POSITION IS NOT EQUAL TO OUR KEY INCREASE I AND COLLISION
            i++;
            
            if(!generate_correction) collision++;         // generate_correction IS JUST FOR SHOWING MESSAGES, generate_correction is WORK WHEN THE SPELL
                                                          // BECAUSE THIS RETRIEVE FUNCTION IS ALSO USED WHEN WE TRY TO GENERATE CORRECTION BY CHANGING ONE CHAR IN STRING
        } else {                                          // WHEN WE ARE LOOKING FOR CORRECTIONS WE DO NOT WANT TO SEE ANY MESSAGE ON CONSOLE WE JUST WANT TO GET TRUE OR FALSE VALUE
            if (!generate_correction) {                   // TO UNDERSTAND THAT WORD IS IN THE HASH TABLE AND WE DO NOT WANT TO INCREASE COLLISION WHEN WE GENERATE CORRECTIONS
                
                std::cout << "RETRIEVE: The word '" << s << "' found in the dictionary with index: " << position <<std::endl;   // --------------------------------------------
                std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;                             //
            }                                                                                                                   //  WHEN THE STRING IS FOUND IN THAT INDEX
                                                                                                                                //  THIS PART WORKS
            return true;                                                                                                        //
        }                                                                                                                       // --------------------------------------------
        
        position = (index + i) % _tableSize;                                                                                    // FIND THE NEW POSITION WITH INCREASED I (LINEAR PROBING)
        
        if (position == index) break;                                                                                           // IF WE COME TO SAME POSITION BREAK THE LOOP (TRAVERSED WHOLE ARRAY)
    }
    
    if (!generate_correction) {                                                                                                 // OUR KEY IS NOT IN THE ARRAY IF WE ARE NOT LOOKING FOR GENERATING
        std::cout << "The word '" << s << "' couldn't be found in the dictionary." << std::endl;                                // CORRECTIONS PRINT THE NOT FOUND MESSAGE
        std::cout << "Looking for possible suggestions." << std::endl;
        std::cout << "SUGGESTIONS for " << s << ":";
        
        for (int a = 0; a < s.length(); a++) {                                                                                  // LOOK FOR ALL VARIANTS OF STRING
            s = temp;
            for (int b = 97; b < 123; b++) {
                s[a] = b;
                
                if (temp != s) {
                    if (retrieve(s, true)) std::cout << " " << s << ",";                                                   // USE RETRIEVE FUNCTION TO LOOK THE VARIANT
                }                                                                                                          // BUT THIS TIME SEND TRUE FOR generate_correction PARAMETER
            }                                                                                                              // BECAUSE WE DO NOT WANT TO SEE MESSAGES WE JUST WANT TRUE OR FALSE VALUE
        }
        
        std::cout << std::endl << "COLLISIONS :" << collision - collision_before_operation << std::endl;
    }
    
    return false;                                                                                                               // KEY IS NOT FOUND
}

bool myHash::remove(std::string s){
    
    ll index = hashFunc(s);                                         // SAME AS IN RETRIEVE FUNCTION
    ll i = 0, position;
    ll collision_before_operation = collision;
    position = index;
    
    while (myHashTable[position] != "?") {                                      // LOOK UNTIL EMPTY PLACE
        
        if (myHashTable[position] != s) {       // NOT EQUAL TO OUR KEY INCREASE COLLISION AND I TO LOOK AT NEXT PLACE (LINEAR PROBING)
            collision++;
            i++;
                
        } else {                                            // KEY IS FOUND DELETE IT
            myHashTable[position] = "*";
            std::cout << "REMOVE: The word '" << s << "' is removed from the dictionary." << std::endl;
            std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;
            totalEntries--;
            return true;
        }
        
        position = (index + i) % _tableSize;            // LOOK FOR NEW POSITION
        
        if (position == index) break;                   // IF WHOLE ARRAY IS LOOKED BREAK THE LOOP
        
    }
    
    std::cout << "WARNING: The word '" << s << "' couldn't be found in the dictionary" << std::endl;            // KEY IS NOT FOUND
    std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;
    return false;
}

void myHash::insert(std::string s){
    
    ll index = hashFunc(s);
    ll i = 0, position;
    ll collision_before_operation = collision;
    
    while (i < _tableSize) {                        // IN THE WORST CASE WE WILL HAVE TO TRAVERSE WHOLE ARRAY
        position = (index + i) % _tableSize;        // CALCULATE THE POSITION
        
        if (myHashTable[position] != "?" && myHashTable[position] != "*") {         // IF THE POSITION IS FULL
            
            if (myHashTable[position] == s) {                                               // AND OUR KEY EXISTS I THAT POSITION KEY ALREADY WARNING SHOWS
                std::cout << "h(x) result is " << index << " for: " << s << std::endl;
                std::cout << "WARNING: The word '" << s << "' is already in the dictionary!" << std::endl;
                std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;
                return;
            }
            
            i++;                                            // INCREASE I AND COLLISION, I IS INCREASED FOR LINEAR PROBING
            collision++;
        
        } else {                                            // THE POSITION IS EMPTY OR DELETED
            myHashTable[position] = s;                      // PUT THE KEY IN THAT POSITION
            
            if (collision - collision_before_operation != 0) std::cout << "h(x) result is " << index << " for: " << s << std::endl;     // SHOW MESSAGES FOR SUCCESSFUL INSERT OPERATION
            std::cout << "INSERT: The word '" << s << "' is put in the cell number " << position << std::endl;                          // h(x) result IS SHOWN ONLY WHEN THE COLLISION NUMBER FOR THAT
            std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;                                         // INSERT OPERATION IS NOT ZERO
            
            totalEntries++;
            return;
        }
    }
    
    std::cout << "h(x) result is " << index << " for: " << s << std::endl;                                          // WHOLE ARRAY TRAVERSED AND INSERT OPERATION IS UNSUCCESSFUL
    std::cout << "WARNING: There are no empty space in the hash table for the word: " << s << std::endl;            // THEN SHOW NO EMPTY SPACE WARNING MESSAGE
    std::cout << "COLLISIONS :" << collision - collision_before_operation << std::endl;
}


ll myHash::hashFunc(std::string s){                 // HASH FUNCTION
    
    ll hash_value = 1;
    
    for (int a = 0; a < s.length(); a++){
        hash_value *= (s[a] % _tableSize);          // FIRST MULTIPLY THE CURRENT HASH VALUE BY (ASCII(Ch) MOD TABLESIZE)
        hash_value %= _tableSize;                   // THEN TAKE THE MODULO OF HASH VALUE
    }                                               // IT IS DONE TO PREVENT OVERFLOW IN EVERY STEP IT IS GUARENTEED THAT WE HAVE SMALLER VALUE THAN TABLE SIZE
    
    return hash_value;
}

#endif 
