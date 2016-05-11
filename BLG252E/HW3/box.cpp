/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#include "box.h"

template <class T>                      // DEFAULT BOX CONSTRUCTOR
Box<T>::Box(double wei,double len, double wid, double max):Base("",wei,len,wid) {
    maximumWeight = max;
    boxWeight = wei;
    size = 0;
    head = NULL;
}

template <class T>                                      // COPY CONSTRUCTOR OF BOX CLASS
Box<T>::Box(Box & other):Base("",other.getWeight(),other.getLength(),other.getWidth()){
    maximumWeight = other.getMaxWeight();
    size = other.getSize();
    head = new T[size];
    boxWeight = other.getBoxWeight();
    
    for (int a=0; a <size; a++) {
        head[a] = other[a];
    }
}

template <class T>                  // BOX DESTRUCTOR
Box<T>::~Box() {
    
    if (size > 1) {             // IF SIZE BIGGER THAN 1 DELETE ARRAY
        delete [] head;
    } else if (size == 1) {     // ELSE THERE IS ONE ELEMENT DELETE IT
        delete head;
    }
    
}

template <class T>              // TO RETURN ADDRESS OF THE HEAD ELEMENT
T* Box<T>::getHead(){
    return head;
}

template <class T>                  // TO RETURN BOX'S OWN WEIGHT WITHOUT OBJECTS IN IT
double Box<T>::getBoxWeight(){
    return boxWeight;
}

template <class T>                  // TO GET TYPE OF BOX
string Box<T>::getType(){
    
    if (head) {
        return "Box<" + head[0].getType() + ">";        // WHAT IS THE TYPE OF HEAD OBJECT
    } else {
        return "NULL";
    }
}

template <class T>                          // ADD FUNCTION
void Box<T>::add(T &added) {
    
    bool big = false;
    
    if (added.getLength() > length || added.getWidth() > width) {           // CHECK ADDED OBJECT SIZE IS SMALLER OR EQUAL THE BOX SIZE
        big = true;                                                         // IF IT IS BIGGER BIG IS TRUE
        
        if (added.getLength() <= width && added.getWidth() <= length) {     // TURN 90 DEGREES IN Z AXIS AND CHECK AGAIN
            big = false;                                                    // IF IT IS SMALLER THE OBJECT IS NOT BIGGER THAN BOX
        }
    }
    
    if (big) {                          // IF OBJECT SIZE IS BIGGER THROW AN ERROR
        const string error = "The dimensions of the contained object should be equal or smaller than those of the box!";
        throw error;
    }
    
    if (added.getWeight() > maximumWeight - getWeight()) {          // OBJECT WEIGHT MUST BE SMALLER THAN MAXIMUM WEIGHT - TOTAL WEIGHT OF BOX
        const string error = "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";
        throw error;
    }
    
    
    if (size == 0) {                // IF THERE IS NO OBJECT IN BOX FOR THE FIRST OBJECT
        
        head = new T;                   // GET A DYNAMIC MEMORY FOR ONE OBJECT
        head[size++] = added;           // HEAD IS THAT OBJECT AND SIZE IS INCREMENTED
        weight += added.getWeight();    // ADD THE TOTAL WEIGHT OF ADDED OBJECT TO BOX'S TOTAL WEIGHT
        
    } else {
        T * ptr = new T[size+1];            // IF THERE IS OBJECT IN BOX
        
        for (int a = 0; a < size; a++) {        // GET A NEW DYNAMIC MEMORY FOR OBJECTS NUMBER OF SIZE+1
            ptr[a] = head[a];                   // COPY THE OLD OBJECTS TO THAT AREA
        }
        
        if (size > 1) {                         // DELETE OLD AREA
            delete [] head;
        } else {
            delete head;
        }
        
        head = ptr;                         // AND ASSIGN THAT AREA TO HEAD
        head[size++] = added;               // THE LAST OBJECT IN THAT DYNAMIC ARRAY WILL BE ADDED OBJECT
        weight += added.getWeight();        // ADD THE TOTAL WEIGHT OF ADDED OBJECT TO BOX'S TOTAL WEIGHT AND INCREMENT SIZE BY 1
        
    }
}

