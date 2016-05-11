// Can Yılmaz Altıniğne - 150130132
// Computer Operating Systems - Homework 3

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <time.h>

#define SEMKEY1 1234
#define SEMKEY2 5678
#define SEMKEY3 1763
#define SEMKEY4 2134
#define SHMKEY1 9876

typedef struct question {       // Question Struct
    char text[45];
    int approvals;
} Question;

typedef struct application{     // Application Struct
    int exam_score;
    int interview_score;
    int total_score;
} ApplicationForm;

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

void mysignal(int signum){};        // Signal handling function

void mysigset(int num){
    struct sigaction mysigaction;
    mysigaction.sa_handler = (void *)mysignal;
    mysigaction.sa_flags = 0;
    sigaction(num,&mysigaction,NULL);
}

void * doWork(void * typ){                  // Thread function

    char lesson[30];
    int buff;
    int waitTime;

    //  ---------------- CRITICAL SECTION -----------------------------
    // s2 is currently 1 - Mutual Exclusion for reading data from input

    sem_wait(s2,1);

    fscanf(inputFile, "%d %s %d", &buff, lesson, &waitTime);        // Reading line
    int order = buff;

    strcpy(questionSheet[order-1].text, lesson);                 // Writing the data to array
    strcat(questionSheet[order-1].text, " question");
    questionSheet[order-1].approvals = 0;                        // Approaval initialization

    sem_signal(s2,1);                           // ---------------- CRITICAL SECTION ENDS

    sleep(waitTime);          // Sleep until wait time.

    sem_wait(s2,1);           // Decrease the total question number value
    questionNumber--;           // There is mutex because it is a global variable we need to be careful
    sem_signal(s2,1);

    printf("WEC member %d: A question is prepared on %s\n",order,lesson); // Question is prepared

    if(questionNumber == 0) { // S1 is initially 0, if all questions are written in the array, the last thread to write it make S1 equal to 1
        sem_signal(s1,1);
    }

    sem_wait(s1,1);       // Wait until S1 becomes 1, S1 is initially 0       SYNCHRONIZATION OF THREADS

    sem_signal(s1,1);     // When one thread get in the checking section it makes the next thread get in too.

    // CHECKING QUESTIONS

    int c = 0;              // All threads get in this section at the same time

    for(; c < memberNo; c++) {
        if(c != order-1) {

            sleep(1);   // Wait 1 second

            sem_wait(s2,1);     // Be careful changing shared variables, we use s2 for mutex

            questionSheet[c].approvals++;   // Increment approval other than the member's order number

            if(questionSheet[c].approvals == memberNo-1) {      // approvals = T-1 question is ready In the second homework i did not
                printf("WEC member %d: Question %d is ready\n",order,c+1);  // put this in mutual exclusion section
            }                                                           // it may sometimes print 2 ready message for 1 question
                                                                        // But in 3rd homework by putting this in mutex
            sem_signal(s2,1);                                           // keeps error.
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

    int f, i, shmid = 0;
    int child[2];                           // To keep pid of child processes
    mysigset(12);                           // Signal handler with num 12
    ApplicationForm * globalcp = NULL;      // Pointer to shared memory space
    int interViewEnd = 0, wecEnd = 0;       // Shared semaphores

    memberNo = atoi(argv[2]);               // read the member number from command line
    questionNumber = memberNo;              // assign it to global variable to use in threads

    for (i = 0; i < 2; i++) {               // Fork two child processes
        f = fork();                         // Parent process is registrar, child processes are wec and interviewer
        child[i] = f;

        if (f == 0) {
            break;
        } else if (i < 0){
            printf("Fork Error\n");
            exit(1);
        }
    }

    if(f==0) {      // CHILD PROCESSES

        if (i == 0) {               // THE WEC -------------------------------------------------------------------------------------

            pause();        // Wait for the kill signal from Registrar

            wecEnd = semget(SEMKEY4,1,0);       // Get wecEnd semaphore and signal it at the end Main processes will be waiting for it.

            s1 = semget(SEMKEY1, 1, 0700|IPC_CREAT); // Create s1 semaphore for sync
            semctl(s1, 0, SETVAL, 0);

            s2 = semget(SEMKEY2, 1, 0700|IPC_CREAT); // Create s2 semaphore for mutex
            semctl(s2, 0, SETVAL, 1);

            printf("The Written Exams Committee started preparing questions.\n");

            pthread_attr_t attr; // thread attribute initilaziton to join them
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
            setvbuf(stdout, (char*)NULL, _IONBF, 0);    // No buffer to write outputs to console

            int rc;

            inputFile = fopen(argv[1], "r+"); // Open the file in main function

            if (!inputFile) {
                printf("File not found");
                return EXIT_FAILURE;
            }

            questionSheet = malloc(memberNo*sizeof(Question)); // Question sheet has dynamic memory
            pthread_t * thArray = malloc(memberNo*sizeof(pthread_t)); // Thread array to create as much as the member number

            rewind(inputFile);  // Take the cursor to beginning

            int x = 0; // I defined int for for loops outside, Because Terminal in Lubuntu 14.04 gives some C99 error for that

            for (; x < memberNo; x++) { // Creating threads
                rc = pthread_create(&thArray[x], &attr, doWork, (void *)x);

                if(rc) {
                    printf("\n Error: Thread not created");
                    exit(EXIT_FAILURE);
                }
            }

            pthread_attr_destroy(&attr); // We dont need attr value anymore

            int b = 0;

            for (; b < memberNo; b++) {                     // We have to use pthread_join to stop main() to perform steps after here
                rc = pthread_join(thArray[b], NULL);        // such as free, fclose, semctl
                                                            // We pause execution of main until all threads finish their jobs
                if(rc) {
                    printf("\n Error: Thread not joined");
                    exit(EXIT_FAILURE);
                }
            }

            free(questionSheet); // Free questionSheet and thread dynamic arrays
            questionSheet = NULL;

            free(thArray);
            thArray = NULL;

            fclose(inputFile);

            semctl(s1,0,IPC_RMID,0); // Delete semaphores used by thread function
            semctl(s2,0,IPC_RMID,0);

            printf("The Written Exams Committee finished preparing questions.\n");

            sem_signal(wecEnd,1);       // Signal wecEnd semaphore so registrar (Main Process) can keep running
            exit(0);

        } else {        // CHILD PROCESS - THE INTERVIEWER -------------------------------------------------------------------------------------

            int interviewDur = atoi(argv[4]);               // read interview duration from command line

            pause();        // Wait for the kill signal from Registrar

            interViewEnd = semget(SEMKEY3,1,0);             // Get interViewEnd semaphore and signal it at the end Main processes will be waiting for it.

            srand(time(NULL));

            shmid = shmget(SHMKEY1, 3*sizeof(ApplicationForm), 0);          // Get shared memory space (Application Form)
            globalcp = (ApplicationForm *) shmat(shmid, 0, 0);

            printf("The Interviewer started interviews.\n");

            int sira;

            for (sira = 0; sira < 3; sira++) {                          //Give random interview score for 3 applicants
                globalcp[sira].interview_score = rand() % 51;
            }

            for (sira = 0; sira < 3; sira++) {
                sleep(interviewDur);                                    // For every applicant interviewer waits for interview duration.
                printf("Interview score of applicant %d is %d.\n",sira+1, globalcp[sira].interview_score);
            }

            printf("The Interviewer finished interviews.\n");
            shmdt(globalcp);                                        // Detach shared memory space
            sem_signal(interViewEnd,1);                             // Signal interViewEnd semaphore so registrar (Main Process) can keep running
            exit(0);
        }

    } else {            // MAIN PROCESS - PARENT PROCESS - THE REGISTRAR -------------------------------------------------------------------------------------

        int writtenExDur = atoi(argv[3]);           // Read written exam duration

        interViewEnd = semget(SEMKEY3, 1, 0700|IPC_CREAT); // Create interViewEnd semaphore for sync between registrar and interviewer
        semctl(s1, 0, SETVAL, 0);

        wecEnd = semget(SEMKEY4, 1, 0700|IPC_CREAT); // Create wecEnd semaphore for sync between registrar and wec
        semctl(s2, 0, SETVAL, 0);

        shmid = shmget(SHMKEY1, 3*sizeof(ApplicationForm), 0700|IPC_CREAT);     // Create shared memory space size of 3*ApplicationForm (There are 3 applicants)
        globalcp = (ApplicationForm *)shmat(shmid, 0, 0);

        srand(time(NULL));

        printf("The Registrar started taking applications.\n");         // Take application sleep 3 seconds
        sleep(3);
        printf("The Registrar finished taking applications.\n");

        kill(child[0], 12);             // Signal wec process
        sem_wait(wecEnd,1);             // Wait until wec process finish its job and signal wecEnd semaphore same thing as waitpid(child[0], NULL, 0)

        printf("The Registrar started the written exam.\n");

        int sira;

        for (sira = 0; sira < 3; sira++) {                  // Give random exam points to 3 applicants
            globalcp[sira].exam_score = rand() % 51;
        }

        sleep(writtenExDur);                            // Sleep for written exam duration

        for (sira = 0; sira < 3; sira++) {                              // Show them
            printf("Written exam score of applicant %d is %d.\n",sira+1, globalcp[sira].exam_score);
        }

        printf("The Registrar finished the written exam.\n");

        kill(child[1], 12);             // Signal interviewer process
        sem_wait(interViewEnd,1);       // Wait until interview process finish its job and signal interViewEnd semaphore same thing as waitpid(child[1], NULL, 0)

        printf("The Registrar started calculating total scores.\n");

        for (sira = 0; sira < 3; sira++) {              // Calculate total scores
            globalcp[sira].total_score = globalcp[sira].exam_score + globalcp[sira].interview_score;
        }

        sleep(3);           // Sleep 3 seconds to calculate total scores

        for (sira = 0; sira < 3; sira++) {      // Show total scores
            printf("Total score of applicant %d is %d.\n",sira+1, globalcp[sira].total_score);
        }

        printf("The Registrar finished calculating total scores.\n");

        shmdt(globalcp);                    // Detach shared memory space
        shmctl(shmid, IPC_RMID, 0);         // Delete shared memory space
        semctl(wecEnd,0,IPC_RMID,0);        // Delete wecEnd semaphore
        semctl(interViewEnd,0,IPC_RMID,0);  // Delete interView semaphore

        exit(0);

    }

    return 0;
}
