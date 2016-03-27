//  Can Yılmaz Altıniğne - 150130132

#include "Instructor.h"
#include "InstructorList.h"

class AddressBook {
    
    InstructorList list;        // List variable
    Instructor * a;             // For first 3 Instructors
    Instructor * b;
    Instructor * c;
    Instructor * d;
    
public:
    
    AddressBook();
    ~AddressBook();
    void startInterface();
    void search(int &);
    void listAll();
    void add();
    void deleteIns();

};

AddressBook::~AddressBook(){
    
    delete a;
    delete b;
    delete c;
    delete d;
}

AddressBook::AddressBook(){
    
    // Initialize first 3 instructors
    
    a = new Instructor("Asst. Prof. Dr.", "Hatice", "Köse", "90 212 2853593", 3315, "hbkose", "hatice.kose@itu.edu.tr", "BLG252E BLG233E");
    b = new Instructor("Doç. Dr.", "Gözde", "Ünal", "90 212 2853852", 5111, "unalgo", "unalgo@itu.edu.tr", "BLG202E BLG354E");
    c = new Instructor("Asst. Prof. Dr.", "Gökhan", "İnce", "90 212 2856986", 4310, "incegokh", "gokhan.ince@itu.edu.tr", "BLG222E BLG242E BLG442E");
    d = new Instructor("Prof. Dr.", "Eşref", "Adalı", "90 212 2853586", 4322, "adali", "adali@itu.edu.tr", "BLG212E");
    
    list.addInstructor(*a);                                     // Add them into list
    list.addInstructor(*b);
    list.addInstructor(*c);
    list.addInstructor(*d);
}

void AddressBook::search(int &a){               // Search function calls InstructorList search function with values 4,5,6,7
    list.searchInstructor(a);
}

void AddressBook::listAll(){                    // Listing all instructors
    list.listInstructor();
}

void AddressBook::add(){                    // Add instructor function
    list.addInstructor();
}

void AddressBook::deleteIns(){              // Delete instructor function
    list.deleteInstructor();
}

void AddressBook::startInterface(){         // For interface
    
    int i;
    char control = 'Y';
    
    while (control == 'Y' || control == 'y') {
        cout << endl << "1. Add a new instructor";
        cout << endl << "2. Delete an instructor";
        cout << endl << "3. List all instructors";
        cout << endl << "4. Search by Name";
        cout << endl << "5. Search by Surname";
        cout << endl << "6. Search by Telephone Number";
        cout << endl << "7. Search by Room Number";
        cout << endl << "8. Exit";
        cout << endl << "Enter the number for operation you want to perform: ";
        cin >> i;
        
        switch (i) {
            case 1:
                add();          // Add
                break;
                
            case 2:
                deleteIns();        // Delete
                break;
                
            case 3:
                listAll();          // List
                break;
                
            case 4:
                search(i);          // Search by name
                break;
                
            case 5:
                search(i);          // Search by surname
                break;
                
            case 6:
                search(i);          // Search by telephone number
                break;
                
            case 7:
                search(i);          // Search by room number
                break;
                
            case 8:
                cout << endl << "Exiting ........" << endl;
                return;
                break;
                
            default:
                cout << endl << "Please enter appropriate input !";
                break;
        }
        
        cout << endl << "Do you want to perform another operation?(Y/N): ";
        cin >> control;
        
        while (control != 'Y' && control != 'y' && control != 'N' && control != 'n' ) {
            cout << endl << "Please enter Y or N: ";
            cin >> control;
        }
    }
    
    cout << endl << "Exiting ........" << endl;
    return;
}

int main() {
    
    AddressBook address;
    address.startInterface();
    return 0;
}
