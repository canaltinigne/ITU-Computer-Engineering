#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node{
    char * name;
    char * surname;
    char number[10];
    Node * next;
};

struct Liste{
    Node * head;
    void create();
    void add();
    void list();
    void remove(int);
    void update(int);
    Node * search();
    void finish();
};

Node * Liste::search(){
    
    char arama[15];
    
    cout << endl << "Enter your search";
    cin >> arama;
    
    Node * traverse = head;
    Node * searchHead = NULL;
    Node * headSearchList = NULL;
    Node * newNode = NULL;
    
    while (traverse && !(strncmp(traverse->name,arama,strlen(arama)) > 0) ) {
        
        if (strncmp(arama,traverse->name,strlen(arama)) == 0) {
            
            if (!searchHead) {
                
                newNode = new Node;
                newNode->name = new char[strlen(traverse->name)+1];
                strcpy(newNode->name,traverse->name);
                newNode->surname = new char[strlen(traverse->surname)+1];
                strcpy(newNode->surname,traverse->surname);
                strcpy(newNode->number,traverse->number);
                newNode->next = NULL;
                searchHead = newNode;
                headSearchList = searchHead;
            
            } else {
                
                newNode = new Node;
                newNode->name = new char[strlen(traverse->name)+1];
                strcpy(newNode->name,traverse->name);
                newNode->surname = new char[strlen(traverse->surname)+1];
                strcpy(newNode->surname,traverse->surname);
                strcpy(newNode->number,traverse->number);
                newNode->next = NULL;
                headSearchList->next = newNode;
                headSearchList = newNode;
            }
        }
        
        traverse = traverse->next;
    }
    
    return searchHead;
}

void Liste::list(){
    
    Node * traverse = head;
    
    int i = 0;
    
    if (traverse==NULL) {
        
        cout << endl << "There are no records" << endl;
        
    } else {
        
        while (traverse) {
            
            cout << endl << ++i << ". " << traverse->name << " " << traverse->surname << " " << traverse->number;
            
            traverse = traverse->next;
            
        }
    }
}

void Liste::update(int index){
    
    Node * traverse = head;
    int counter = 0;
    
    while (traverse) {
        traverse = traverse->next;
        counter++;
    }
    
    if (index > counter) {
       
        cout << endl << "Invalid choice";
    
    } else {
        
        remove(index);
        add();
        
    }
}


void Liste::remove(int index){

    Node * traverse, * tail;
    
    int counter = 1;
    
    traverse = head;
    
    if (head == NULL) {
        
        cout << endl << "There are no records";
    
    } else {
        
        if (index <= 0) {
         
            cout << endl << "Invalid entry";
            return;
        }
        
        if (index == 1) {
            head = head->next;
            delete [] traverse->name;
            delete [] traverse->surname;
            delete traverse;
            return;
        }
        
        while ((traverse != NULL) && (counter < index)) {
            tail = traverse;
            traverse = traverse->next;
            counter++;
        }
        
        if (counter < index){
            
            cout << endl << "Could not find the record";
            
        } else {
            
            tail->next = traverse->next;
            delete [] traverse->name;
            delete [] traverse->surname;
            delete traverse;
        }
    }
}

void Liste::finish(){

    Node * silinecek;
    
    while (head) {
        
        silinecek = head;
        delete [] silinecek->name;
        delete [] silinecek->surname;
        head = head->next;
        delete silinecek;
    }
    
    cout << endl << "Tum kayitlar silindi - Programdan cikiliyor...";
}



void Liste::add(){
    
    Node * traverse, *tail;
    traverse = head;
    Node * newNode = new Node;
    newNode->next = NULL;
    
    char tutucu[30];
    
    cout << endl << "Enter the name: ";
    cin >> tutucu;
    newNode->name = new char[strlen(tutucu)+1];
    strcpy(newNode->name,tutucu);
    
    cout << endl << "Enter the surname: ";
    cin >> tutucu;
    newNode->surname = new char[strlen(tutucu)+1];
    strcpy(newNode->surname,tutucu);
    
    cout << endl << "Enter the number: ";
    cin >> newNode->number;
    
    if (head==NULL) {
        
        head = newNode;
        return;
    
    }
    
    if (strcmp(newNode->name,head->name) < 0) {
        
        newNode->next = head;
        head = newNode;
        return;
    }
    
    while (traverse && (strcmp(newNode->name,traverse->name) > 0)) {
        tail = traverse;
        traverse = traverse->next;
    }
    
    if (traverse) {
        
        newNode->next = traverse;
        tail->next = newNode;
    
    } else {
        
        tail->next = newNode;
    }
}

void Liste::create(){
   
    head= NULL;
}


typedef Liste Phonebook;

Phonebook linkedList;

void menuYazdir();
void callingFunc(Node *);

Node * searchList = NULL;

int main(){
    
    linkedList.create();
    char secim;
    int index;

    while (1) {
        
        menuYazdir();
        cin >> secim;
        
        switch (secim) {
            case 'A': case 'a':
                linkedList.add();
                break;
            
            case 'R': case 'r':
                linkedList.list();
                cout << endl << "Enter the index of the record you want to remove: ";
                cin >> index;
                linkedList.remove(index);
                break;
            
            case 'U': case 'u':
                linkedList.list();
                cout << endl << "Enter the index of the record you want to update: ";
                cin >> index;
                linkedList.update(index);
                break;
            
            case 'S': case 's':
                searchList = linkedList.search();
                break;
                
            case 'C': case 'c':
                callingFunc(searchList);
                break;
            
            case 'L': case 'l':
                linkedList.list();
                break;
            
            case 'E': case 'e':
                linkedList.finish();
                exit(EXIT_SUCCESS);
                break;
            
            default:
                cout << endl << "Invalid choice";
                break;
        }
    }
    
    return 0;
}

void menuYazdir(){
    
    cout << endl << endl << "Phone Book" << endl;
    cout << "A: Add Record" << endl;
    cout << "R: Remove Record" << endl;
    cout << "U: Update Record" << endl;
    cout << "S: Search Record" << endl;
    cout << "C: Calling Search Records" << endl;
    cout << "L: List Record" << endl;
    cout << "E: Exit" << endl;
    cout << endl << "Enter your option: ";
}

void callingFunc(Node * arg){
    
    Node * traverse = arg;
    
    int i = 0;
    
    if (traverse==NULL) {
        
        cout << endl << "There are no findings";
        
    } else {
        
        while (traverse) {
            
            cout << endl << ++i << ". " << traverse->name << " " << traverse->surname << " " << traverse->number;
            
            traverse = traverse->next;
            
        }
    }
    
    while (arg) {
        
        traverse = arg;
        delete [] traverse->name;
        delete [] traverse->surname;
        arg = arg->next;
        delete traverse;
    }
    
    searchList = NULL;
}
