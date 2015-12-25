#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <stdio.h>
#include "record.h"

struct File{
	char *filename;
	FILE *phonebook;
	void create();
	void close();
	void add(Phone_Record *);
	int search(char []);
	void removee(int recordnum);
	void update(int recordnum, Phone_Record *);
};
#endif
