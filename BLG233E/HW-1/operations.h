/*
 * @Author
 * Student Name: Can Yılmaz Altıniğne
 * Student ID : 150130132
 * Date: 08/10/2015
 */

#ifndef operations_h
#define operations_h

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct book_record {                                //  Book Record Struct
    char authorName[20], authorSurname[20], title[20];
    int isbn, location;
    char bookType[10];
}Book;

struct File{                        //  List struct and its functions
    FILE * list;
    void create();
    void addBook();
    void printCatalogue();
    void searchBookAuthor();
    void searchBookType();
    void updateBook();
    void deleteBook();
    void close();
};

#endif /* operations_h */
