// BLG 252E - Homework 2
// Can Yılmaz Altıniğne - 150130132

#ifndef hetlist_h
#define hetlist_h

// Heterogeneous List Class

class HetList {
    
    Base * head;
    
public:
    
    HetList();
    ~HetList();
    
    void insert(Base *);
    void traverser(Base *);
    Base * getHead() const;
    void print(int *);
};

// Heterogeneous List Member Functions

HetList::HetList(){                 // Constructor firstly head = NULL
    head = NULL;
}

HetList::~HetList(){                // Destructor for HetList
    Base * ptr;                     // Delete all members of list before terminating program
    
    ptr = head;
    
    while (ptr) {
        head = head->next;
        delete ptr;
        ptr = head;
    }
}

Base * HetList::getHead() const {      // To get Head of the List
    return head;
}

void HetList::insert(Base * ptr){       // Insert function: insert cards to head new member is the new head value
                                        // Like Stack Data Structure
    if (!head) {                        // First element to add
        head = ptr;
    } else {                            // If there is an element in list add new to head.
        ptr->next = head;
        head = ptr;
    }
}

void HetList::traverser(Base * ptr){    // Traverse function to comparing one list with another list
                                        // Take other list's head as parameter
    Base * traverse = head;
    
    while (traverse) {
        traverse->compare(ptr);         // Call Compare function for one list, compare function handle's
        traverse = traverse->next;      // two elements one for list 1 one for list 2
        ptr = ptr->next;
    }
}

void HetList::print(int * resArray){        // print function is used by displayResults
    
    Base * traverse = head;
                                                    // Take an array of 3 integers (Win=0 Lose=0 Tie=0)
    while (traverse) {
        cout << traverse->getResult() << " ";       // Print result for all list member
        
        if (traverse->getResult() == Win) {             // With respect to result increment array member
            resArray[Win]++;
        } else if (traverse->getResult() == Tie){
            resArray[Tie]++;
        } else {
            resArray[Lose]++;
        }
        
        traverse = traverse->next;
    }
}

#endif