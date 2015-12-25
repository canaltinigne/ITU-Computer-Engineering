/* Can Yılmaz Altıniğne - 150130132 - BIL 105E Homework (Scientific Calculator) */

/* !!! You have to enlarge the screen because of comment lines. It all mixes up if you do not. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float sine(float);
float cosine(float);
float exponent(float);                                                          /* ================================================= */
float power(float, float);                                                      /*                 FUNCTION PROTOTYPES               */
float absolute(float);                                                          /* ================================================= */
float factorial(float);
void showOperationList(void);

int main(){
    
    float number = 0, number2 = 0, buffer = 0, memory = 0;
    char str[20];
    char strNumber2[20];
    
    showOperationList();
    
    while (1) {                                             /* Infinite Loop until "Q" is entered. */
    
        printf("\nEnter user input: ");
        scanf("%19s", str);
                                                                                        /* ========================== */
        if (strcmp(str,"Q")==0) {      /* ---------------------------------->>>     To terminate the program  */
            break;                                                              /* ========================== */
        }
        
        else if (strcmp(str,"0") == 0 || atof(str) != 0) {      /* THE NUMBER CONDITION */
            number = atof(str);
            buffer = number;                                                    /* ======================================================================================= */
                                                                                            /*              To understand whether the string has number in itself or not.              */
        }                                                                       /*          atof function returns float number if the string has number in it and          */
                                                                                        /*          strcmp function compares two strings, if they are equal it returns 0.          */
                                                                                        /*          Also atof function returns 0 if the string has only characters. To know        */
                                                                                        /*  the input is number, case of having 0 in string and case of returning different value  */
                                                                                        /*         from 0 has been considered. We have to notice that the strcmp function          */
                /* ================================================= */                 /*       returns 0 if string has 0 and it also returns 0 if it has only characters.        */
                /*  To understand which operation will be executed.  */                 /*    Because of both atof and strcmp function ought to be used to understand the case     */
                /* ================================================= */                 /* ======================================================================================= */
        
        else if(strcmp(str,"S")==0){            /* SINE CONDITION. */
            
            printf("\nSin(%.4f) = %.4f\n", number, sine(number));                           /* =========================================================================== */
            buffer = sine(number);                                                          /*     Buffer is used for making multiple operations by using the output of    */
            number = buffer;                                                                /*    the previous operation. For example, if the user enter 21 first, later   */
                                                                                                        /*    + and finally 43, the result is 64. The user can enter / now and enter   */
        }                                                                                   /*      a new number such as 32. The program makes new operation 64 / 32 = 2.  */
                                                                                                    /* The user can always enter new 2 numbers for new operation if the user wants */
        else if(strcmp(str,"N")==0){           /* COSINE CONDITION. */                      /*          but the use of buffer provides the continuation of operation.      */
                                                                                                        /* =========================================================================== */
            printf("\nCos(%.4f) = %.4f\n", number, cosine(number));
            buffer = cosine(number);
            number = buffer;
        }
        
        
        else if(strcmp(str,"T")==0){          /* TANGENT CONDITION */
            
            if(number == 90 || number == 270)                                       /* Undefined situation of tangent */
                printf("\nIt is undefined\n");
            
            else{
                printf("\nTan(%.4f) = %.4f\n", number, sine(number) / cosine(number));
                buffer = sine(number) / cosine(number);
                number = buffer;
            }
        }
        
        else if(strcmp(str,"E")==0){                /* EXPONENT CONDITION */
            
            printf("\nExp(%d) = %.f\n", (int)number, exponent(number));
            buffer = exponent(number);
            number = buffer;
        }
        
        else if(strcmp(str,"W")==0){                    /* POWER CONDITION */
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (W).\n");             /* If the user does not enter a number after calling the function */
                printf("\nEnter user input: ");                                                           /* this while loop provides a new entry as a number for function  */
                scanf("%s", strNumber2);                                                                  /*                after showing invalid input sentence.           */
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )           /* NUMBER SITUATION FOR 2nd operand */
                number2 = atof(strNumber2);
            
            else if (strcmp(strNumber2,"MR") == 0)                              /* MR value for 2nd operand */
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)                                /* PI value for 2nd operand */
                number2 = 3.1415;
            
            printf("\nPower(%.4f,%d) = %.4f\n", number, (int)number2, power(number, number2));
            buffer = power(number, number2);
            number = buffer;
        }
        
        else if(strcmp(str,"A")==0){                    /* ABSOLUTE CONDITION */
            
            printf("\nAbsolute(%.4f) = %.4f\n", number, absolute(number));
            buffer = absolute(number);
            number = buffer;
        }
        
        else if(strcmp(str,"F")==0){                                               /* FACTORIAL CONDITION */
            
            printf("\nFactorial(%d) = %.f\n", (int)number, factorial(number));
            buffer = factorial(number);
            number = buffer;
        }
        
        else if(strcmp(str,"+")==0){                                    /* ADDING */
            
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (+).\n");                  /* THE SAME SITUATIONS IN THE POWER SITUATION (While loop, MR, Number, PI values.) */
                printf("\nEnter user input: ");
                scanf("%s", strNumber2);
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )
                number2 = atof(strNumber2);
                
            else if (strcmp(strNumber2,"MR") == 0)
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)
                number2 = 3.1415;
            
            printf("\n%.4f + %.4f = %.4f\n", number, number2, number + number2);
            buffer = number + number2;
            number = buffer;
        }
        
        else if(strcmp(str,"-")==0){                                   /* SUBTRACTION */
            
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (-).\n");                  /* THE SAME SITUATIONS IN THE POWER SITUATION (While loop, MR, Number, PI values.) */
                printf("\nEnter user input: ");
                scanf("%s", strNumber2);
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )
                number2 = atof(strNumber2);
            
            else if (strcmp(strNumber2,"MR") == 0)
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)
                number2 = 3.1415;
            
            printf("\n%.4f - %.4f = %.4f\n", number, number2, number - number2);
            buffer = number - number2;
            number = buffer;
        }
        
        else if(strcmp(str,"/")==0){                                /* DIVIDING */
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (/).\n");                  /* THE SAME SITUATIONS IN THE POWER SITUATION (While loop, MR, Number, PI values.) */
                printf("\nEnter user input: ");
                scanf("%s", strNumber2);
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )
                number2 = atof(strNumber2);
            
            else if (strcmp(strNumber2,"MR") == 0)
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)
                number2 = 3.1415;
            
            if(number2 == 0)
                printf("\nIt is undefined\n");
            
            else if(number2 != 0){
                printf("\n%.4f / %.4f = %.4f\n", number, number2, number / number2);
                buffer = number / number2;
                number = buffer;
            }
        }
        
        else if(strcmp(str,"*")==0){                                                /* MULTIPLING */
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (*).\n");                  /* THE SAME SITUATIONS IN THE POWER SITUATION (While loop, MR, Number, PI values.) */
                printf("\nEnter user input: ");
                scanf("%s", strNumber2);
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )
                number2 = atof(strNumber2);
            
            else if (strcmp(strNumber2,"MR") == 0)
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)
                number2 = 3.1415;
            
            printf("\n%.4f * %.4f = %.4f\n", number, number2, number * number2);
            buffer = number * number2;
            number = buffer;
        }
        
        else if(strcmp(str,"%")==0){                                                        /* MODULUS */
            printf("\nEnter user input: ");
            scanf("%s", strNumber2);
            
            while(strcmp(strNumber2,"0") != 0 && atof(strNumber2) == 0 && strcmp(strNumber2,"MR")!=0 && strcmp(strNumber2,"P")!=0){
                printf("\nInvalid input for the operator (%%).\n");                 /* THE SAME SITUATIONS IN THE POWER SITUATION (While loop, MR, Number, PI values.) */
                printf("\nEnter user input: ");
                scanf("%s", strNumber2);
            }
            
            if(strcmp(strNumber2,"0") == 0 || atof(strNumber2) != 0 )
                number2 = atof(strNumber2);
            
            else if (strcmp(strNumber2,"MR") == 0)
                number2 = memory;
            
            else if(strcmp(strNumber2,"P") == 0)
                number2 = 3.1415;
            
            printf("\n%d %% %d = %d\n", (int)number, (int)number2, (int)number % (int)number2);     /* We have to use int values for modulus. */
            buffer = (int)number % (int)number2;
            number = buffer;
        }
        
        else if(strcmp(str,"P")==0){                                                      /* PI */
            printf("\n3.1415\n");
            number = 3.1415;
        }
        
        else if(strcmp(str,"C")==0){                                                        /* CLEAN */
            printf("\n0.0000\n");
            buffer = 0;
            number = buffer;
        }
        
        else if(strcmp(str,"M")==0){                                                     /* MEMORY */
            memory = buffer;
        }
        
        else if(strcmp(str,"MR")==0){                                                   /* MEMORY RETURN */
            printf("\n%.4f\n", memory);
            number = memory;
        }
        
        else if(strcmp(str,"MC")==0){                                                   /* MEMORY CLEAN */
            memory = 0;
        }
        
        else{
            printf("\nInvalid character. Choose from the operators below:\n");
            showOperationList();
        }
            
    }
    
    printf("\nThank you for using the program.\n");
    return 0;
    
}

