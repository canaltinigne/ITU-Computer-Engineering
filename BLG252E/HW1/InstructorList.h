//  Can Yılmaz Altıniğne - 150130132

#ifndef InstructorList_h
#define InstructorList_h                // I use cin.ignore and getline function to take inputs with spaces in it.

class InstructorList {
    
    Instructor * insList;
    int size;
    int current;
    
public:
    
    InstructorList(const int & length){         // Constructor creates an Instructor array with size depending on input value
        size = length;
        current = 0;
        insList = new Instructor[size];
    }
    
    InstructorList(){                           // Default contructor creates an Instructor array with size of 4
        size = 4;
        current = 0;
        insList = new Instructor[4];
    }
    
    ~InstructorList(){
        delete [] insList;
    }
    
    void addInstructor();
    void addInstructor(const Instructor &);
    void searchInstructor(const int&) const;
    void deleteInstructor();
    void listInstructor() const;
};

void InstructorList::deleteInstructor(){            // Delete Instructor Function
    
    string buf1, buf2;
    bool deleted = false;
    int a;
    Instructor * ptr;
    
    cout << endl << "Enter the first name of the record to be deleted: ";
    cin.ignore();
    getline(cin, buf1);
    
    cout << endl << "Enter the last name of the record to be deleted: ";
    cin >> buf2;
    
    for (a = 0; a < current; a++) {                     // Check if there is a match
        if (insList[a].getFirstname() == buf1) {
            if (insList[a].getLastname() == buf2) {
                deleted = true;                         // deleted = true if there is a match
                break;
            }
        }
    }
    
    if(deleted == false){                               // If there is no match print not found message
        cout << endl << "Record not found." << endl;
        
    } else {                                            // Else create a new Instructor array with current size
        
        ptr = new Instructor[size];
        
        int c = 0;
        
        for (int b = 0; b < current; b++) {                // Copy the old array without data that will be deleted
            if (b != a) {                               // a value holds the position of data value that will be deleted.
                ptr[c] = insList[b];
                c++;
            }
        }
        
        delete [] insList;                              // Delete old array
        
        insList = ptr;                                  // Assign new array to ptr value which olds the instructor list.
        
        current--;                                  // Decrease current position value by 1 because we are deleting an Instructor
        
        listInstructor();
        
        cout << endl << "Record has been deleted!" << endl;
    
    }
}

void InstructorList::searchInstructor(const int &a) const{       // Search Instructor Function
    
    string buffer;
    int x;
    bool found = false;
    
    if (a == 4) {                                       // If a is 4 Search by name
        cout << endl << "Enter the first name: ";
        cin.ignore();
        getline(cin, buffer);
        
        cout << endl << "------ Search Results ------" << endl;
        
        for (int b = 0; b < current; b++) {                 // If there is a match
            if (insList[b].getFirstname() == buffer) {
                insList[b].displayInfo();
                found = true;                               // Found is true
            }
        }
        
    } else if (a == 5){                                 // If a is 5 Search by surname
        cout << endl << "Enter the last name: ";
        cin >> buffer;
        
        cout << endl << "------ Search Results ------" << endl;
        
        for (int b = 0; b < current; b++) {             // If there is a match
            if (insList[b].getLastname() == buffer) {
                insList[b].displayInfo();
                found = true;                               // Found is true
            }
        }
        
    } else if (a == 6){                                 // If a is 6 Search by phone number
        cout << endl << "Enter the telephone number: ";
        cin.ignore();
        getline(cin, buffer);
        
        cout << endl << "------ Search Results ------" << endl;
        
        for (int b = 0; b < current; b++) {                 // If there is a match
            if (insList[b].getPhoneNumber() == buffer) {
                insList[b].displayInfo();
                found = true;                           // Found is true
            }
        }
        
    } else if (a == 7){                                     // If a is 7 Search by room number
        cout << endl << "Enter the room number: ";
        cin >> x;
        
        cout << endl << "------ Search Results ------" << endl;
        
        for (int b = 0; b < current; b++) {                 // If there is a match
            if (insList[b].getRoomNumber() == x) {
                insList[b].displayInfo();
                found = true;                               // Found is true
            }
        }
    }
    
    if (found == false) {                                   // If found is false print error message
        cout << endl << "No record found." << endl;
    }
}

void InstructorList::listInstructor() const{                // Listing Instructors Function
    int a = 0;
    
    cout << endl << "----------List of all Instructors in Computer Engineering of ITU----------" << endl;
    
    while (a < current) {                       // List them until current value
        insList[a].displayInfo();
        a++;
    }
}

void InstructorList::addInstructor(const Instructor & buffer){          // Add Instructors Function
    
    if (current == size) {              // Check if current value is equal to size
        Instructor * ptr;               // We need to bigger size of array
        
        ptr = new Instructor[size*2];           // Create new array with two times of old size value
        
        for (int b = 0; b < current; b++) {     // Until current value copy the datas to new array.
            ptr[b] = insList[b];
        }
        
        delete [] insList;              // Delete old array
        
        insList = ptr;                      // Assign new value to array pointer
        size *= 2;                              // Double the size
    }
    
    insList[current++] = buffer;                // Add the new data to Instructor array
}

void InstructorList::addInstructor(){           // Add Instructor Function
    
    string arr[3];
    string buffer;
    int room;
    
    if (current == size) {                      // Check if the size is sufficient or not like the function above
        Instructor * ptr;
        
        ptr = new Instructor[size*2];
        
        for (int b = 0; b < current; b++) {
            ptr[b] = insList[b];
        }
        
        delete [] insList;
        
        insList = ptr;
        size *= 2;
    }
    
    cin.ignore();
    cout << endl << "Enter the title: ";                // Enter the title
    getline(cin,arr[0]);
    
    cout << endl << "Enter the First Name: ";           // Enter the first name
    getline(cin,arr[1]);
    
    cout << endl << "Enter the Last Name: ";            // Enter the last name
    getline(cin,arr[2]);
    
    for (int a = 0; a < current; a++) {                     // Check if there is a duplication
        if (insList[a].getTitle() == arr[0]) {
            if (insList[a].getFirstname() == arr[1]) {
                if (insList[a].getLastname() == arr[2]) {
                    cout << endl << "Error: There is a duplication, you cannot add same person" << endl;
                    return;
                }
            }
        }
    }
    
    insList[current].setTitle(arr[0]);                  // If there is not duplication copy the data to current place of array
    insList[current].setFirstname(arr[1]);
    insList[current].setLastname(arr[2]);
    
    cout << endl << "Enter the Telephone Number: ";         // Enter the phone number
    cin.ignore();
    getline(cin, buffer);
    insList[current].setPhonenumber(buffer);
    
    cout << endl << "Enter the Room Number: ";              // Enter the room number
    cin >> room;
    insList[current].setRoomnumber(room);
    
    cout << endl << "Enter the User Name: ";                // Enter the username
    cin >> buffer;
    insList[current].setUsername(buffer);
    
    cout << endl << "Enter the E-Mail: ";                   // Enter the email
    cin >> buffer;
    insList[current].setEmail(buffer);
    
    cout << endl << "Enter the Courses (with spaces such as BLG222E BLG354E BLG212E): ";        // Enter the courses with spaces for example
    cin.ignore();                                               // BLG322E BLG231E BLG476E
    getline(cin,buffer);
    insList[current].setCourses(buffer);
    
    current++;                                              // Increment current value by 1
    
    cout << endl << "New instructor is added!" << endl;
}

#endif 
