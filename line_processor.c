#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>




size_t bufsize = 1000;
int arrsize = 1000;
int printsize = 80;
char buffer1[50][1000];
char buffer2[50][1000];
char buffer3[50][1000];

size_t characters;
char c[] = "++";
char d[] = "^";

int startBuf1;
int endBuf1;

int startBuf2;
int endBuf2;

int startBuf3;
int endBuf3;

int startBuf4;
int endBuf4;

bool ending;


void getInput(){

    char temp[1000];
    char *t = temp;

    printf("Type something: ");
    characters = getline(&t,&arrsize,stdin);

    while (strcmp(t, "STOP\n") != 0) {
        printf("%zu characters were read.\n",characters);
        printf("You typed: '%s'\n",temp);

        strcpy(buffer1[endBuf1], temp);
        printf("Buffer: '%s'\n", buffer1[endBuf1]);

        endBuf1 = (endBuf1 + 1) % bufsize;

        characters = getline(&t,&arrsize,stdin);

    }

    strcpy(buffer1[endBuf1], "-1\n");
    endBuf1 = (endBuf1 + 1) % bufsize;

    ending = true;

    return;
}

void removeSep(){

    bool continueSep = true;
    char temp [arrsize];

    // while (startBuf1 < endBuf1){
    while (continueSep == true) {
        // copy contents of buffer 1
        // strcpy(buffer2[endBuf2], buffer1[startBuf1]);
        printf("Startbuf1 = %i\n", startBuf1);
        strcpy(temp, buffer1[startBuf1]);
        printf("Buffer1 arr %i: '%s'\n", startBuf1, buffer1[startBuf1]);
        memset(buffer1[startBuf1], 0, sizeof(buffer1[startBuf1]));
        startBuf1 = (startBuf1 + 1) % bufsize;

        temp[strlen(temp) - 1] = ' ';
        strcpy(buffer2[endBuf2], temp);
        printf("Buffer2 arr %i: '%s'\n", endBuf2, buffer2[endBuf2]);
        endBuf2 = (endBuf2 + 1) % bufsize;

        if (strcmp(temp, "-1 ") == 0) {
            printf("MUST END!\n");
            continueSep = false;
        }
        
        // clear contents of string in buffer 1
        // memset(buffer1[startBuf1], 0, sizeof(buffer1[startBuf1]));
        
        

        

        

        
        

        
        // printf("Finding length %i\n", strlen(buffer2[endBuf2]));
        // int length = strlen(buffer2[endBuf2]);
        // printf("Finding char: %c\n", buffer2[endBuf2][1]);

        // buffer2[endBuf2][strlen(buffer2[endBuf2]) - 1] = ' ';

        // printf("Buffer2 arr %i: '%s'\n", startBuf2, buffer2[endBuf2]);

        // endBuf2 = (endBuf2 + 1) % bufsize;
    }

    return;
}

// Function to replace a string with another
// string
// Credit: https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
char * replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char initial [arrsize];
    char result [arrsize];
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    // result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';

    // strcpy(buffer3[endBuf3], result);

    //printf("Result of replacement = '%s'\n", result);

    //printf("In buf3: '%s'\n", buffer3[endBuf3]);

    printf("Result of replacement = '%s'\n", result);
    // endBuf3 = (endBuf3 + 1) % 50;

    return result;
    // return result;
}

void replacePlus(){

    char initial [arrsize];
    bool contReplacePlus = true;

    // while (startBuf2 < endBuf2) {
    while (contReplacePlus == true) {
        strcpy(initial, buffer2[startBuf2]);
        startBuf2 = (startBuf2 + 1) % 50;
    

        strcpy(buffer3[endBuf3], replaceWord(initial, c, d));

        if (strcmp(initial, "-1 ") == 0) {
            printf("MUST END REPLACE PLUS!\n");
            contReplacePlus = false;

        }

        printf("In buf3: '%s'\n", buffer3[endBuf3]);

        endBuf3 = (endBuf3 + 1) % 50;
    }

    return;
}


