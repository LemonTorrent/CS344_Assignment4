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


void getInput(){
    

    char temp[1000];
    char *t = temp;

    bool first = true;

    printf("Type something. Input will end when you type '-1' on its own line, then hit enter: ");
    characters = getline(&t,&arrsize,stdin);

    while (strcmp(t, "STOP\n") != 0) {
        // printf("%zu characters were read.\n",characters);
        printf("You typed: '%s'\n",temp);

        if (first != true) {
            pthread_mutex_lock(&arr1Mutex);
        }
        

        strcpy(buffer1[endBuf1], temp);
        // printf("Buffer: '%s'\n", buffer1[endBuf1]);

        endBuf1 = (endBuf1 + 1) % bufsize;

        pthread_mutex_unlock(&arr1Mutex);


        characters = getline(&t,&arrsize,stdin);
        first = false;
    }

    pthread_mutex_lock(&arr1Mutex);
    strcpy(buffer1[endBuf1], "-1\n");
    endBuf1 = (endBuf1 + 1) % bufsize;
    pthread_mutex_unlock(&arr1Mutex);

    ending = true;

    printf("\n");

    return;
}

void removeSep(){
    


    bool continueSep = true;
    char temp [arrsize];
    bool first = true;

    // while (startBuf1 < endBuf1){
    while (continueSep == true) {
        // copy contents of buffer 1
        // strcpy(buffer2[endBuf2], buffer1[startBuf1]);
        // printf("Startbuf1 = %i\n", startBuf1);
        printf("Thred 2 accessing buffer 1\n");

        pthread_mutex_lock(&arr1Mutex);
        strcpy(temp, buffer1[startBuf1]);
        
        // printf("Buffer1 arr %i: '%s'\n", startBuf1, buffer1[startBuf1]);
        memset(buffer1[startBuf1], 0, sizeof(buffer1[startBuf1]));
        startBuf1 = (startBuf1 + 1) % bufsize;
        pthread_mutex_unlock(&arr1Mutex);

        printf("Copied string: %s\n", temp);
        temp[strlen(temp) - 1] = ' ';


        if (first != true) {
            pthread_mutex_lock(&arr2Mutex);
        }
        strcpy(buffer2[endBuf2], temp);
        // printf("Buffer2 arr %i: '%s'\n", endBuf2, buffer2[endBuf2]);
        endBuf2 = (endBuf2 + 1) % bufsize;
        pthread_mutex_unlock(&arr2Mutex);

        first = false;

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

    // printf("Result of replacement = '%s'\n", result);
    // endBuf3 = (endBuf3 + 1) % 50;

    return result;
    // return result;
}

void replacePlus(){

    char initial [arrsize];
    bool contReplacePlus = true;
    bool first = true;

    // while (startBuf2 < endBuf2) {
    while (contReplacePlus == true) {
        pthread_mutex_lock(&arr2Mutex);
        strcpy(initial, buffer2[startBuf2]);
        startBuf2 = (startBuf2 + 1) % 50;
        pthread_mutex_unlock(&arr2Mutex);
    
        if (first == false) {
            pthread_mutex_lock(&arr3Mutex);
        }
        strcpy(buffer3[endBuf3], replaceWord(initial, c, d));
        endBuf3 = (endBuf3 + 1) % 50;
        pthread_mutex_unlock(&arr3Mutex);

        if (strcmp(initial, "-1 ") == 0) {
            // printf("MUST END REPLACE PLUS!\n");
            contReplacePlus = false;

        }

        first = false;

        // printf("In buf3: '%s'\n", buffer3[endBuf3]);

        
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

    // printf("\n\n starting print string: \n\n");

    char temp [arrsize];
    char printLine [printsize + 10];
    char extra [printsize];

    int curr = 0;
    int currPrint = 0;
    int templen;
    bool foundEnd = false;

    pthread_mutex_lock(&arr3Mutex);
    strcpy(temp, buffer3[startBuf3]);
    memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
    startBuf3 += 1 % 50;
    pthread_mutex_unlock(&arr3Mutex);

    templen = strlen(temp);
    // printf("Buffer 3 '%s'\n", temp);

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

    // printf("Start buf3 %i, end buf3 %i\n", startBuf3, endBuf3);

    // printf("Starting print line '%s'\n", printLine);
    // while (curr < templen) {
    // while (startBuf3 <= endBuf3) {
    while (foundEnd == false) {
        // printf("%c", temp[curr]);
        printLine [currPrint] = temp[curr];
        // printf("%c\n", temp[curr]);
        curr += 1;
        currPrint += 1;
        // printf("Line: '%s', num %i\n\n", printLine, currPrint);
        if (currPrint % 80 == 0) {
            printLine [currPrint] = '\0';
            printf("%s\n", printLine);
            memset(printLine, 0, sizeof(printLine));
            currPrint = 0;
        }

        if (curr >= templen) {
            // printf("Getting new line from buffer\n");
            // get new line
            pthread_mutex_lock(&arr3Mutex);
            strcpy(temp, buffer3[startBuf3]);
            memset(buffer3[startBuf3], 0, sizeof(buffer3[startBuf3]));
            startBuf3 += 1 % 50;
            pthread_mutex_unlock(&arr3Mutex);

            // printf("Temp = '%s'\n", temp);
            if (strcmp(temp, "-1 ") == 0) {
                // printf("MUST END PRINTING!\n");
                foundEnd = true;
                return;
            }
            
            // printf("Buffer = '%s'\n", buffer3[startBuf3]);
            
            templen = strlen(temp);
            curr = 0;
        }
    }

    printf("\n");

    // printf("After print string\n");
    

    // printf("Printline: '%s'\n", printLine);
}

void *thread1(void *args) {
    pthread_mutex_lock(&arr1Mutex);
    printf("Inside thread 1\n");
    getInput();

    printf("Ending thread 1\n");

    return NULL;
}

void *thread2(void *args) {

    pthread_mutex_lock(&arr2Mutex);

    printf("Inside thread 2");
    removeSep();
    printf("Ending thread 2\n");

    return NULL;
}

void *thread3(void *args) {
    pthread_mutex_lock(&arr3Mutex);

    printf("Inside thread 3");
    replacePlus();
    printf("Ending thread 3\n");

    return NULL;
}

void *thread4(void *args) {
    // pthread_mutex_lock(&arr3Mutex);

    printf("Inside thread 4");
    printString();
    printf("Ending thread 4\n");

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

    // getInput();
    pthread_create(&input_t, NULL, thread1, NULL);
    
    pthread_create(&remove_sep_t, NULL, thread2, NULL);
    pthread_create(&rep_plus_t, NULL, thread3, NULL);
    pthread_create(&output_t, NULL, thread4, NULL);


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