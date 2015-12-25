/*
 * @Author
 * Student Name: Can Yılmaz Altıniğne
 * Student ID : 150130132
 * Date: 08/10/2015
 */

#include "operations.h"

using namespace std;

void File::close(){         // File closing function
    fclose(list);
}

void File::create(){                    // File creating function when the program starts
    
    list = fopen("booklist.txt","r+");

    if (!list) {
        
        list = fopen("booklist.txt","w+");
        
        if (!list) {
            cout << "Booklist file could not be opened!";
            exit(1);
        }
    }
}

void File::printCatalogue(){                    //  Printing books
    
    Book record;
    
    fseek(list,0,SEEK_SET);
    
    cout << endl << "================ CATALOGUE ================" << endl;
        
    while (!feof(list)) {
            
        fread(&record,sizeof(Book),1,list);
            
        if (feof(list)) {
            break;
        }
            
        cout << endl << "Location: " << record.location << endl;
        cout << "Author Name: " << record.authorName << endl;
        cout << "Author Surname: " << record.authorSurname << endl;
        cout << "Book Title: " << record.title << endl;
        cout << "ISBN Number: " << record.isbn << endl;
        cout << "Book Type: " << record.bookType << endl;
        cout << endl << "===========================================" << endl;
        
    }
}

void File::updateBook(){                            //  Updating book
    
    Book searched;
    int loc;                            // integer variable to search ISBN Number of Book
    fseek(list,0,SEEK_SET);

    cout << endl << "Enter the ISBN Number of the book you want to update: " << endl;
    cin >> loc;
    cin.ignore(1000,'\n');
        
    while (!feof(list)) {
            
        fread(&searched,sizeof(Book),1,list);
            
        if (feof(list)) {                                                           // If it can not be found this works.
            cout << endl << "The book you searched could not be found." << endl;
            break;
        }
            
        if (searched.isbn == loc) {                                       /* If it was found we already passed that found book, to read that */
            fseek(list,-sizeof(Book),SEEK_CUR);                           /* we get back 1 Book size to come to beginning of the book we */
                                                                              /* want to change */
            cout << endl << "Enter the new Author Name: " << endl;
            cin.getline(searched.authorName,20);
            cout << "Enter the new Author Surname: " << endl;
            cin.getline(searched.authorSurname,20);
            cout << "Enter the new Book Title: " << endl;
            cin.getline(searched.title,20);
            cout << "Enter the new ISBN Number: " << endl;
            cin >> searched.isbn;
            cout << "Enter the new Location: " << endl;
            cin >> searched.location;
                
            while (searched.location < 1000 || searched.location > 9999) {                  /* Location controller 4-Digit */
                cout << "Please enter a 4 digit number for location: " << endl;
                cin >> searched.location;
            }
                
            cin.ignore(1000,'\n');
                
            cout << "Enter the new Book Type: " << endl;
            cin.getline(searched.bookType,10);
            
            fwrite(&searched,sizeof(Book),1,list);                      /* Write updated book to file */
                
            cout << endl << "You have updated the book" << endl;
                
            break;
                
        }
    }
}

void File::addBook(){                                       // Adding function
    
    Book newBook;
    
    cout << endl << "Enter the Author Name: " << endl;
    cin.getline(newBook.authorName,20);
    cout << "Enter the Author Surname: " << endl;
    cin.getline(newBook.authorSurname,20);
    cout << "Enter the Book Title: " << endl;
    cin.getline(newBook.title,20);
    cout << "Enter the ISBN Number: " << endl;
    cin >> newBook.isbn;
    cout << "Enter the Location: " << endl;
    cin >> newBook.location;
    
    while (newBook.location < 1000 || newBook.location > 9999) {
        cout << "Please enter a 4 digit number for location: " << endl;
        cin >> newBook.location;
    }
    
    cin.ignore(1000,'\n');
    cout << "Enter the Book Type: " << endl;
    cin.getline(newBook.bookType,10);
    
    fwrite(&newBook,sizeof(Book),1,list);
    
    cout << endl << "You have inserted a new book into the list" << endl;
}