void showOperationList(void){              /* Showing operation list. */                                /* ======================================================== */
    printf("\n------------------------------------------------------------"                             /*                          FUNCTIONS                       */
           "\nThe list of operations in this simple calculator:"                                        /* ======================================================== */
           "\nsine (S), cosine (N), tangent (T), exponent (E)"
           "\npower (W), absolute (A), factorial (F)"
           "\nadd (+), subtract (-), divide(/), multiply(*), modulus (%%)"
           "\nπ (P), Quit (Q), Memory (M), Clear (C), Memory Clear (MC)"
           "\nMemory Return (MR)"
           "\n------------------------------------------------------------\n");
}

float sine(float x){                                                    /* SINE FUNCTION */
    
    float radian, taylorSin=0, i;
    
    if (x==0 || x == 180 || x == 360)
        return 0;
        
    else if (x==90)
        return 1;
    
    else if (x==270)
        return -1;
    
    else if(x > 0 && x < 90){
        
        radian = x * 3.14159 / 180;                                                                 /* Transform of degree entry to radian for Taylor Series. */
        
        for (i=0; i<=12; i++){
            taylorSin += (power(-1,i) * power(radian,(2*i)+1) / factorial((2*i)+1));                /* Taylor Series for sine. */
        }
        
        return taylorSin;
    }                                                                                               /* We should consider all 4 areas of coordination system. */
    
    else if(x > 90 && x < 180){
        
        x = 180 - x;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=12; i++){
            taylorSin += (power(-1,i) * power(radian,(2*i)+1) / factorial((2*i)+1));
        }
        
        return taylorSin;
    }
    
    else if(x > 180 && x < 270){
        
        x = x - 180;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=12; i++){
            taylorSin -= (power(-1,i) * power(radian,(2*i)+1) / factorial((2*i)+1));
        }
        
        return taylorSin;
    }
    
    else if(x > 270 && x < 360){
        
        x = 360 - x;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=12; i++){
            taylorSin -= (power(-1,i) * power(radian,(2*i)+1) / factorial((2*i)+1));
        }
        
        return taylorSin;
    }
    
    else
        return 0;
}

