// BLG 413E - SYSTEM PROGRAMMING
// PROJECT 1 - PART 2
// TEAM 6
//
// 150120107 AHMET TÜRK
// 150130039 OZAN ATA
// 150130132 CAN YILMAZ ALTINİĞNE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_nex_num(int *, int *, int);

void print_array(int * matrix, int row, int col){           // ARRAY PRINTING FUNCTION
    int j,k;
    for(j = 0; j < row; j++){
        printf("\n");
        for(k = 0; k < col; k++){
            printf("%c ", matrix[(j)*(col)+k] ? 'X' : '-');     // X FOR BLACK AND - FOR WHITE
        }
    }
}

int main(int argc, char * argv[]) {

	char matrix_file_name[20];
	strcpy(matrix_file_name, argv[1]);

	char rule_file_name[20];
	strcpy(rule_file_name, argv[2]);

	FILE * matrix_file, * rule_file;

	int res, matrix_row_number, matrix_column_number, total_size, j = 0, k = 0,x,y,i;
	int * matrix, *input_matrix, *rule_array, *new_matrix, *ptr;
	char ch;

	if((matrix_file = fopen(matrix_file_name, "r+")) == NULL) exit(EXIT_FAILURE);
	if((rule_file = fopen(rule_file_name, "r+")) == NULL) exit(EXIT_FAILURE);

	fscanf(matrix_file,"%d %d",&matrix_row_number, &matrix_column_number);

    int matrix_size = matrix_row_number * matrix_column_number;
	total_size = (matrix_row_number+2)*(matrix_column_number+2);        // WE WRAP THE MATRIX WITH ZEROS AROUND IT
                                                                        // BY THIS WAY WE CAN START WITH THE FIRST ELEMENT
	matrix = (int*) malloc(sizeof(int) * total_size);                   // OF THE EXTENDED MATRIX TO CALCULATE
	input_matrix = (int*) malloc(sizeof(int) * matrix_size);            // MATRIX IS EXTENDED INPUT MATRIX
	new_matrix = (int*) malloc(sizeof(int) * matrix_size);              // INPUT MATRIX IS WHAT WE HAVE FROM INPUT FILE
	rule_array = (int*) malloc(sizeof(int) * 32);                       // NEW MATRIX IS CREATED BY ASSEMBLY FUNCTION
                                                                        // AND RULE ARRAY KEEPS RULE FROM RULE INPUT FILE
	while(fscanf(matrix_file,"%d",&res)==1) input_matrix[j++] = res;    // ASSIGNING ELEMENTS TO INPUT MATRIX

	int big_row = matrix_row_number+2;                                  // HEIGHT AND WIDTH OF EXTENDED INPUT MATRIX
	int big_column = matrix_column_number+2;

	for(j=0; j < total_size; j++){
        if(j < big_column) matrix[j] = 0;                               // SIDES OF THAT MATRIX IS 0, OTHER ELEMENTS ARE
        else if(j%big_column == 0) matrix[j] = 0;                       // FROM THE INPUT MATRIX
        else if(j%big_column == big_column-1) matrix[j] = 0;
        else if(j >= (big_row-1)*big_column) matrix[j] = 0;
        else matrix[j] = input_matrix[k++];
	}

	j = 0;

	while(fscanf(rule_file,"%d",&res)==1) rule_array[j++] = res;            // ASSIGNING RULE ARRAY
	ch = 'y';

	while (ch != 'n') {                                 // WHILE THE USER DOES NOT ENTER N KEEP CREATING NEW MATRICES
        for(x = 0; x < matrix_row_number; x++){
            for(y = 0; y < matrix_column_number; y++){
                ptr = &matrix[x*(matrix_column_number+2)+y];                    // WE USE ADDRESS OF ELEMENTS OF EXTENDED MATRIX
                i = find_nex_num(ptr, rule_array, matrix_column_number+2);      // UNTIL ROW AND COLUMN NUMBERS OF SMALLER INPUT MATRIX
                new_matrix[(x*matrix_column_number)+y] = i;                     // N: CURRENT LOC, N+1: NORTH, N+COL: WEST, N+COL+1: CENTER
            }                                                                   // N+COL+2: EAST, N+2*COL+1: SOUTH
        }                                                                       // ASSEMBLY FUNCTION RETURNS THE SITUATION OF THAT LOCATION
                                                                                // IN THE NEW MATRIX
        k = 0;                                                                  // COL_NUMBER+2 IS THE COLUMN NUMBER OF EXTENDED MATRIX

        print_array(new_matrix,matrix_row_number,matrix_column_number);         // PRINT THE NEW ARRAY
        printf("\n");

        for(j=0; j < total_size; j++){                                      // ASSIGN THE ELEMENTS OF NEW ARRAY TO BIG ARRAY
            if(j < big_column) matrix[j] = 0;                               // TO CREATE NEW MATRICES
            else if(j%big_column == 0) matrix[j] = 0;
            else if(j%big_column == big_column-1) matrix[j] = 0;
            else if(j >= (big_row-1)*big_column) matrix[j] = 0;
            else matrix[j] = new_matrix[k++];
        }

        printf("Keep going ? (Y/n): ");
        scanf(" %c", &ch);

        printf("\033[2J\033[1;1H");                         // TO CLEAN THE TERMINAL
	}

	fclose(matrix_file);
	fclose(rule_file);
	free(rule_array);
	free(matrix);
	free(new_matrix);
	free(input_matrix);

	return 0;
}
