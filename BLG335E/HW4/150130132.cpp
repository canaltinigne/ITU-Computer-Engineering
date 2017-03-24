//  Analysis of Algorithms I - HW 4
//  Can Yılmaz Altıniğne - 150130132

#include <fstream>
#include "150130132.h"

#define COMMAND 0
#define KEY     1

int main(int argc, const char * argv[]) {
    
    std::ifstream words_file;
    char * ptr;                                         // JUST FOR STRTOLL FUNCTION, DOES NOT MEAN ANYTHING
    
    words_file.open(argv[1]);                           // OPEN INPUT FILE
    
    std::ofstream output_file;
    output_file.open("150130132_output.txt");
    
    std::string command;
    std::string command_and_key[2];                     // KEEP COMMAND AND KEY
    
    myHash hash_table(strtoll(argv[2], &ptr, 10));      // INITIALIZE HASH TABLE

    while (words_file >> command) {                                                 // TAKE COMMANDS LIKE 'insert:dummy'
        
        myHash::split_command(command, command_and_key);                            // SPLIT 'insert and dummy' put them into command_and_key array 
        
        if (command_and_key[COMMAND] == "insert") hash_table.insert(command_and_key[KEY]);
            
        else if (command_and_key[COMMAND] == "delete") hash_table.remove(command_and_key[KEY]);
        
        else if (command_and_key[COMMAND] == "retrieve") hash_table.retrieve(command_and_key[KEY], false);
        
        std::cout << "-------------------------------------" << std::endl;
        
    }
    
    std::cout << "TOTAL COLLISIONS: " << hash_table.collision << std::endl;
    std::cout << "Final form of hash table is saved as 150130132_output.txt" << std::endl;
    
    hash_table.print_list(output_file);
    
    words_file.close();
    output_file.close();
    
    return EXIT_SUCCESS;
}