float cosine(float x){                                          /* COSINE FUNCTION */
    
    float radian, taylorCos = 0, i;
    
    if (x==90 || x == 270)
        return 0;
    
    else if (x==0 || x==360)
        return 1;
    
    else if (x==180)
        return -1;
    
    else if(x > 0 && x < 90){
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=15; i++){
            taylorCos += (power(-1,i) * power(radian,2*i) / factorial(2*i));                            /* Taylor Series for cosine. */
        }
        
        return taylorCos;
    }
    
    else if(x > 90 && x < 180){
        x = 180 - x;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=15; i++){
            taylorCos -= (power(-1,i) * power(radian,2*i) / factorial(2*i));
        }
        
        return taylorCos;
    }
    
    else if(x > 180 && x < 270){
        
        x = x - 180;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=15; i++){
            taylorCos -= (power(-1,i) * power(radian,2*i) / factorial(2*i));
        }
        
        return taylorCos;
    }
    
    else if(x > 270 && x < 360){
        
        x = 360 - x;
        
        radian = x * 3.14159 / 180;
        
        for (i=0; i<=15; i++){
            taylorCos += (power(-1,i) * power(radian,2*i) / factorial(2*i));
        }
        
        return taylorCos;
    }
    
    else
        return 0;
}

float exponent(float x){                                /* EXPONENT FUNCTION */
    return power(10,x);
}

float power(float x, float y){                          /* POWER FUNCTION */
    
    double result=1;
    int i;
    
    y = (int)y;
    
    if (y==0) {
        return 1;
    }
    
    else {
        for (i=1; i<=y; i++) {
            result *= x;
        }
        
        return result;
    }
}

float absolute(float x){                                   /* ABSOLUTE FUNCTION */
    if (x<0) {
        return -1 * x;
    }
    else
        return x;
}

float factorial(float x){                                  /* FACTORIAL FUNCTION */
    x = (int)x;
    
    if (x==0 || x==1) {
        return 1;
    }
    else
        return x * factorial(x-1);
}