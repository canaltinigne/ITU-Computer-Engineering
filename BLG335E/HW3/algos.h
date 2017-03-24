//  ANALYSIS OF ALGORITHMS I - HOMEWORK 3
//  CAN YILMAZ ALTINİĞNE - 150130132

#ifndef algos_h
#define algos_h

// HEAP SORT AND RADIX SORT

#include "player.h"
#include "number.h"

class Algorithms {
    
    Number * output_list;
    
    void counting_sort(Number * number_list, long int list_size, int which_digit){                  // COUNTING SORT
        
        int count_array[10] = {0};                                                                  // K = 10
        
        for (long int a = 0; a < list_size; a++) count_array[number_list[a].get_number_at_index(which_digit)]++;    // FIND THE C VECTOR
        
        for (int a = 1; a < 10; a++) count_array[a] += count_array[a-1];                                            // FIND THE C' VECTOR
        
        for (long int a = list_size-1; a >= 0; a--) {                                                               //  PLACING THE NUMBERS TO THE CORRECT PLACES
            output_list[count_array[number_list[a].get_number_at_index(which_digit)]-1] = number_list[a];
            count_array[number_list[a].get_number_at_index(which_digit)]--;
        }
        
        for (long int b = 0; b < list_size; b++) number_list[b] = output_list[b];                                   // NEW ORDER IS ASSIGNED TO ORIGINAL NUMBER LIST FILE
        
    }
    
    void max_heapify(Player * player_list, long int pos, long int heap_size){                                       // MAX HEAPIFY FOR HEAP SORT
        
        long int left_child = 2*(pos+1)-1;                                          // IF INDEXING STARTS FROM 1 LEFT CHILD=2K RIGHT CHILD = 2K+1
        long int right_child = 2*(pos+1);
        
        long int largest = pos;
        
        (left_child < heap_size && player_list[left_child] > player_list[pos]) ? largest = left_child : largest = pos;      // FIND THE NEW POSITION OF THE NODE
        
        if (right_child < heap_size && player_list[right_child] > player_list[largest]) largest = right_child;
        
        if (largest != pos){                            // IF THE NEW PLACE IS DIFFERENT FROM THE ORIGINAL PLACE
            Player temp = player_list[pos];             // SWAP THE NUMBER WITH NEW PLACE AND CALL MAX_HEAPIFY AGAIN
            player_list[pos] = player_list[largest];
            player_list[largest] = temp;
            
            max_heapify(player_list, largest, heap_size);
        }
    }
    
    void build_max_heap(Player* p_list, long int arr_size){         // FOR INNER NODES CALL MAX_HEAPIFY FUNCTION
   
        for (long int a = (arr_size/2 - 1); a >= 0; a--) max_heapify(p_list, a, arr_size);
    }
    
public:
    
    void radix_sort(Number * player_list, long int size){
        
        output_list = new Number[size];             // OUTPUT ARRAY IS SET
        
        for (int b = 9; b>=0; b--) counting_sort(player_list, size, b);     // CALL COUNTING SORT FOR EVERY DIGIT IN THE NUMBER FROM RIGHT TO LEFT
        
        delete [] output_list;                      // DELETE THE DYNAMIC OUTPUT ARRAY
    }
    
    void heap_sort(Player * player_list, long int size){
        build_max_heap(player_list, size);                      // BUILD THE MAX HEAP FIRST
        
        for (long int b = size-1; b > 0; b--) {                 // FOR EVERY PLAYER IN HEAP
            Player temp = player_list[0];                       // FIRST SWAP THE LAST ONE AND THE FIRST ONE THAN DECREMENT THE SIZE AND CALL MAX_HEAPIFY
            player_list[0] = player_list[b];
            player_list[b] = temp;
            
            max_heapify(player_list, 0, --size);
        }
    }
    
};

int find_level(long int x){             // FIND THE LEVEL OF NODE IN HEAP
    
    int level = 0;
    
    if (x == 0) return level;       // 0 IS THE LEVEL OF ROOT
    
    x++;                        // ACT LIKE INDEXING STARTS FROM 1, LEFT CHILD IS 2K AND RIGHT CHILD IS 2K+1
    
    while (x != 1) {
        if (x % 2 == 0) {
            x /= 2;
        } else {
            x--;
            x /= 2;
        }
        
        level++;
    }
    
    return level;
}

#endif
