// This code will create children based on a user input value,
// and split the array of given numbers between the children 
// to be summed and returned to the parent for a total sum 
// with a message of what child sent what total
// example input 3 children and 6 values:
// gcc -o 4669 4669.c
// ./4669 3 1 2 3 4 5 6

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
    int children = atoi(argv[1]); //number of children
    int arryLen = argc - 2; //length of the array
    int arryIn[arryLen]; //make an array that is the length of the input array
    int i = 0;
    int total = 0;
    char parentStr[100] = "I am the parent of:";
    for (i = 0; i < arryLen; i++) {
        arryIn[i] = atoi(argv[i + 2]);
    }
    //Make read and write pipes
    int readPipe[children][2];
    int writePipe[children][2];
    for (i = 0; i < children; i++) {
        pipe(readPipe[i]);
        pipe(writePipe[i]);
    }

    int pid = getpid();
    printf("I am parent with pid %i\n", pid);

    for (i = 0; i < children; i++) {
        int childId = fork();
        if (childId == 0) {
            // if it is a child
            int j = 0;
            int arryRead[arryLen];
            int childTotal = 0;
            int arryLenChild = 0;
            close(writePipe[i][1]); // Close the write end of the write pipe
            read(writePipe[i][0], arryRead, sizeof(arryRead)); //
            close(writePipe[i][0]);
            // Print info
            int childPid = getpid();
            printf("I am child with pid %i: received ", childPid);
            // Maths
            if (arryLen % children == 0) {
                arryLenChild = arryLen/children;
            }
            else {
                arryLenChild = (arryLen/children) + 1;
            }
            for (j = (arryLenChild * i); j < (arryLenChild * i + arryLenChild); j++) {
                int count = j;
                if (j < arryLen) {
                    printf("%i ", arryRead[j]);
                    childTotal += arryRead[j];
                }
            }
            printf("sending partial sum %i\n", childTotal);
            // Write back
            char returnStr[10] = { 0 };
            sprintf(returnStr, "%i", childTotal);
            close(readPipe[i][0]);
            write(readPipe[i][1], returnStr, 10);
            close(readPipe[i][1]);
            exit(0);
        }
        else {
            // if it is the parent
            char readStr[10] = { 0 };
            close(writePipe[i][0]); // Close the read end of the write pipe in the parent
            write(writePipe[i][1], arryIn, sizeof(arryIn)); // Send the array through the write pipe
            close(writePipe[i][1]); // Pass control to child?
            wait(NULL); // Wait until the child is done
            close(readPipe[i][1]); // Close the write end of the read pipe
            read(readPipe[i][0], readStr, 10); // Read from the read end of the read pipe
            close(readPipe[i][0]);
            total += atoi(readStr);
            strcat(parentStr, " child ");
            char childIdStr[10] = { 0 };
            sprintf(childIdStr, "%i", childId);
            strcat(parentStr, childIdStr);
            strcat(parentStr, " who returned partial sum ");
            strcat(parentStr, readStr);
        }
        
        
    }
    strcat(parentStr, " which has a total sum of ");
    char totalStr[10] = { 0 };
    sprintf(totalStr, "%i", total);
    strcat(parentStr, totalStr);
    printf("%s\n", parentStr);
    exit(0);
}