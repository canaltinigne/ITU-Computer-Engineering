/*
 * @Author
 * Student Name: Can Yılmaz Altıniğne * Student ID : 150130132
 * Date: 07 / 11 / 2015
 */

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Transaction {                    // Transaction struct
    char tranName[15];
    Transaction * next;
};

struct Customer {                   //  Customer Struct
    char name[15];
    char surname[15];
    char customerType;
    int transactionNumber;
    Customer * next;
    Transaction * headTransaction;
};

struct List {                                       // Main List struct
    Customer * head, *headPremium, *headNormal;     // This struct holds functions, input-output files and head-tail pointer of normal list
    Customer * tailPremium, *tailNormal;            // premium list and head of the main list.
    FILE * giris;
    ofstream outputFile;
    void addCustomer(char *);
    void searchCustomer(char *);
    void removeCustomer(char *);
    void printCustomer();
    void processTran();
    void create();
    void destruct();
};

void List::processTran(){                   // TRANSACTION PROCESSING FUNCTION
    
    Customer * p;
    Transaction * first, *q;
    
    if (head==NULL) {                                               // When there is no one in the list
    
        outputFile << endl << "There is no one in the line" << endl;
    
    } else {                                                        // If there is somebody
        
        if (head->customerType == 'N') {
            
            outputFile << endl << "Next transaction is processed" << endl;
            
            p = head;                   // p is going to be deleted.
            
            head = head->next;          // Head is the next one, if there is no element head is null
            
            headNormal = head;          // HeadNormal is the next element if there is no element headnormal is null.
            
            q = p->headTransaction;     // q is going to be deleted.
            
            while (q) {                 // All transactions of the element is being deleted.
                
                first = q;
                q = q->next;
                delete first;
            }
            
            delete p;                   // The element is being deleted.
            
        
        } else if (head->customerType == 'P'){              // If head element is a premium
            
            outputFile << endl << "Next transaction is processed" << endl;
            
            first = head->headTransaction;                          // first gets the first transaction of the element
            head->headTransaction = head->headTransaction->next;    // Head transaction of the element is the second transaction
            delete first;
            
            if (head->headTransaction == NULL) {                    // If there is no head transaction (There is no more than 1 element)
                p = head;                                           // p is being deleted, p is the first element of the main list
                head = head->next;                                  // head is the next one
                
                if (head) {                                         // if head is not null
                    if (head->customerType == 'P') {
                        headPremium = head;                         // if head is premium member head premium is the head
                    }
                } else {
                    headPremium = head;                             // else headpremium is null like head
                }
                
                
                delete p;                                           // p is being deleted
                return;
            }
            
            if (head != NULL && head->customerType != 'N') {        // If there are more than 1 transaction
                tailPremium->next = head;                           // tailpremium next is the head that makes head go to the end of the premium list
                tailPremium = tailPremium->next;                    // new tailpremium
                head = head->next;                                  // head is the next one
                tailPremium->next = headNormal;                     // premiumlist and normallist connects
            }
        
        } else {
            return;
        }
    }
}

void List::destruct(){                  // DESTRUCTION FUNCTION
    
    Customer * p;                           // All elements are deleted.
    Transaction * first, * q;
    
    while (head) {
        
        p = head;
        head = head->next;
        q = p->headTransaction;
        
        while (q) {
            
            first = q;
            q = q->next;
            delete first;
        }
        
        delete p;
    }
    
    fclose(giris);
    outputFile << endl << "Program exits";
    outputFile.close();
}

