//  Can Yılmaz Altıniğne - 150130132

#ifndef Instructor_h
#define Instructor_h

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Instructor {
    
    string title;                   // Private Members of Instructor Class
    string firstname;
    string lastname;
    string telephoneNumber;
    int roomNumber;
    string username;
    string email;
    char courses[6][10];
    
public:
    
    // Member Functions of Instructor Class
    
    Instructor(const string &, const string &, const string &, const string & = "N/A", const int & = 0, const string & = "N/A", const string & = "N/A", string = "");
    Instructor();
    Instructor(const Instructor &);
    
    void displayInfo() const;
    
    void setFirstname(const string & input){            // SET FUNCTIONS
        firstname = input;
    }
    
    void setLastname(const string & input){
        lastname = input;
    }
    
    void setTitle(const string & input){
        title = input;
    }
    
    void setPhonenumber(const string & input){
        telephoneNumber = input;
    }
    
    void setRoomnumber(const int & input){
        roomNumber = input;
    }
    
    void setUsername(const string & input){
        username = input;
    }
    
    void setEmail(const string & input){
        email = input;
    }
    
    void setCourses(string & arr);
    
    string getTitle() const {               // GET FUNCTIONS
        return title;
    };
    
    string getFirstname() const {
        return firstname;
    };
    
    string getLastname() const {
        return lastname;
    };
    
    string getPhoneNumber() const {
        return telephoneNumber;
    };
    
    int getRoomNumber() const {
        return roomNumber;
    };
    
};

void Instructor::setCourses(string & arr){
    
    char array[60] = "";                    // I take a String and change it to a c type string to use strtok function
    strcpy(array,arr.c_str());
    int i = 0;
    
    char * p;
    p = strtok (array," ");                 // I tokenize this string
    
    while (p != NULL){
        
        strcpy(courses[i++],p);             // The new strings separated by spaces are assigning into courses array.
        p = strtok (NULL, " ");
        
    }
    
    while (i < 6) {
        strcpy(courses[i++]," ");           // I took 6 courses at most. When the assigning stops, this ensures that the rest of array
    }                                       // will be just space.
}

Instructor::Instructor(const string & title1, const string & first, const string & last, const string & phone, const int & room, const string & usr, const string & mail, string arr){
    
    title = title1;
    firstname = first;
    lastname = last;
    telephoneNumber = phone;
    roomNumber = room;
    username = usr;
    email = mail;
    setCourses(arr);
}

Instructor::Instructor(){               // DEFAULT CONSTRUCTOR
  
    title = " ";
    firstname = " ";
    lastname = " ";
    telephoneNumber = " ";
    roomNumber = -1;
    username = " ";
    email = " ";
    
    for (int c = 0; c < 6; c++) {
        strcpy(courses[c], " ");
    }
}

Instructor::Instructor(const Instructor & a){           // COPY CONSTRUCTOR
    title = a.title;
    firstname = a.firstname;
    lastname = a.lastname;
    telephoneNumber = a.telephoneNumber;
    roomNumber = a.roomNumber;
    username = a.username;
    email = a.email;
    
    int order = 0;
    
    while (strcmp(a.courses[order], " ") != 0) {            // While the course[index] is not equal to space assign them to new Instructor object
        strcpy(courses[order],a.courses[order]);
        order++;
    }
    
    while (order < 6) {
        strcpy(courses[order++]," ");           // I took 6 courses at most. When the assigning stops, this ensures that the rest of array
    }
}

void Instructor::displayInfo() const {                  // THIS FUNCTION SHOWS PROPERTIES OF INSTRUCTORS
    
    int a = 0;
    
    cout << endl << "Title: " << title;
    cout << endl << "Firstname: " << firstname;
    cout << endl << "Surname: " << lastname;
    cout << endl << "Telephone Number: " << telephoneNumber;
    cout << endl << "Room Number: " << roomNumber;
    cout << endl << "Username: " << username;
    cout << endl << "Email: " << email;
    cout << endl << "Courses: [";
    
    while (strcmp(courses[a+1]," ") != 0) {         // While the courses[index] is not equal to space, I write them to console.
        cout << courses[a] << ", ";
        a++;
    }
    
    cout << courses[a] << "]" << endl << "-------------------------------------------------";
}

#endif
