//  ANALYSIS OF ALGORITHMS I - HOMEWORK 3
//  CAN YILMAZ ALTINİĞNE - 150130132

//  NUMBER CLASS FOR RADIX SORT

#ifndef number_h
#define number_h

class Number {
    long int order;
    int digits[10];
    
public:
    void set_order(long int order){
        this->order = order;
    }
    
    long int get_order(){
        return order;
    }
    
    void set_number(long int number){           // NUMBERS ARE KEPT AS THEY ARE SEPERATED TO 10 DIGITS FOR COUNTING SORT
        int x = 9;
        
        while (number) {
            digits[x--] = number % 10;
            number /= 10;
        }
    }
    
    int * get_number(){
        return digits;
    }
    
    int get_number_at_index(int a){
        return digits[a];
    }
};

#endif