void File::searchBookAuthor(){                      // Searching book by author function
    
    char name[20], surname[20];
    Book searched;
    
    int found = 0;
    
    fseek(list,0,SEEK_SET);

    cout << endl << "Enter the author name you want to find : " << endl;
    cin >> name;
    cout << "Enter the author surname: " << endl;
    cin >> surname;
    
    while (!feof(list)) {
            
        fread(&searched,sizeof(Book),1,list);
            
        if (feof(list)) {
                
            if (found==0) {
                cout << endl << "The book you searched could not be found." << endl;
            }
                
            break;
        }
            
        if (strcmp(searched.authorName,name) == 0) {                          // If it is found, write it to stream.
            if (strcmp(searched.authorSurname,surname) == 0) {
                    
                cout << endl << "===========================================" << endl;
                cout << endl << "Location: " << searched.location << endl;
                cout << "Author Name: " << searched.authorName << endl;
                cout << "Author Surname: " << searched.authorSurname << endl;
                cout << "Book Title: " << searched.title << endl;
                cout << "ISBN Number: " << searched.isbn << endl;
                cout << "Book Type: " << searched.bookType << endl;
                cout << endl << "===========================================" << endl;
                found++;
            }
        }
    }
    
    cout << endl << found << " books were found." << endl;
}

void File::deleteBook(){                                // Delete function
    
    Book searched;
    Book emptyRecord = {"","","",0,0,""};
    Book temporaryRecord;
    
    int loc;
    fseek(list,0,SEEK_SET);
        
    cout << endl << "Enter the ISBN Number of the book you want to delete: " << endl;
    cin >> loc;
        
    while (!feof(list)) {
            
        fread(&searched,sizeof(Book),1,list);
            
        if (feof(list)) {
            cout << endl << "The book you searched could not be found." << endl;
            return;
        }
            
        if (searched.isbn == loc) {                         /* If it was found we already passed that found book, to read that */
                                                                /* we get back 1 Book size to come to beginning of the book we */
            fseek(list,-sizeof(Book),SEEK_CUR);             /* want to delete, we write empty record to book which we want to delete */
            fwrite(&emptyRecord,sizeof(Book),1,list);
            break;
        }
    }
        
    FILE * temporaryFile = fopen("temp.txt", "w+");         /* Temporary file is opened */
        
    fseek(list, 0, SEEK_SET);                   /* Both files at the beginning */
    fseek(temporaryFile, 0, SEEK_SET);
        
    while (!feof(list)) {                               /* Writing books to temporary excluding blank book which is deleted */
            
        fread(&temporaryRecord, sizeof(Book), 1, list);
            
        if (feof(list)){
            break;
        }
            
        if (strcmp(temporaryRecord.authorName, "") != 0) {      /* Writing */
            fwrite(&temporaryRecord, sizeof(Book), 1, temporaryFile);
        
        }
    }
        
    remove("booklist.txt");                     // Initial list which we use is deleted to open it blank.
        
    create();                                   // Creating our initial list again but this time it is blank
        
    fseek(list, 0, SEEK_SET);                   /* Both files at the beginning */
    
    fseek(temporaryFile, 0, SEEK_SET);
        
    while (!feof(temporaryFile)) {                                  /* We have non-blank books in temporary file, we copy those books to */
                                                                        /* our clean initial list. */
        fread(&temporaryRecord, sizeof(Book), 1, temporaryFile);
            
        if (feof(temporaryFile)){
            break;
        }
            
        fwrite(&temporaryRecord, sizeof(Book), 1, list);
    }
        
    fclose(temporaryFile);                                      /* Temporary file finishes its work */
        
    cout << endl << "The book you chose has been deleted." << endl;
}

void File::searchBookType(){                    // Book searching by type function
    
    char type[10];
    Book searched;
    
    int found = 0;
    
    fseek(list,0,SEEK_SET);

    cout << endl << "Enter the book type you want to find : " << endl;
    cin.ignore(1000,'\n');
    cin.getline(type,10);
    
    while (!feof(list)) {
            
        fread(&searched,sizeof(Book),1,list);
            
        if (feof(list)) {
                
            if (found==0) {
                cout << endl << "The book you searched could not be found." << endl;
            }
                
            break;
        }
            
    if (strcmp(searched.bookType,type) == 0) {                      // If it is found, write it to stream.
                
            cout << endl << "===========================================" << endl;
            cout << endl << "Location: " << searched.location << endl;
            cout << "Author Name: " << searched.authorName << endl;
            cout << "Author Surname: " << searched.authorSurname << endl;
            cout << "Book Title: " << searched.title << endl;
            cout << "ISBN Number: " << searched.isbn << endl;
            cout << "Book Type: " << searched.bookType << endl;
            cout << endl << "===========================================" << endl;
            found++;
        }
    }
    
    cout << endl << found << " books were found." << endl;
}