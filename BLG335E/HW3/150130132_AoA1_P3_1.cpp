//  ANALYSIS OF ALGORITHMS I - HOMEWORK 3   PART A: RADIX SORT
//  CAN YILMAZ ALTINİĞNE - 150130132

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "algos.h"

#define PART_A_FILE "numbers_to_sort.txt"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ifstream file_opened;
    long int order, number;
    Algorithms algos;
    clock_t t = 0;
        
    long int N = atoi(argv[1]);
    file_opened.open(PART_A_FILE);
        
    ofstream sorted_numbers;
    sorted_numbers.open("sorted_numbers.txt");
        
    Number * ptr = new Number[N];
        
    for (long int z = 0; z < N; z++) {              // GET THE UNSORTED NUMBERS FROM FILE
        file_opened >> order >> number;
        ptr[z].set_order(order);
        ptr[z].set_number(number);
    }
        
    t = clock();
        
    algos.radix_sort(ptr, N);                       // RADIX SORT WORKS
        
    t = clock() - t;
        
    cout << "Wow ! It only took " << double(t) / CLOCKS_PER_SEC << " seconds to sort " << N << " numbers with radix sort." << endl << endl;
        
    for (long int z = N-1; z >= 0; z--) {                               // PRINTING SORTED NUMBERS
        sorted_numbers << setw(15) << left << ptr[z].get_order();
            
        int * pt = ptr[z].get_number();
            
        for (int a = 0; a < 10; a++) sorted_numbers << pt[a];
            
        sorted_numbers << endl;
    }
        
    delete [] ptr;
        
    file_opened.close();
    sorted_numbers.close();
    
    return EXIT_SUCCESS;
        
}