void List::removeCustomer(char * textline){             // REMOVING FUNCTION
    
    Customer * traverse = head;
    Customer * behind;
    char nameHolder[15], surnameHolder[15];
    char typeHolder;
    
    int i = 0;
    int a = 2;
    int found = 0;
    
    for (a = 2; textline[a] != ';'; a++) {          // ============ THIS PART READS THE FILE ==============
        nameHolder[i] = textline[a];
        i++;
    }
    
    nameHolder[i] = '\0';
    
    i = 0;++a;
    
    for (; textline[a] != ';'; a++) {
        surnameHolder[i] = textline[a];
        i++;
    }
    
    surnameHolder[i] = '\0';
    
    ++a;
    
    typeHolder = textline[a];                       // ======================================================
    
    Customer * p;
    Transaction *q, *first;
    
    if (head == NULL) {                             // If there is no element in the list
        outputFile << endl << nameHolder << " " << surnameHolder << " could not be found" << endl;
        return;
    }
    
    if (strcmp(head->name,nameHolder)==0) {
        if (strcmp(head->surname,surnameHolder)==0) {
            if (head->customerType == typeHolder) {             // If it is head
                
                p = head;                               // All transactions and the head itself is deleted and head is the next one
                head = head->next;
                q = p->headTransaction;
                    
                while (q) {
                        
                    first = q;
                    q = q->next;
                    delete first;
                        
                }
                
                delete p;
                outputFile << endl << nameHolder << " " << surnameHolder << " is removed" << endl;
                return;
            }
        }
    }
    
    while (traverse) {                          // Searching other elements
        
        behind = traverse;
        
        traverse = traverse->next;
        
        if (traverse==NULL) break;
        
        if (strcmp(traverse->name,nameHolder)==0) {
            if (strcmp(traverse->surname,surnameHolder)==0) {
                if (traverse->customerType == typeHolder) {         // if it is found
                    
                    p = traverse;                           // All transactions and the element itself is deleted
                    behind->next = traverse->next;          // connections
                    q = p->headTransaction;
                    
                    while (q) {
                        
                        first = q;
                        q = q->next;
                        delete first;
                        
                    }
                    
                    delete p;
                    outputFile << endl << nameHolder << " " << surnameHolder << " is removed" << endl;
                    return;
                }
            }
        }
    }
    
    outputFile << endl << nameHolder << " " << surnameHolder << " " << "could not be found" << endl;            // If it is not found
}

void List::create(){                            // CREATE FUNCTION
    
    giris = fopen("input_file.txt","r+");
    rewind(giris);
    
    if (!giris) {
        
        giris = fopen("input_file.txt","w+");
        
        if (!giris) {
            outputFile << endl << "File can not be opened";
            exit(EXIT_FAILURE);
        }
    }
    
    outputFile.open ("output_file.txt");
    
    head=NULL;headPremium=NULL;headNormal=NULL;
    tailPremium=NULL;tailNormal=NULL;
}

void List::searchCustomer(char * textline){
    
    Customer * traverse = head;
    char nameHolder[15] = {}, surnameHolder[15] = {};
    
    int i = 0;
    int a = 2;
    int found = 0;
    
    for (; textline[a] != ';' ; a++, i++) {                     // =============== READS THE FILE ==============
        nameHolder[i] = textline[a];
        
    }
    
    nameHolder[i] = '\0';
    
    i = 0;++a;
    
    for (; textline[a] != '\n'; a++, i++) {
        surnameHolder[i] = textline[a];
    }

    surnameHolder[i] = '\0';                                    // ==============================================
    
    while (traverse) {
        
        if (strncmp(traverse->name,nameHolder,strlen(traverse->name)) == 0){
            
            if (strncmp(traverse->surname,surnameHolder,strlen(traverse->surname)) == 0){       // If it is found, print it
        
                outputFile << endl << "The person is found";
                outputFile << endl << traverse->name << " " << traverse->surname << " " << traverse->customerType;
                found = 1;
                
                Transaction * headTran = traverse->headTransaction;
                
                while (headTran) {
                    outputFile << " " << headTran->tranName;
                    headTran = headTran->next;
                }
            
                outputFile << endl;
            }
        }
        
        traverse = traverse->next;
    }
    
    if (found == 0) {                       // If it is not found
        
        outputFile << endl << nameHolder << " " << surnameHolder << " could not be found" << endl;
    }
}

void List::printCustomer(){             // PRINT FUNCTION
    
    Customer * traverse = head;
    
    if (head==NULL) {
    
        outputFile << endl << "There is no one in the line" << endl;
        return;
    
    } else {
        
        while (traverse) {
            
            outputFile << endl << traverse->name << " " << traverse->surname << " " << traverse->customerType;
            
            Transaction * headTran = traverse->headTransaction;
            
            while (headTran) {
                outputFile << " " << headTran->tranName;
                headTran = headTran->next;
            }
            
            traverse = traverse->next;
        }
    }
    
    outputFile << endl;
}

