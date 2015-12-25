#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Number {
    char number[10];
    char type[10];
    Number * next;
};

struct Person{
    char name[10];
    Person * next;
    Person * back;
    Number * phonenum = NULL, *tailNum;
};

struct Liste{
    Person * head = NULL;
    void addPerson();   // +
    void addNumber();   // +
    void removePerson();    // +
    void removeNumber();    // +
    void updatePerson();
    void updateNumber();    //+
    void search();          // +
    void list();
    void finish();// +
};

void Liste::addPerson(){
    
    Person * tail;
    Person * traverse = head;
    Person * newNode = new Person;
    newNode->next = NULL;
    newNode->back = NULL;
    newNode->phonenum = NULL;

    cout << endl << "Enter the name: ";
    cin >> newNode->name;

    
    if (head==NULL) {
        
        head = newNode;
        tail = head;
        return;
        
    }
    
    if (strcmp(newNode->name,head->name) < 0) {
        
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        return;
    }
    
    while (traverse && (strcmp(newNode->name,traverse->name) > 0)) {
        tail = traverse;
        traverse = traverse->next;
    }
    
    if (traverse) {
        
        newNode->next = traverse;
        newNode->back = tail;
        tail->next = newNode;
        traverse->back = newNode;
        
    } else {
        
        tail->next = newNode;
        newNode->back = tail;
    }
}

void Liste::addNumber(){
    
    Person * traverse = head;
    Number * headNum;
    Number * eklenecek;
    
    char name[10], number[10];
    char type[10];
    
    cout << endl << "Enter the name: ";
    cin >> name;
    
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (traverse==NULL) {
        
        cout << endl << "Could not be found";
        return;
        
    } else {
        cout << endl << "Enter the number: ";
        cin >> number;
        
        cout << endl << "Enter the number type: ";
        cin >> type;
        
        eklenecek = new Number;
        strcpy(eklenecek->number, number);
        strcpy(eklenecek->type, type);
        eklenecek->next = NULL;
        
        if (traverse->phonenum == NULL) {
            
            traverse->phonenum = eklenecek;
            traverse->tailNum = traverse->phonenum;
            
        } else {
            
            traverse->tailNum->next = eklenecek;
            traverse->tailNum = traverse->tailNum->next;
        }
    }
}

void Liste::removePerson(){
    
    Person * traverse = head;
    
    char name[10];
    
    cout << endl << "Enter the name: ";
    cin >> name;
 
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
    } else {
        
        Number * p = traverse->phonenum;
        Number * silinecek;
        
        while (p) {
            
            silinecek = p;
            p = p->next;
            delete silinecek;
        }
        
        if (traverse == head) {
            head = traverse->next;
            delete traverse;
            return;
        
        }
        
        if (traverse->next == NULL) {
            traverse->back->next = traverse->next;
            delete traverse;
            return;
        }
        
        
        traverse->back->next = traverse->next;
        traverse->next->back = traverse->back;
        delete traverse;
    }
}

void Liste::list(){
    
    Person * traverse = head;
    Number * p;
    
    while (traverse) {
        
        cout << endl << traverse->name;
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << "    " << p->type << " " << p->number;
            p=p->next;
        }
        
        cout << endl;
        
        traverse = traverse->next;
    }
}


void Liste::removeNumber(){
    
    Person * traverse = head;
    int i=0;
    int index;
    Number * silinecek, *p;
    
    char name[10];
    
    cout << endl << "Enter the name: ";
    cin >> name;
    
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (!traverse) {
    
        cout << endl << "Could not be found";
    
    } else {
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << ++i << " " << p->type << "" << p->number;
            p = p->next;
        }
        
        cout << endl;
        
        cout << endl << "Enter the index: ";
        cin >> index;
        
        p = traverse->phonenum;
        
        Number * son;
        
        for (int a = 1; a < index; a++) {
            son = p;
            p = p->next;
        }
        
        silinecek = p;
        
        if (silinecek == traverse->phonenum) {
            traverse->phonenum = silinecek->next;
            delete silinecek;
        } else {
            son->next = silinecek->next;
            delete silinecek;
        }
        
        cout << endl << "Silindi";
    }
}

