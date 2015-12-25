#include "fileoperations.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void File::add(Phone_Record *nrptr){
	fseek(phonebook, 0, SEEK_END);
	fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::create(){	
	filename="phonebook.txt";
	phonebook = fopen( filename, "r+" );
	if(!phonebook){		
		if(!(phonebook = fopen( filename, "w+" ))){
			cerr << "Cannot open file" << endl;
			exit(1);
		}
	}
}

void File::close(){
	fclose(phonebook);
}

int File::search(char *desired){
	Phone_Record k;
	int index=0;
	bool all=false;
	int found=0;
	if(strcmp(desired,"*")==0)
		all=true;
	fseek(phonebook, 0, SEEK_SET);
	while(!feof(phonebook)){		
		index++;
		fread( &k, sizeof (Phone_Record), 1, phonebook);		
		if(feof(phonebook)) break;

		if(all || strncmp(k.name, desired, strlen(desired))==0){
			cout << index << "." << k.name << " " << k.phonenum << endl;
			found++;
		}
	}	
	return found;
}

void File::update(int recordnum, Phone_Record *nrptr){
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET)==0)
		fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::removee(int recordnum) {
	Phone_Record emptyrecord = { "","" };
	if (fseek(phonebook, sizeof(Phone_Record)*(recordnum - 1), SEEK_SET) == 0)
		fwrite(&emptyrecord, sizeof(Phone_Record), 1, phonebook);

	Phone_Record temprecord;
	FILE * tempFile;
	tempFile = fopen("temp.txt", "w+");

	if (!tempFile) {
		cout << "Temp file cannot open" << endl;
		exit(1);
	}

	fseek(phonebook, 0, SEEK_SET);
	fseek(tempFile, 0, SEEK_SET);

	while (!feof(phonebook)) {
		fread(&temprecord, sizeof(Phone_Record), 1, phonebook);

		if (feof(phonebook)) break;

		if (strcmp(temprecord.name, "") != 0) {
			if (strcmp(temprecord.phonenum, "") != 0) {
				fwrite(&temprecord, sizeof(Phone_Record), 1, tempFile);
			}
		}
	}
	
	remove(filename);
	
	if (!(phonebook = fopen(filename, "w+"))) {
		cout << "cannot open" << endl;
		exit(1);
	}
	fseek(phonebook, 0, SEEK_SET);
	fseek(tempFile, 0, SEEK_SET);

	while (!feof(tempFile)) {
		fread(&temprecord, sizeof(Phone_Record), 1, tempFile);
		if (feof(tempFile)) break;
		fwrite(&temprecord, sizeof(Phone_Record), 1, phonebook);
	}

	fclose(tempFile);
}