template <class T>                  // ADD FUNCTION WHICH TAKES PARAMETER OF POINTER
void Box<T>::add(T* ptr, int x) {
    
    for (int a = 0; a < x; a++) {       // FOR X TIMES CALL ADD FUNCTION
        add(ptr[a]);
    }
}

template <class T>              // THIS RETURNS SIZE OF BOX (NUMBER OF ITEMS IN IT)
int Box<T>::getSize(){
    return size;
}

template <class T>              // GET THE MAXIMUM VALUE OF A BOX CAN HANDLE
double Box<T>::getMaxWeight(){
    return maximumWeight;
}

template <class T>                                  // OSTREAM OPERATOR OVERLOADING FOR BOX CLASS
ostream& operator<<(ostream& os, Box<T>& box) {
    
    os << "***** " << box.getType() << " *****" << endl;
    os << "Box item count: " << box.getSize() << endl;
    os << "Size: " << box.getLength() << "x" << box.getWidth() << " Box Weight: " << box.getBoxWeight() << "kg" << " Total/Maximum Allowed Weight: " << box.getWeight() << "kg" << "/" << box.getMaxWeight() << "kg" << endl;
    os << "Items:" << endl;
    
    for (int x = 0; x < box.getSize(); x++) {           // FOR ALL OBJECTS IN BOX CALL OSTREAM OPERATOR FOR THAT OBJECT
        os << x+1 << ":"<< box[x];
    }
    
    os << "********************" << endl;
    
    return os;
}

template <class T>                          // [] OPERATOR OVERLOADING
T& Box<T>::operator[](int i){
    
    if (i >= 0 && i < size) {               // IF PARAMETER IS BETWEEN 0 AND SIZE-1 RETURN THAT REFERENCE TO THAT VALUE
        return head[i];
    } else {                                            // ELSE INDEX ERROR
        const string error = "Index out of bounds!";
        throw error;
    }
}


template <class T>                          // ASSIGNMENT OPERATOR OVERLOADING FOR PUTTING BOXES IN A BOX
void Box<T>::operator=(Box<T>&added){           // WE HAVE TO USE THIS WHEN THE ADDED OBJECT IS A BOX IF WE DO NOT WANT TO CAUSE MEMORY LEAK
    
    T * ptr = new T[added.getSize()];               // IF THE ADDED OBJECT IS A BOX CREATE A DYNAMIC MEMORY IN (SIZE OF ADDED BOX)->(TOY NUMBER OR BOOK NUMBER IN BOX)
    
    for (int a = 0; a < added.getSize(); a++) {         // COPY THE ITEMS (BOOKS OR TOYS) IN THAT DYNAMIC MEMORY AREA
        ptr[a] = added[a];
    }
    
    head = ptr;                                 // THIS HEAD IS NOT THE HEAD OF BOX<BOX<TOY>> OR BOX<BOX<BOOK>>, THIS HEAD IS THE BOX'S HEAD WHICH IS IN SIZE POSITION IN THE BOX
    size = added.getSize();                     // IN ADD FUNCTION WE USE   !!! head[size++] = added !!! HEAD[SIZE++] IS A BOX WHEN WE ADD BOXES IN BOX
                                                // WE HAVE TO ASSIGN NEWLY CREATED DYNAMIC MEMORY TO OUR BOX'S HEAD WHICH IS IN A BOX.
                                                // head[size] has type of Box<Toy> or Box<Book> in this situation
    weight = added.getWeight();                 // PROPERTIES OF BOX WHICH WILL BE PUT IN A BOX ARE ASSIGNED TO BOX WHICH WILL BE IN THE BOX
    length = added.getLength();
    width = added.getWidth();
    maximumWeight = added.getMaxWeight();
    boxWeight = added.getBoxWeight();
}