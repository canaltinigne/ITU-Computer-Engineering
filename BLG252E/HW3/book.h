/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#ifndef book_h
#define book_h

#include "box.h"

//  BOOK CLASS

class Book: public Base {
    
public:
    Book();
    Book(string lab, double wei, double len, double wid);
    string getType() const;                                     // GET THE TYPE WHICH IS "BOOK"
    friend ostream& operator<<(ostream&, Book&);                // OSTREAM OPERATOR OVERLOADING FOR BOOK CLASS
    ~Book();
};

#endif