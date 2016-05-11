/*
 * @Author
 * Student Name: Can Yılmaz ALtıniğne
 * Student ID : 150130132
 * Date: 07 / 05 / 2016
 */

#include "toy.h"

Toy::Toy(): Base("",0,0,0){             // CONSTRUCTORS FOR TOY CLASS
    containsBattery = false;
}

Toy::Toy(string lab, double wei, double len, double wid, bool bat): Base(lab,wei,len,wid){
    containsBattery = bat;
}

bool Toy::getFlag() const {             // GET THE CONTAINS BATTERY FLAG
    return containsBattery;
}

string Toy::getType() const {           // GET THE TYPE WHICH IS "TOY"
    return "Toy";
}

void Toy::setContainsBattery(bool x){       // TO SET THE CONTAINS BATTERY FLAG
    containsBattery = x;
}

ostream& operator<<(ostream& os, Toy & toy) {               // OSTREAM OPERATOR OVERLOADING FOR TOY CLASS
    
    os << "Toy Label: " << toy.getLabel() << " # " << toy.getLength() << "x" << toy.getWidth() << " " << toy.getWeight() << "kg";
    
    if (toy.getFlag()) {                        // WITH RESPECT TO CONTAINS BATTERY FLAG
        os << " Contains Battery" << endl;
    } else {
        os << " No Battery" << endl;
    }
    
    return os;
}

Toy::~Toy(){}