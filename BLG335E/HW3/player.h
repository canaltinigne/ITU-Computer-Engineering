//  ANALYSIS OF ALGORITHMS I - HOMEWORK 3
//  CAN YILMAZ ALTINİĞNE - 150130132

//  PLAYER CLASS FOR HEAP SORT

#ifndef player_h
#define player_h

class Player {
    long int player_id;
    long int charisma_point;
    
public:
    void set_id(long int id){
        this->player_id = id;
    }
    
    long int get_id(){
        return player_id;
    }
    
    void set_charisma_point(long int cp){
        charisma_point = cp;
    }
    
    long int get_charisma_point(){
        return charisma_point;
    }
    
    bool operator > (Player& x){                            // FOR HEAP SORT
        return charisma_point > x.get_charisma_point();
    }
    
    void decrease_cp(long int x){                              
        charisma_point -= x;
        
        if (charisma_point <= 0) charisma_point = 0;
    }
    
    void increase_cp(long int x){
        charisma_point += x;
    }
    
};

#endif
