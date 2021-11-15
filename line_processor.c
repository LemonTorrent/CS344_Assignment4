#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>



// Size variables
size_t bufsize = 1000;
int arrsize = 1000;
int printsize = 80;

// 2 dimensional arrays:
char buffer1[50][1000];
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;

char buffer2[50][1000];
// Initialize the mutex for buffer 2
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 2
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;


char buffer3[50][1000];

// Strings to replace
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

pthread_mutex_t arr1Mutex;
pthread_mutex_t arr2Mutex;
pthread_mutex_t arr3Mutex;


/*
 * Function that gets input from user
*/

void getInput(){
    

    char temp[1000];
    char *t = temp;

    bool first = true;

    // Get input from user
    // 
    characters = getline(&t,&arrsize,stdin);

    // Repeat until user types STOP on a newline
    while (strcmp(t, "STOP\n") != 0) {
        // printf("%zu characters were read.\n",characters);
        // printf("You typed: '%s'\n",temp);

        // If this isn't the first iteration, lock arr1
        if (first != true) {
            pthread_mutex_lock(&arr1Mutex);
        }
        

        // Copy the contents of buffer1 to temp
        strcpy(buffer1[endBuf1], temp);
        // printf("Buffer: '%s'\n", buffer1[endBuf1]);

        // increment the index by 1
        endBuf1 = (endBuf1 + 1) % bufsize;

        // unlock the array
        pthread_mutex_unlock(&arr1Mutex);

        // get another line of input from the user
        characters = getline(&t,&arrsize,stdin);
        first = false;
    }

    // Lock arr1, set last line of input to -1 to signal end of file.
    pthread_mutex_lock(&arr1Mutex);
    strcpy(buffer1[endBuf1], "-1\n");
    endBuf1 = (endBuf1 + 1) % bufsize;
    pthread_mutex_unlock(&arr1Mutex);

    ending = true;

    //printf("\n");

    return;
}

