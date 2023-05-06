////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      mySigHandler.c, division.c
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

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    // Check if number of command-line arguments is correct.
    if (argc!=3) {
        printf("Usage: sendsig <signal type> <pid>\n");
        exit(1);
    }

    // parse argv and assign corresponding variables
    char flag = argv[1][1];
    char *pid_str = argv[2];
    int pid =atoi(pid_str);

    // check user inputs for flags and perform corresponding task
    // checks return values of kill() functions
    if (flag=='i') {
        if (kill(pid,SIGINT)) {
            printf("Failed to send a signal\n");
            exit(1);
        }
    }

    if (flag=='u') {
        if (kill(pid,SIGUSR1)) {
            printf("Failed to send a signal\n");
            exit(1);
        }
    }

    return 0;
}