/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#include "book.h"

Book::Book(): Base("",0,0,0){}                          // BOOK CLASS CONSTRUCTORS

Book::Book(string lab, double wei, double len, double wid): Base(lab,wei,len,wid){}

string Book::getType() const {                  // BOOK GET TYPE FUNCTION
    return "Book";
}

ostream& operator<<(ostream& os, Book& book) {              // OSTREAM OPERATOR OVERLOADING FOR BOOK CLASS 
    
    os << "Book Label: " << book.getLabel() << " # " << book.getLength() << "x" << book.getWidth() << " " << book.getWeight() << "kg" << endl;
    
    return os;
}

Book::~Book(){}