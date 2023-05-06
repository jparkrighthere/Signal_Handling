////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      mySigHandler.c, sendsig.c
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

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

// Global variable for successful operation count
int count = 0;

// Signal handler that handles SIGFPE - divided by zero
void handler_SIGFPE() {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %i\n", count);
    printf("The program will be terminated.\n");
    exit(0);
}

// Signal handler that handles SIGINT - ctrl-v
void handler_SIGINT() {
    printf("\nTotal number of operations completed successfully: %i\n", count);
    printf("The program will be terminated.\n");
    exit(0);
}

int main() {
    int num1, num2;
    char input[100];

    // set up structs for sigaction
    struct sigaction zero;
    struct sigaction c;

    memset(&zero, 0, sizeof(zero));
    memset(&c, 0, sizeof(c));

    // assign signal handlers and check returns of sigactions
    zero.sa_handler =handler_SIGFPE;
    c.sa_handler =handler_SIGINT;

    if (sigaction(SIGFPE, &zero, NULL)!=0) {
        printf("Error: binding SIGFPE Handler\n");
        exit(1);
    }

    if (sigaction(SIGINT, &c, NULL)!=0) {
        printf("Error: binding SIGINT Handler\n");
        exit(1);
    }

    while (1) {
        printf("Enter first integer: ");

        // gets an user input and check return value to see if it was successful
        if(fgets(input, 100, stdin) == NULL){ 
        printf("Error: unable to get inputs\n");
        exit(1);
        }

        num1 = atoi(input); // Turn fetched string into an int

        printf("Enter second integer: ");

        // gets an user input and check return value to see if it was successful
        if(fgets(input, 100, stdin) == NULL){
        printf("Error: unable to get inputs\n");
        exit(1);  
        }
        
        num2 = atoi(input);  // Turn fetched string into an int
        
        printf("%i / %i is %i with a remainder of %i\n", num1, num2, num1 / num2, num1 % num2);
        count++;// Count for successful operations
    }

    return 0;
}