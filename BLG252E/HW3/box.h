/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#ifndef box_h
#define box_h
#include <string>
#include <iostream>

using namespace std;

// ------------------------------------------------------------------------------------------

class Base {                            // BASE CLASS FOR TOY, BOX, BOOK
    
protected:
    string label;                           // COMMON VARIABLES FOR ALL 3 CLASSES
    double weight, length, width;
    
public:
    Base(string lab, double wei, double len, double wid){       // BASE CLASS CONSTRUCTOR
        label = lab;
        weight = wei;
        length = len;
        width = wid;
    }
    
    double getWeight() const{               // COMMON FUNCTIONS FOR ALL 3 CLASSES
        return weight;                      // RETURN WEIGHT, WIDTH, LENGTH, LABEL OF THAT OBJECT
    }                                       // FOR BOXES GET WEIGHT FUNCTION RETURNS WEIGHT OF BOX AND ALL THE OBJECTS IN IT (TOTAL WEIGHT)
    
    double getWidth() const{
        return width;
    }
    
    double getLength() const{
        return length;
    }
    
    string getLabel() const{
        return label;
    }
    
};

// ------------------------------------------------------------------------------------------

template <class T>
class Box: public Base {            // BOX CLASS
    
    double maximumWeight;           // MAXIMUM WEIGHT THAT A BOX HANDLES
    double boxWeight;               // BOX WEIGHT WITHOUT OBJECTS IN IT
    int size;                       // TOY, BOOK OR BOX NUMBER IN THAT BOX
    T * head;                       // TO KEEP TOYS, BOOKS OR BOXES DYNAMICALLY
    
public:
    
    Box(double=0,double=0,double=0,double=0);       // BOX CLASS CONSTRUCTORS
    Box(Box &);
    
    void operator=(Box<T>&);                        // THIS IS IMPORTANT BECAUSE FOR ADDING BOXES IN BOX WE NEED TO OVERLOAD ASSIGNMENT OPERATOR
    
    int getSize();                                  // GETTING SIZE OF BOX
    double getBoxWeight();                          // GETTING BOX'S OWN WEIGHT WITHOUT OBJECTS IN IT
    string getType();                               // GETTING TYPE OF BOX
    
    template <class J>                              // FRIEND FUNCTION FOR OVERLOADING OSTREAM OPERATOR
    friend ostream& operator<<(ostream&, Box &);

    double getMaxWeight();                          // GETTING MAXIMUM WEIGHT A BOX HANDLES
    
    void add(T&);                                   // ADD FUNCTIONS
    void add(T*,int);
    
    T& operator[](int);                             // OVERLOADING [] OPERATOR
    T* getHead();                                   // GETTING ADDRESS OF HEAD OF THE BOX
    
    ~Box();                                         // BOX DESTRUCTOR
};

#endif