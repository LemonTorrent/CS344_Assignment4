#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


char *buffer;
size_t bufsize = 100;
size_t characters;
char c[] = "++";
char d[] = "^";
    


void getInput(){


    printf("Type something: ");
    characters = getline(&buffer,&bufsize,stdin);
    printf("%zu characters were read.\n",characters);
    printf("You typed: '%s'\n",buffer);
    return;
}

void removeSep(){
    buffer[strcspn(buffer, "\n")] = 0;

    return;
}

// Function to replace a string with another
// string
char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    
    char* result;
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
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
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
    return result;
}

void replacePlus(){
    /*char temp [bufsize];
    char replacement [] = "^";
    bool isOnEnd = false;

    // copy buffer into temp
    strcpy(temp, buffer);

    printf("Temps %s\n", temp);
    memset(buffer,0,sizeof(buffer));

    if (temp[0] == '+' && temp[1] == '+'){
        strcat(buffer, replacement);
    }

    if (temp[strlen(temp) - 1] == '+' && temp[strlen(temp) - 2] == '+') {
        isOnEnd = true;
    }

    char * token = strtok(temp, "++");
    printf("Token: %s\n", token);
    while (token != NULL){
        strcat(buffer, token);
        
        token = strtok(NULL, "++");
        if (token != NULL) {
            strcat(buffer, replacement);
        }
    }

    if (isOnEnd == true) {
        strcat(buffer, replacement);
    }

    */
    

    return;
}

int main(int argc, char *argv[])
{
    /*printf("Num args %d\n", argc);
    if (argc >= 2)
    {
        printf("Usage: ./main num_items\n");
        printf("\tTaking file as input\n");
      
    } else if (argc == 1){
        printf("Taking command line as input\n");
    }
    */

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }


    // Don't need to handle input. linux does this on its own.
    char* result;

    result = (char *)malloc(bufsize * sizeof(char));

    getInput();

    printf("In main\n");

    printf("You typed: '%s'\n",buffer);

    removeSep();

    printf("After buffer: '%s'\n",buffer);

    // replacePlus();
    result = replaceWord(buffer, c, d);


    printf("Original string should be replaced: %s\n", result);

    return 0;
}