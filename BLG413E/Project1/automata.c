#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_next_seq(char *);

int main(int argc, char * argv[]) {

	// VARIABLE
	char filename[20];
	FILE *fp;
	int  *arrayOne;
	int size = 10;
	int i = 0;
	int rule_number, generation_number;

	printf("Enter the rule number: ");
	scanf("%d\n", &rule_number);

	printf("Enter the generation number: ");
	scanf("%d\n", &generation_number);

	// READING FILE NAME FROM CONSOLE
	strcpy(filename,argv[1]);

	// BINARY STRING
	arrayOne = (int*) malloc(sizeof(int) * size);

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("File not found\n");
		exit(1);
	}

	// READING BINARY STRING
	while(1){
		int res = fscanf(fp, "%d", &arrayOne[i]);
		if (res == EOF) {
			break;
		}
		i++;
		if (i == size) {
			size *= 2;
			arrayOne = (int*) realloc(arrayOne, size);
		}
	}




	int j;
	for(j = 0; j < i; j++){
		printf("%d ", arrayOne[j]);
	}
	printf("\n");

	return 0;
}