void Liste::updatePerson(){
    
    Person * traverse = head, *tail;
    int i=0;
    int index;
    Number * silinecek;
    Person * eklenecek = new Person;
    
    char name[10];
    
    cout << endl << "Enter the name: ";
    cin >> name;
    
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (!traverse) {
        
        cout << endl << "Could not be found";
        
    } else {
        
        cout << endl << "It is found";
        
        cout << endl << "Enter the new name: ";
        cin >> eklenecek->name;
        eklenecek->next = NULL;
        
        Person * silinecek = traverse;
        
        if (silinecek != head) {
            silinecek->back->next = silinecek->next;
            silinecek->next->back = silinecek->back;
            delete silinecek;
        } else {
            head = head->next;
            head->back = NULL;
            delete silinecek;
        }
        
        Number * baslangic = traverse->phonenum;
        
        eklenecek->phonenum = baslangic;
        
        traverse = head;
        tail = head;
        
        if (strcmp(eklenecek->name,head->name) < 0) {
            
            eklenecek->next = head;
            head->back = eklenecek;
            head = eklenecek;
            return;
        }
        
        while (traverse && (strcmp(eklenecek->name,traverse->name) > 0)) {
            tail = traverse;
            traverse = traverse->next;
        }
        
        if (traverse) {
            
            eklenecek->next = traverse;
            eklenecek->back = tail;
            tail->next = eklenecek;
            traverse->back = eklenecek;
            
        } else {
            
            tail->next = eklenecek;
            eklenecek->back = tail;
        }
    }
}

void Liste::updateNumber(){
    
    Person * traverse = head;
    Number * p;
    int i=0;
    int index;
    
    char name[10];
    
    cout << endl << "Enter the name: ";
    cin >> name;
    
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (!traverse) {
        
        cout << endl << "Could not be found";
        
    } else {
        
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << ++i << " " << p->type << "" << p->number;
            p = p->next;
        }
        
        cout << endl;
        
        cout << endl << "Enter the index: ";
        cin >> index;
        
        p = traverse->phonenum;
        
        for (int a = 1; a < index; a++) {
            p = p->next;
        }
        
        cout << endl << "Enter the new number: ";
        cin >> p->number;
        
        cout << endl << "Updated";
        
    }
}

void Liste::search(){
    
    char arama[10];
    
    cout << endl << "Enter the name";
    cin >> arama;
    Number * p;
    
    Person * traverse = head;
    
    while (traverse && !(strncmp(traverse->name,arama,strlen(arama)) > 0) ) {
        
        if (strncmp(arama,traverse->name,strlen(arama)) == 0) {
            
            cout << endl << traverse->name;
            p = traverse->phonenum;
            
            while (p) {
                cout << endl << " " << p->type << "" << p->number;
                p=p->next;
            }
            
            cout << endl;
            
        }
        
        traverse = traverse->next;
    }
}

void Liste::finish(){

    Person * traverse = head, * perSil;
    Number * p, *silinecek;
    
    while (traverse) {
        
        perSil = traverse;
        p = traverse->phonenum;
        traverse = traverse->next;
        
        while (p) {
            
            silinecek = p;
            p = p->next;
            delete silinecek;
        }
        
        delete perSil;
        
    }
    
    cout << endl << "Tum kayitlar silindi - Programdan cikiliyor...";
}

typedef Liste Phonebook;
Phonebook linkedList;
void menuYazdir();

int main(){
    
    char secim;
    int index;

    while (1) {
        
        menuYazdir();
        cin >> secim;
        
        switch (secim) {
            case 'A': case 'a':
                linkedList.addPerson();
                break;
            
            case 'N': case 'n':
                linkedList.addNumber();
                break;
            
            case 'R': case 'r':
                linkedList.removePerson();
                break;
            
            case 'V': case 'v':
                linkedList.removeNumber();
                break;
                
            case 'U': case 'u':
                linkedList.updatePerson();
                break;
            
            case 'P': case 'p':
                linkedList.updateNumber();
                break;
            
            case 'S': case 's':
                linkedList.search();
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
    cout << "A: Add Person" << endl;
    cout << "N: Add Number" << endl;
    cout << "R: Remove Person" << endl;
    cout << "V: Remove Number" << endl;
    cout << "U: Update Person" << endl;
    cout << "P: Update Number" << endl;
    cout << "S: Search" << endl;
    cout << "L: List" << endl;
    cout << "E: Exit" << endl;
    cout << endl << "Enter your option: ";
}