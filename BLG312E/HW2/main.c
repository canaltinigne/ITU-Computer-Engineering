// Can Yılmaz Altıniğne - 150130132
// Computer Operating Systems - Homework 2

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEMKEY1 1234
#define SEMKEY2 5678

typedef struct question{
    char text[45];
    int approvals;
} Question;

int s1,s2,questionNumber,memberNo;          // Global variables for semaphores, question number, member number
Question * questionSheet;                   // Global pointer for shared question sheet
FILE * inputFile;                           // Global pointer for input file

void sem_wait(int semid, int val){          // Semaphore wait function to decrement the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void sem_signal(int semid, int val){        // Semaphore signal function to increment the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void * doWork(void * typ){                  // Thread function

    char lesson[30];
    int buff;
    int waitTime;

    sem_wait(s2,1);                                 //  ---------------- CRITICAL SECTION -----------------------------
                                                                    // s2 is currently 1 - Mutual Exclusion for reading data from input
        fscanf(inputFile, "%d %s %d", &buff, lesson, &waitTime);        // Reading line
        int order = buff;

        strcpy(questionSheet[order-1].text, lesson);                 // Writing the data to array
        strcat(questionSheet[order-1].text, " question");
        questionSheet[order-1].approvals = 0;                        // Approaval initialization

    sem_signal(s2,1);                               // ---------------- CRITICAL SECTION ENDS

	sleep(waitTime);                // Sleep until wait time.

	sem_wait(s2,1);                 // Decrease the total question number value
        questionNumber--;           // There is mutex because it is a global variable we need to be careful
    sem_signal(s2,1);

	printf("WEC member %d: A question is prepared on %s\n",order,lesson);       // Question is prepared

	if(questionNumber == 0){    // S1 is initially 0, if all questions are written in the array, the last thread to write it make S1 equal to 1
        sem_signal(s1,1);
	}

	sem_wait(s1,1);             // Wait until S1 becomes 1, S1 is initially 0       SYNCHRONIZATION OF THREADS

	sem_signal(s1,1);           // When one thread get in the checking section it makes the next thread get in too.

            // CHECKING QUESTIONS

        int c = 0;              // All threads get in this section at the same time

        for(; c < memberNo; c++){
            if(c != order-1){

                sleep(1);           // Wait 1 second

                sem_wait(s2,1);             // Be careful changing shared variables, we use s2 for mutex

                    questionSheet[c].approvals++;       // Increment approval other than the member's order number

                sem_signal(s2,1);

                if(questionSheet[c].approvals == memberNo-1){               // approvals = T-1 question is ready
                    printf("WEC member %d: Question %d is ready\n",order,c+1);
                }
            }
        }

        // In homework it says wec members check questions concurrently and one question can be checked by more than one wec member
        // It means Checking operation must finish in ( Total member - 1 ) second since they can check questions concurrently
        // If we have 5 member all checking operation finishes in 4 seconds or like in the example it needs to finish in 2 seconds
        // I could have used sleep between sem_wait and sem_signal but then the checking operation finishes MemberNo * (MemberNo-1)
        // This gives output like in the homework pdf. But I think all checking operation has to finish in MemberNo-1 seconds since
        // Checking operations are made concurrently.

    pthread_exit(NULL);
}

int main(int argc, char * argv[]) {

    memberNo = atoi(argv[2]);           // read the member number from command line
    questionNumber = memberNo;          // assign it to global variable to use in threads

    pthread_attr_t attr;                // thread attribute initilaziton to join them
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);                    // No buffer to write outputs to console

    int rc;

    inputFile = fopen(argv[1], "r+");       // Open the file in main function

    if (!inputFile) {
        printf("File not found");
        return EXIT_FAILURE;
    }

    s1 = semget(SEMKEY1, 1, 0700|IPC_CREAT);            // Create s1 semaphore for sync
    semctl(s1, 0, SETVAL, 0);

    s2 = semget(SEMKEY2, 1, 0700|IPC_CREAT);            // Create s2 semaphore for mutex
    semctl(s2, 0, SETVAL, 1);

    questionSheet = malloc(memberNo*sizeof(Question));              // Question sheet has dynamic memory
    pthread_t * thArray = malloc(memberNo*sizeof(pthread_t));       // Thread array to create as much as the member number

    rewind(inputFile);                  // Take the cursor to beginning

    int x = 0;          // I defined int for for loops outside, Because Terminal in Lubuntu 14.04 gives some C99 error for that

    for (; x < memberNo; x++) {         // Creating threads
        rc = pthread_create(&thArray[x], &attr, doWork, (void *)x);

        if(rc){
            printf("\n Error: Thread not created");
            exit(EXIT_FAILURE);
        }
    }

    pthread_attr_destroy(&attr);        // We dont need attr value anymore

    int b = 0;

    for (; b < memberNo; b++) {                 // We have to use pthread_join to stop main() to perform steps after here
        rc = pthread_join(thArray[b], NULL);    // such as free, fclose, semctl
                                                // We pause execution of main until all threads finish their jobs
        if(rc){
            printf("\n Error: Thread not joined");
            exit(EXIT_FAILURE);
        }
    }

    free(questionSheet);                // Free questionSheet and thread dynamic arrays
    questionSheet = NULL;

    free(thArray);
    thArray = NULL;

    fclose(inputFile);

    semctl(s1,0,IPC_RMID,0);            // Delete semaphores
    semctl(s2,0,IPC_RMID,0);

    return 0;
}
