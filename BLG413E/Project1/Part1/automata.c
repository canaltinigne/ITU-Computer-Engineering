// BLG 413E - SYSTEM PROGRAMMING
// PROJECT 1 - PART 1
// TEAM 6
//
// 150120107 AHMET TÜRK
// 150130039 OZAN ATA
// 150130132 CAN YILMAZ ALTINİĞNE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_next_seq(int *, int *, int, int);

int main(int argc, char * argv[]) {

	// VARIABLES
	char filename[20];
	FILE *fp;

	int * input_binary_array, * prev_gen_array, * next_gen_array;
	int j, generation_size = 0, rule_number, generation_number, res;

	printf("Enter the rule number: ");
	scanf("%d", &rule_number);

	printf("Enter the generation number: ");
	scanf("%d", &generation_number);

	// READING FILE NAME FROM CONSOLE
	strcpy(filename, argv[1]);

	if ((fp = fopen(filename, "rb+")) == NULL) {
		printf("File not found\n");
		exit(1);
	}

	if(fscanf(fp, "%d", &res) == 1) generation_size = res;

    printf("\n");

	// BINARY STRING
	input_binary_array = (int*) malloc(sizeof(int) * generation_size);

	// READING BINARY STRING
    j = 0;

	while(fscanf(fp, "%d", &res) == 1) input_binary_array[j++] = res;

    // USE THIS ARRAY FOR ITERATION
	prev_gen_array = (int*) malloc(sizeof(int) * generation_size);

    // FOR THE FIRST ARRAY PRINTING X IS BLACK - IS WHITE
	for (j = 0; j < generation_size; j++){
        prev_gen_array[j] = input_binary_array[j];
        prev_gen_array[j] ? printf("X ") : printf("- ");
	}

    // USE THIS ARRAY FOR ITERATION
	next_gen_array = (int*) malloc(sizeof(int) * generation_size);
	fclose(fp);

	printf("\n");

	// FOR GENERATIONS CALL ASSEMBLY FUNCTION TO FIND NEXT GENERATION THEN USE PREV ARRAY TO KEEP ITERATIONS

	while (generation_number--) {

        generate_next_seq(prev_gen_array, next_gen_array, rule_number, generation_size);

        for (j = 0; j < generation_size; j++) {     // NEXT GEN ARRAY IS THE ARRAY WHICH IS FOUND BY ASSEMBLY FUNCTION

            next_gen_array[j] ? printf("X ") : printf("- ");        // PRINT THAT ARRAY AND NOW PREV ARRAY IS THAT ARRAY
            prev_gen_array[j] = next_gen_array[j];                  // AND SEND THAT ARRAY TO ASSEMBLY FUNCTION AS THE OLD ARRAY
        }

        printf("\n");
	}

    printf("\n");

	free(input_binary_array);
	free(prev_gen_array);
	free(next_gen_array);

	return 0;
}
