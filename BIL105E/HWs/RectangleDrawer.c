#include <stdio.h>

void rectangleDrawerCaseOne (int height, int width, int thickness);
void rectangleDrawerCaseTwo (int recHeight, int recWidth, int recThickness);
void rectangleDrawerCaseThree (int recHeight, int recWidth, int recThickness);
void rectangleDrawerCaseFour (int recHeight, int recWidth, int recThickness);

int main(){
    
    int height, width, thickness, control = 1;
    
    printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * *");
    printf("\n* Rectangle Drawer Program coded by Can Altinigne *");
    printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * *");
    
    while (control == 1) {
        
        printf("\n\n=================MENU=====================");
        printf("\nEnter the height value of rectangle: ");                                                  // Entering the values.
        scanf("%d", &height);
        printf("Enter the width value of rectangle: ");
        scanf("%d", &width);
        printf("Enter the thickness value of rectangle: ");
        scanf("%d", &thickness);
        printf("==========================================\n");
        
        if (2*thickness >= height && 2*thickness >= width )                                                 // Assigning the functions which are used for the different situations.
            rectangleDrawerCaseOne (height, width, thickness);
        
        else if (2*thickness >= width)
            rectangleDrawerCaseTwo(height, width, thickness);
        
        else if (2*thickness >= height)
            rectangleDrawerCaseThree(height, width, thickness);
        
        else
            rectangleDrawerCaseFour(height, width, thickness);
        
        printf("\nIf you want to continue to draw please press 1, otherwise please press 0: ");             // To continue or not.
        scanf("%d", &control);
        
        if (control == 0) {                                                                                 // If the user enters 0 to quit. That leads to
            break;                                                                                          // "Thank you for using the program." message.
        }
        
        while(control != 0 && control != 1){                                                                // If the user enters a value which is not equal to 1 or 0,
            printf("\nIf you want to continue to draw please press 1, otherwise please press 0: ");         // This while loop works.
            scanf("%d", &control);
        }
    }
    
    printf("\nThank you for using the program.");
        
    return 0;
    
}

void rectangleDrawerCaseOne (int recHeight, int recWidth, int recThickness){                // This function is used when 2*thickness >= height and 2*thickness >= width
    
    int i,j;
    
    printf("It is not possible to draw your rectangle with the specified thickness.");
    printf("\nThe rectangle without the thickness option is drawn below:\n");
    
    for (i=1; i<=recHeight; i++) {
        for (j=1; j<=recWidth; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void rectangleDrawerCaseTwo (int recHeight, int recWidth, int recThickness){                // This function is used when 2*thickness >= width
    
    int i,j,k,a;
    int totalStarsOneSide;
    
    if (recWidth%2==0)                                                                  // We have to look at the value of width. If it is even or odd then the number of
        totalStarsOneSide = (recWidth/2)-1;                                             // total stars and thickness at left and right changes respect to this value.
    
    else if (recWidth%2==1)
        totalStarsOneSide = (recWidth-1)/2;
    
    if (recThickness<recWidth){                                                             // First we should consider the situations that
                                                                                                    // the thickness itself is lower than the width of the rectangle.
        for (i=1; i<=recThickness; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
            printf("\n");
        }
        
        for (i=1; i<=recHeight-(2*recThickness); i++) {
            for (j=1; j<=totalStarsOneSide; j++) {
                printf("*");
            }
            for (k=1; k<=recWidth-(2*totalStarsOneSide); k++) {
                printf(" ");
            }
            for (a=1; a<=totalStarsOneSide; a++) {
                printf("*");
            }
            
            printf("\n");
        }
        
        for (i=1; i<=recThickness; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
            printf("\n");
        }
    }

    else{                                                                                      // Secondly, we have to look at the situations that thickness
                                                                                                       // is higher or equal to width value.
        for (i=1; i<=recThickness; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
            printf("\n");
        }
        
        if (recWidth%2==0)
            totalStarsOneSide = (recWidth/2)-1;
            
        else if (recWidth%2==1)
            totalStarsOneSide = (recWidth-1)/2;
        
        for (i=1; i<=recHeight-(2*recThickness); i++) {
            for (j=1; j<=totalStarsOneSide; j++) {
                printf("*");
            }
            for (k=1; k<=recWidth-(2*totalStarsOneSide); k++) {
                printf(" ");
            }
            for (a=1; a<=totalStarsOneSide; a++) {
                printf("*");
            }
            
            printf("\n");
        }
        
        for (i=1; i<=recThickness; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
}

void rectangleDrawerCaseThree (int recHeight, int recWidth, int recThickness){              // This function is used when 2*thickness >= height
    
    int i,j,k,a;
    int rowNumberForOneSide;
    
    if (recHeight%2==0)                                                                      // We have to look at the value of height. If it is even or odd then the number of
        rowNumberForOneSide = (recHeight/2)-1;                                               // rows and thickness at up and down changes respect to this value.
    
    else if (recHeight%2==1)
        rowNumberForOneSide = (recHeight-1)/2;

    
    if (recThickness<recHeight) {                                                           // First we should consider the situations that
                                                                                                    // the thickness itself is lower than the height of the rectangle.
        for (i=1; i<=rowNumberForOneSide; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
        
            printf("\n");
        }
            
        for (i=1; i<=recHeight-2*rowNumberForOneSide; i++) {
            for (j=1; j<=recThickness; j++) {
                printf("*");
            }
            for (k=1; k<=recWidth-2*recThickness; k++) {
                printf(" ");
            }
            for (a=1; a<=recThickness; a++) {
                printf("*");
            }
            
            printf("\n");
            
        }
        
        for (i=1; i<=rowNumberForOneSide; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
            
            printf("\n");
        }
    }
    
    else {                                                                                  // Secondly, we have to look at the situations that thickness
                                                                                                    // is higher or equal to height value.
        for (i=1; i<=rowNumberForOneSide; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
                    
            printf("\n");
        }
            
        for (i=1; i<=recHeight-2*rowNumberForOneSide; i++) {
            for (j=1; j<=recThickness; j++) {
                printf("*");
            }
            for (k=1; k<=recWidth-2*recThickness; k++) {
                printf(" ");
            }
            for (a=1; a<=recThickness; a++) {
                printf("*");
            }
                    
            printf("\n");
                    
        }
            
        for (i=1; i<=rowNumberForOneSide; i++) {
            for (j=1; j<=recWidth; j++) {
                printf("*");
            }
                    
            printf("\n");
        }
    }
}

void rectangleDrawerCaseFour (int recHeight, int recWidth, int recThickness){               // This function is used when 2*thickness < height and 2*thickness < weight
    
    int i,j,k,a;
    
    for (i=1; i<=recThickness; i++) {
        for (j=1; j<=recWidth; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    for (i=1; i<=recHeight-(2*recThickness); i++) {
        for (j=1; j<=recThickness; j++) {
            printf("*");
        }
        for (k=1; k<=recWidth-2*recThickness; k++) {
            printf(" ");
        }
        for (a=1; a<=recThickness; a++) {
            printf("*");
        }
            
        printf("\n");
    }
    
    for (i=1; i<=recThickness; i++) {
        for (j=1; j<=recWidth; j++) {
            printf("*");
        }
        printf("\n");
    }
}