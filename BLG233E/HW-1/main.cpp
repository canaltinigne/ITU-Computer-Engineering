/*
 * @Author
 * Student Name: Can Yılmaz Altıniğne
 * Student ID : 150130132
 * Date: 08/10/2015
 */

#include "operations.h"

struct File library;

using namespace std;

void showMenu();            // Menu function prototype

int main(){
    
    char secim;
                   // Creating File variable with the name of "library"
    library.create();   // create() function in struct is called to create a text file to write books to it
    
    while(1){
        
        showMenu();
        cin >> secim;
        
        switch (secim) {
                
            case 'P': case'p' :
                // PRINT THE CATALOGUE
                library.printCatalogue();
                break;
                
            case 'A': case'a' :
                // SEARCH BY AUTHOR
                library.searchBookAuthor();
                break;
                
            case 'T': case't' :
                // SEARCH BY TYPE
                library.searchBookType();
                break;
                
            case 'I': case'i' :
                // INSERT
                cin.ignore(1000,'\n');
                library.addBook();
                break;
                
            case 'U': case'u' :
                // UPDATE
                cout << endl << "ALL BOOKS IN THE CATALOGUE" << endl;
                library.printCatalogue();
                library.updateBook();
                break;
                
            case 'R': case'r' :
                // REMOVE
                cout << endl << "ALL BOOKS IN THE CATALOGUE" << endl;
                library.printCatalogue();
                library.deleteBook();
                break;
                
            case 'E': case'e' :
                // EXIT
                cout << endl << "Thank you for using the program." << endl;
                library.close();
                exit(0);
                break;
                
            default:
                cout << endl << "Please enter a valid choice." << endl;
                break;
        }
    }
    
    return 0;
}

void showMenu(){                            // Showing menu function
   
    cout << endl << "Please select the operation to perform and enter the operation code" << endl;
    cout << "(P) Print the whole catalogue," << endl;
    cout << "(A) Search the catalogue by author," << endl;
    cout << "(T) Search the catalogue by book type," << endl;
    cout << "(I) Insert a new book record," << endl;
    cout << "(U) Update an existing book record," << endl;
    cout << "(R) Remove a book record," << endl;
    cout << "(E) Exit the program." << endl;
    cout << "Your Selection is: ";
}

