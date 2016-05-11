/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#ifndef toy_h
#define toy_h

#include <iostream>
#include "box.h"

using namespace std;

class Toy: public Base {
    
    bool containsBattery;               // CONTAINS BATTERY FLAG
    
public:
    
    Toy();
    Toy(string lab, double wei, double len, double wid, bool bat);
    string getType() const;                                         // GET THE TYPE WHICH IS "TOY"
    bool getFlag() const;                                           // GET THE CONTAINS BATTERY FLAG
    void setContainsBattery(bool x);                                // TO SET CONTAINS BATTERY FLAG
    friend ostream& operator<<(ostream& os, Toy & toy);             // OSTREAM OPERATOR OVERLOADING FOR TOY CLASS
    ~Toy();
};

#endif