/*
 * Function that replaces newline with a space
*/
void removeSep(){
    


    bool continueSep = true;
    char temp [arrsize];
    bool first = true;

    // while (startBuf1 < endBuf1){
    while (continueSep == true) {

        // copy contents of buffer 1
        
        // strcpy(buffer2[endBuf2], buffer1[startBuf1]);
        // printf("Startbuf1 = %i\n", startBuf1);
        // printf("Thred 2 accessing buffer 1\n");

        // lock array 1
        pthread_mutex_lock(&arr1Mutex);
        strcpy(temp, buffer1[startBuf1]);
        
        // clear line that was read
        memset(buffer1[startBuf1], 0, sizeof(buffer1[startBuf1]));

        // increment index by 1
        startBuf1 = (startBuf1 + 1) % bufsize;
        pthread_mutex_unlock(&arr1Mutex);

        // printf("Copied string: %s\n", temp);
        temp[strlen(temp) - 1] = ' ';

        // if this isn't the first time running, lock arr2
        if (first != true) {
            pthread_mutex_lock(&arr2Mutex);
        }

        // copy replaced line to arr2
        strcpy(buffer2[endBuf2], temp);
        // increment by 1
        endBuf2 = (endBuf2 + 1) % bufsize;
        pthread_mutex_unlock(&arr2Mutex);

        first = false;

        // found end of file, change variable to exit function
        if (strcmp(temp, "-1 ") == 0) {
            // printf("MUST END!\n");
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

/*
 * Function to replace a string with another string
 * Credit: https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
*/
char * replaceWord(const char* s, const char* oldW, const char* newW) {
    char initial [arrsize];
    char result [arrsize];
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // set index to 0
    i = 0;
    // while there are still characters in the string:
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            // copy contents
            strcpy(&result[i], newW);

            // increment indexes
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    // set end of string to null char
    result[i] = '\0';

    return result;
}

/*
 * Replaces plus signs with carrot symbols
*/
void replacePlus(){

    char initial [arrsize];
    bool contReplacePlus = true;
    bool first = true;

    // continue while the -1 line hasn't been found
    while (contReplacePlus == true) {
        
        // Lock arr2 to copy contents into local string
        pthread_mutex_lock(&arr2Mutex);
        strcpy(initial, buffer2[startBuf2]);

        if (strcmp(initial, "") != 0){
            startBuf2 = (startBuf2 + 1) % 50;
        }
        
        pthread_mutex_unlock(&arr2Mutex);
    

        //if (first == false){
            //pthread_mutex_lock(&arr3Mutex);
        //}

        if (strcmp(initial, "") != 0) {
            // Lock arr3 if this isn't the first time using loop
            if (first == false) {
                pthread_mutex_lock(&arr3Mutex);
            }

            // copy replaced word version into arr3
            strcpy(buffer3[endBuf3], replaceWord(initial, c, d));
            endBuf3 = (endBuf3 + 1) % 50;
            

            
            pthread_mutex_unlock(&arr3Mutex);

            // If the line is -1, return because we have reached the end of the file

            if (strcmp(initial, "-1 ") == 0) {
                // printf("MUST END REPLACE PLUS!\n");
                contReplacePlus = false;
                return;

            }

            first = false;
            //NULL;
        }


        

        // printf("In buf3: '%s'\n", buffer3[endBuf3]);

        //pthread_mutex_unlock(&arr3Mutex);

        
    }

    return;
}

/*
 * Print strings of length 80
*/
void printString() {

    

    char temp [arrsize];
    char printLine [printsize + 10];
    char extra [printsize];

    int curr = 0;
    int currPrint = 0;
    int templen;
    bool foundEnd = false;

    // Lock arrary 3, copy to local string
    pthread_mutex_lock(&arr3Mutex);
    strcpy(temp, buffer3[startBuf3]);
    // clear string contents
    memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
    // increment index or arr3
    startBuf3 += 1 % 50;
    pthread_mutex_unlock(&arr3Mutex);

    templen = strlen(temp);
    

    // Clear the line that we will print
    memset(printLine, 0, sizeof(printLine));

    
    // while we haven't found the end of the file
    while (foundEnd == false) {
        // copy character by character
        printLine [currPrint] = temp[curr];
        // increment each index by 1
        curr += 1;
        currPrint += 1;
        // If the string has 80 characters, set end of string to null, print line, then clear contents of line
        if (currPrint % 80 == 0) {
            printLine [currPrint] = '\0';
            printf("%s\n", printLine);
            memset(printLine, 0, sizeof(printLine));
            currPrint = 0;
        }

        if (curr >= templen) {
            // 
            // get new line from arr3
            pthread_mutex_lock(&arr3Mutex);
            
            //printf("Printing buffer\n");
            //for (int i = 0; i < endBuf2; i++){
            //    printf("%s\n", buffer2[i]);
           // }
            //  copy string to local variable, clear string in buffer and incement index by 1
            strcpy(temp, buffer3[startBuf3]);
            memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
            startBuf3 += 1 % 50;

            pthread_mutex_unlock(&arr3Mutex);
            

            // If you find line with -1
            if (strcmp(temp, "-1 ") == 0) {
                // indicate we found end of file
                foundEnd = true;
                //return;
            }

            
            
            // get length of the string to pring
            
            templen = strlen(temp);
            curr = 0;
        }
    }

    printf("\n");

    // printf("After print string\n");
    

    // printf("Printline: '%s'\n", printLine);
}

/*
 * calls the first thread's functionality
*/
void *thread1(void *args) {
    pthread_mutex_lock(&arr1Mutex);
    //printf("Inside thread 1\n");
    getInput();

    //printf("Ending thread 1\n");

    return NULL;
}

/*
 * calls the second thread's functionality
*/
void *thread2(void *args) {

    pthread_mutex_lock(&arr2Mutex);

    //printf("Inside thread 2");
    removeSep();
    //printf("Ending thread 2\n");

    return NULL;
}

/*
 * calls the third thread's functionality
*/
void *thread3(void *args) {
    pthread_mutex_lock(&arr3Mutex);

    //printf("Inside thread 3");
    replacePlus();
    //printf("Ending thread 3\n");

    return NULL;
}

/*
 * calls the fourth thread's functionality
*/
void *thread4(void *args) {
    // pthread_mutex_lock(&arr3Mutex);

    //printf("Inside thread 4");
    printString();
    //printf("Ending thread 4\n");

    return NULL;
}

int main(int argc, char *argv[])
{

    // Don't need to handle input. linux does this on its own.

    ending = false;
    startBuf1 = 0;
    endBuf1 = 0;

    startBuf2 = 0;
    endBuf2 = 0;

    startBuf3 = 0;
    endBuf3 = 0;

    startBuf4 = 0;
    endBuf4 = 0;

    pthread_t input_t, remove_sep_t, rep_plus_t, output_t;
    // Create the threads

    
    pthread_create(&input_t, NULL, thread1, NULL);
    
    pthread_create(&remove_sep_t, NULL, thread2, NULL);
    pthread_create(&rep_plus_t, NULL, thread3, NULL);
    pthread_create(&output_t, NULL, thread4, NULL);

    // get the threads after they have finsihed functionality
    pthread_join(input_t, NULL);
    pthread_join(remove_sep_t, NULL);
    pthread_join(rep_plus_t, NULL);

    
    pthread_join(output_t, NULL);

    // printf("Printing buffer\n");
    // for (int i = 0; i < endBuf2; i++){
    //    printf("%s\n", buffer2[i]);
    // }

    

    // printString();
    // replacePlus();
    // printString();

    return 0;
}