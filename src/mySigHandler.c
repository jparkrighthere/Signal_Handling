////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c, division.c
// Semester:         CS 354 Lecture 002 Spring 2023
// Instructor:       deppeler
// 
// Author:           Jeonghyeon Park
// Email:            jpark634@wisc.edu
// CS Login:         jeonghyeon
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Spring 2023
//
////////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

//global variables for count and time
time_t currtime;
int usr1count;
int num_sec = 4;

// Signal handler that handles SIGALRM
void handler_SIGALRM() {
    currtime = time(NULL);
    //changes time to string format
    char *outputTime = ctime(&currtime);

    // prints process ID and current time
    printf("PID: %d CURRENT TIME: %s", getpid(), outputTime); 
    // rearm alarm for 4 seconds
    alarm(num_sec);
}

// Signal handler that handles SIGUSR1, increments counter
void handler_SIGUSR1() {
    printf("SIGUSR1 handled and counted!\n");
    usr1count++;
}

// Signal handler that handles SIGINT, displays counter for SIGUSR1 and exit
void handler_SIGINT() {
    printf("SIGINT handled.\n");
    printf("SIGUSR1 was handled %i times. Exiting now.\n", usr1count);
    exit(0);
}

int main() {
    struct sigaction act;
    struct sigaction usr;
    struct sigaction sigint;

    memset(&act, 0, sizeof(act));
    memset(&usr, 0, sizeof(usr));
    memset(&sigint, 0, sizeof(sigint));

    alarm(num_sec);// set up an initial alarm for signal to come
    
    // assign signal handlers and check returns of sigactions
    act.sa_handler = handler_SIGALRM;
    usr.sa_handler = handler_SIGUSR1;
    sigint.sa_handler = handler_SIGINT;

    if (sigaction(SIGALRM, &act, NULL)!=0) {
        printf("Error: binding SIGALRM Handler\n");
        exit(1);
    }

    if (sigaction(SIGUSR1, &usr, NULL)!=0) {
        printf("Error: binding SIGUSR1 Handler\n");
        exit(1);
    }

    if (sigaction(SIGINT, &sigint, NULL)!=0) {
        printf("Error: binding SIGINT Handler\n");
    }

    printf("PID and time print every 4 seconds.\n");
    printf("Type Ctrl-C to end the program.\n");

    // infinite loop to keep program running
    while (1) {
    }

    return 0;
}