/*
Algorithm:

1. Check if temp has more than 80 char.
2. If not, copy from buffer 3 to temp.
3. 

1. copy line from buffer
2. copy up to 80 char to print line, print
3. repeat until printline has less than 80 char
4. get another line from buffer

*/
void printString() {

    printf("\n\n starting print string: \n\n");

    char temp [arrsize];
    char printLine [printsize + 10];
    char extra [printsize];

    int curr = 0;
    int currPrint = 0;
    int templen;

    strcpy(temp, buffer3[startBuf3]);
    memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
    startBuf3 += 1 % 50;
    templen = strlen(temp);
    printf("Buffer 3 '%s'\n", temp);

    //if (strlen(temp) < printsize){
    //    printf("Less than\n");
    //    strcpy()
    //}

    //while (templen - curr > printsize) {
        /*
        printf("Iterating through string\n");
        strncpy(printLine, temp + curr, 40);
        printf("'%s'\n", printLine);

        curr += 80;
        */
    //}
    memset(printLine, 0, sizeof(printLine));

    printf("Start buf3 %i, end buf3 %i\n", startBuf3, endBuf3);

    printf("Starting print line '%s'\n", printLine);
    // while (curr < templen) {
    while (startBuf3 <= endBuf3) {
        // printf("%c", temp[curr]);
        printLine [currPrint] = temp[curr];
        // printf("%c\n", temp[curr]);
        curr += 1;
        currPrint += 1;
        // printf("Line: '%s', num %i\n\n", printLine, currPrint);
        if (currPrint % 80 == 0) {
            printLine [currPrint] = '\0';
            printf("Final Print Line: '%s'\n\n", printLine);
            memset(printLine, 0, sizeof(printLine));
            currPrint = 0;
        }

        if (curr >= templen) {
            printf("Getting new line from buffer\n");
            // get new line
            strcpy(temp, buffer3[startBuf3]);
            printf("Temp = '%s'\n", temp);
            if (strcmp(temp, "-1 ") == 0) {
                printf("MUST END PRINTING!\n");
                return;
            }
            memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
            printf("Buffer = '%s'\n", buffer3[startBuf3]);
            startBuf3 += 1 % 50;
            templen = strlen(temp);
            curr = 0;
        }
    }

    printf("\n");

    printf("After print string\n");
    

    // printf("Printline: '%s'\n", printLine);
}

int main(int argc, char *argv[])
{

    // Don't need to handle input. linux does this on its own.

    ending = false;

    getInput();

    

    printf("Buffer in main: '%s'\n", buffer1[startBuf1]);
    printf("Buffer in main: '%s'\n", buffer1[startBuf1 + 1]);
    printf("Buffer in main: '%s'\n", buffer1[startBuf1 + 2]);

    removeSep();

    printf("Buffer in main: '%s'\n", buffer2[startBuf2]);
    printf("Buffer in main: '%s'\n", buffer2[startBuf2 + 1]);
    printf("Buffer in main: '%s'\n", buffer2[startBuf2 + 2]);

    // printf(buffer1);

    replacePlus();

    printf("Printing buffer\n");
    for (int i = 0; i < endBuf3; i++){
        printf("%s\n", buffer3[i]);
    }

    printString();

    return 0;

    removeSep();

    return 0;

    printf("In main\n");

    printf("You typed: '%s'\n",buffer1[0]);

    removeSep();

    printf("After buffer: '%s'\n",buffer1[0]);

    // replacePlus();
    // result = replaceWord(buffer, c, d);


    // printf("Original string should be replaced: %s\n", result);

    startBuf1 = 0;
    endBuf1 = 0;

    startBuf2 = 0;
    endBuf2 = 0;

    startBuf3 = 0;
    endBuf3 = 0;

    startBuf4 = 0;
    endBuf4 = 0;

    return 0;
}