void List::addCustomer(char * textline){            // ADD FUNCTION
    
    Customer * newCustomer = new Customer;
    Customer * traverse;
    newCustomer->next = NULL;
    Transaction *tran = NULL;
    Transaction *tran2 = NULL, *tran3 = NULL;
    
    int i = 0;
    int a = 0;
    
    for (a = 2; textline[a] != ';'; a++) {              // ================== READS THE FILE ===================
        newCustomer->name[i] = textline[a];
        i++;
    }
    
    newCustomer->name[i] = '\0';

    i = 0;++a;
    
    for (; textline[a] != ';'; a++) {
        newCustomer->surname[i] = textline[a];
        i++;
    }
    
    newCustomer->surname[i] = '\0';
    ++a;
    
    newCustomer->customerType = textline[a];
    a+=2;
    
    newCustomer->transactionNumber = textline[a] - 48;      // transaction number returns ascii value so i need to subtract 48 from it.
    
    a+=2;i=0;                                           // ========================================================
    
    tran = new Transaction;                             // Adding the transactions
    
    for (;textline[a] != ';'; a++) {                    // Actually i can do it with a for loop and it would be easy to make it
                                                        // but i did not change it.
        if (textline[a]=='\n') {
            break;
        }
        
        tran->tranName[i] = textline[a];
        i++;
    }
    
    tran->tranName[i] = '\0';
    tran->next = NULL;
    newCustomer->headTransaction = tran;
    
    if (textline[a]!='\n') {
        
        ++a;i=0;
        tran2 = new Transaction;
        
        for (; textline[a] != ';'; a++) {
            
            if (textline[a]=='\n') {
                break;
            }
        
            tran2->tranName[i] = textline[a];
            i++;
        }
        
        tran2->tranName[i] = '\0';
        tran->next = tran2;
        tran2->next = NULL;
    }
    
    if (textline[a]!='\n') {
        ++a;i=0;
        
        tran3 = new Transaction;
        
        for (; textline[a] != ';' || textline[a+1] != '\n'; a++) {
            
            if (textline[a]=='\n') {
                break;
            }
            
            tran3->tranName[i] = textline[a];
            i++;
        }
        
        tran3->tranName[i] = '\0';
        tran2->next = tran3;
        tran3->next = NULL;
    }                                                   // ======= ADDING TRANSACTIONS END ===========
    
    if (newCustomer->customerType == 'P') {             // ADDING ELEMENTS INTHE MAIN LIST
                                                        // If it is premium element
        if (headPremium == NULL) {                      // headpremium is null
        
            headPremium = newCustomer;                  // headpremium is new element
            head = headPremium;
            tailPremium = headPremium;
        
        } else {
            
            tailPremium->next = newCustomer;            // if there are premium elements
            tailPremium = tailPremium->next;            // add the new element to end of the premium list
        }
        
    } else {                                            // If it is normal element
        
        if (headNormal == NULL) {                       // If there is normal element
            
            headNormal = newCustomer;                   // head normal is assigned
            tailNormal = headNormal;
            
            if (headPremium == NULL) {                  // if there is no premium element
                head = headNormal;                      // head is headnormal
            }
        
        } else {                                        // there are normal elements
            
            tailNormal->next = newCustomer;             // new element is added to tailnormal
            tailNormal = tailNormal->next;
        }
    }
    
    if (tailPremium != NULL) {                          // if there are premium elements, connection is made between premiumlist and normallist
        tailPremium->next = headNormal;
    }
    
    outputFile << endl << "New customer is added" << endl;
}

typedef List Line;
Line bankline;

int main() {
    
    bankline.create();
    
    char dizi[60];
    
    while (fgets(dizi, 60, bankline.giris)){
        
        switch (dizi[0]) {
            
            case 'A':case 'a':
                // Add a new customer
                bankline.addCustomer(dizi);
                break;
                
            case 'V':case 'v':
                // Process next customer's transaction
                bankline.processTran();
                break;
                
            case 'S':case 's':
                // Search by name and surname
                bankline.searchCustomer(dizi);
                break;
                
            case 'R':case 'r':
                // Remove customer
                bankline.removeCustomer(dizi);
                break;
                
            case 'P':case 'p':
                // Print customer list
                bankline.printCustomer();
                break;
            
            case 'E':case 'e':
                bankline.destruct();
                return 0;
                break;
                
            default:
                break;
        }
    
        if (bankline.head==NULL) {
            bankline.headNormal=NULL;bankline.headPremium=NULL;
            bankline.tailPremium=NULL;bankline.tailPremium=NULL;
            
        }
    }
    
    return 0;
}
