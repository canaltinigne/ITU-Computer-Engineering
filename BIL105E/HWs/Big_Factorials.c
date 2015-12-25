// Can Yılmaz Altıniğne - 150130132 - BIL 105E HW3
#include <stdio.h>

int facAndLengthFinder (int [], int);               // FUNCTION PROTOTYPES
void printArray (int [], int, int, int);

int main(){
    int len1, len2, len3;
    int factorialNum;
    int numArr1 [300] = {0};                    // Array for N!
    int numArr2 [300] = {0};                    // Array for N-1!
    int numArr3 [300] = {0};                    // Array for N-2!
                                                   // I could not use recursive function because i need
    printf("\nEnter N: ");                      // length of all 3 factorial.
    scanf("%d", &factorialNum);
    
    len1 = facAndLengthFinder(numArr1, factorialNum);
    
    // I benefited from the lengths of arrays to align right.
    
    len2 = facAndLengthFinder(numArr2, factorialNum-1);
    len3 = facAndLengthFinder(numArr3, factorialNum-2);
    
    // Finding length of arrays to align right len3 = facAndLengthFinder(numArr3, factorialNum-2);
    
    printArray (numArr3, factorialNum-2, len1, len3);
    printArray (numArr2, factorialNum-1, len1, len2);
    printArray (numArr1, factorialNum, len1, len1);
    

    return 0;
}                 // FUNCTIONS

int facAndLengthFinder (int numArr[], int number){          // Factorial and Length Finder Function
    
    int i, j, k, a, b;
    int control;
    int zeroFac = 1;
    int commaNumber = 0;                                    // Number of commas is included in length.
    
    if (number<=0) {                                        // If the user enters zero value this provides to
        zeroFac = 0;                                        // find 1! since 0! = 1! and if the user enters
        number = 1;                                         // negative values it finds zero factorial.
    }
    
    numArr[0] = 1;                                          // Initializing the first member of array to 1.
    
    for (i=1; i<=number; i++) {                             // To the number whose factorial is seeking
                                                                    // We have to multiply every member of array with the
        for (j=0; j<=298; j++){                             // 1 to N.
            numArr[j] *= i;
        }
        
        for (k=0; k<=298; k++) {                            // If the value after multiplying is higher than
                                                                        // 9, we have to shift ten's place to next member and
            if (numArr[k]>9) {                              // we have to assign one's place to value of
                numArr[k+1] += numArr[k]/10;                // the array member which we're in.
                numArr[k] = numArr[k]%10;                   // We have to do this for every member.
            }
        }
    }
    
    for (a=298; a>=0; a--) {                                // We have 300 members in array. After finding
                                                                    // factorial, we have some number to final member
        if (numArr[a] != 0) {                               // After final member there are all zeros.
            control = a;                                // Control enables us that the number of final member
            break;                                     // and control + 1 is the value of place for the value.
        }
    }
    
    for (b=control; b>=0; b--){                             // We are finding total comma numbers with this.
        if (b%3==0 && b!=0) {
            commaNumber++;
        }
    }
    
    return commaNumber + (control + 1);                       // This gives us total length of array.
}

void printArray (int numArr[], int number1, int length1, int length2){  // PRINTING ARRAY
    
    int a, control, zeroFac = 1, number, b;
    int rAlign;
    
    for (a=298; a>=0; a--) {
        
        if (numArr[a] != 0) {
            control = a;
            break;
        }
    }
    
    if (zeroFac==0)
        printf("\n%d!  = ", zeroFac);               // Printing 0!
    
    else {
        if (number1<10)                             // Same place for "=" sign.
            printf("\n%d!  = ", number1);
        else
            printf("\n%d! = ", number1);
    }
    
    for (rAlign=0; rAlign<=length1-length2; rAlign++) {         // Shifting right by benefiting the lengths of results.
        printf(" ");
    }
    
    for (b=control; b>=0; b--){                     // Printing array members and comma numbers.
        printf("%d", numArr[b]);
            
        if (b%3==0 && b!=0) {
            printf(",");
        }
    }
}