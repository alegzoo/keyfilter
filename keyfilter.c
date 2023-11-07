//xmarina00

/*
Hi,
The programme you've just opened is emulation of the virtual keyboard in navigation-like system when searching for the address in search bar.
This algorithm let's you easily display only those characters, which are present in the database (no matter the size) after providing
wanted address */

/* Compile as: $ gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter */
/* Run as: ./keyfilter (lettersToLookFor) <database.txt */

/*________________________________________

USED LIBRARIES */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*________________________________________*/


/* FUNCTION FOR ASSIGNING ptrNumCheck A VALUE, WHICH DETERMINES WHAT WILL BE PRINTED AS A RESULT IN main */
void fillingNumCheck(int ASCII_SIZE, int enableOccurrence[], int *ptrNumCheck) {

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (enableOccurrence[i] != 0) {
            *ptrNumCheck = *ptrNumCheck + enableOccurrence[i];
        }
    }

}

/* FUNCTION FOR SORTING ARRAYS */
void sortAlphabetically(char arrayToSort[], int sizeOfArray) {

    int tempVar = 0;

    for (int j = 0; j < sizeOfArray; j++) {
        for (int i = 1 + j; i < sizeOfArray; i++) {
            if ((arrayToSort[j] > arrayToSort[i]) && (j != i)) {
                tempVar = arrayToSort[j];
                arrayToSort[j] = arrayToSort[i];
                arrayToSort[i] = tempVar;
            }
        }
    }

}

void wordCheck(int readLineSize, char foundWord[], char readLine[], int *ptrHasWord) {

    /* PROGRAMME GETS HERE, WHEN BEING CALLED BY THE FUNCTION compareAddressAndInput() WHEN IT DISCOVERS THAT IT
       CAN ENABLE SOME KEY ON KEYBOARD AND THEREFORE IT SHOULD STORE WORD THAT'S THE CLOSEST TO IT */

    for (int i = 0; i < readLineSize; i++) {
        foundWord[i] = readLine[i];
    }

    /* DECREMENTING *ptrHasWord VARIBALE AS A SIGN THAT THE PROGRAMME HAS STORED WORD CLOSEST TO THE INPUTTED ARGUMENT (USED LATER IN main) */
    (*ptrHasWord)--;
}

/* FUNCTION FOR ADDING KEYS (CHARACTERS) TO THE ARRAY enable AND enableOccurrence THAT CAN BE ENABLED */
void fillEnableKeysArray(char enable[], int userInputSize, char readLine[], int *ptrPositionEnable, int enableOccurrence[], int STARTING_POINT) {

    int enableLength = strlen(enable);
    int ixOccurence = readLine[userInputSize] - STARTING_POINT;
    int flag = 0;

    /* WHEN THERE IS AT LEAST 1 CHARACTER ENABLED CHECK IF THE CHARACTER THAT WILL BE STORED IN enable ARRAY ISN'T ALREADY
       PRESENT, IF THE CHARACTER IS PRESENT IN THE enable ARRAY, RAISE A FLAG VALUE BY 1 AS A SIGN THAT IT SHOULD ONLY 
       INCREASE THE VALUE IN THE enableOccurrence ARRAY, ON THE INDEX WHERE IT STORES THE NUMBER OF DUPLICTES OF THAT CHARACTER */

    if (enableLength != 0) {
        for (int i = 0; i < enableLength; i ++) {
            if ((readLine[userInputSize] == enable[i]) && (readLine[userInputSize] != '\n')) {
                flag = 1;
            }
        }


        if (flag == 0) {
            enable[*ptrPositionEnable] = readLine[userInputSize];
            (*ptrPositionEnable)++;
            (enableOccurrence[ixOccurence])++;

        } else {
            (enableOccurrence[ixOccurence])++;
        }

    /* IF THE enable ARRAY HAS A LENGTH OF 1, ADD CHOSEN CHARACTER TO THE ARRAY AND ALSO STORE IT'S OCCURRENCE IN enableOccurrence ARRAY */
    } else {
        enable[*ptrPositionEnable] = readLine[userInputSize];
        (*ptrPositionEnable)++;
        (enableOccurrence[ixOccurence])++;
    }
    

}

/* FUNCTION FOR COMPARING ADDRESS FROM DATABASE AND INPUT */ 
void compareAddressAndInput(char readLine[], char *argv[], int *ptrPositionEnable, int userInputSize, char enable[], int readLineSize, char foundWord[], int enableOccurrence[], int *ptrHasWord, int STARTING_POINT) {

    int flag = 0;

    /* ITERATING OVER THE READ LINE AND USER'S INPUT. WHEN THE CHARACTERS ARE NOT EQUAL IT WILL
    RAISE FLAG VALUE BY 1 AS THE SIGN THAT IT CAN'T ENABLE KEY FOR THAT PARTICULAR ADDRESS */

    for(int i = 0; i < userInputSize; i++) {

        printf("i: %d inputSize %d strlen(readLine) %lu\n", i, userInputSize, strlen(readLine));
        if (readLine[i] != argv[1][i]) {
            flag++;
            break;
        }

    }

    if (flag == 0) {

        /* CALLING FUNCTION FOR ADDING NEXT CHARACTER AS ENABLE-KEY */ 
        fillEnableKeysArray(enable, userInputSize, readLine, ptrPositionEnable, enableOccurrence, STARTING_POINT);

        /* CALLING FUNCTION FOR ASSIGNING THE CLOSEST MATCH TO THE READ LINE */
        wordCheck(readLineSize, foundWord, readLine, ptrHasWord);
        
    }

}

/* emptyInput FUNCTION IS CALLED WHEN THERE IS NO INPUT BY THE USER, JUST DATABASE
   PROVIDED OR THE ADRESSES AND SEARCHED WORD TO THE TERMINAL. IT'S PURPOSE IS TO ENABLE
   ALL FIRST-LETTERS THAT OCCUR IN THE DATABASE */
void emptyInput(char adress[], char enable[], int *ptrPositionEnable, int maxLineLength, int diffAscii) {

    int target = ' ';

    while(fgets(adress, maxLineLength, stdin) != NULL) {

        /* WE DON'T WANT TO ENABLE CHARACTERS THAT OCCUR MORE THAN ONCE SO BY SETTING OUR TARGET AND CALLING
           strchr() FUNCTION WE MAKE SURE THAT EVERY CHARACTER THAT IS PRESENT IN THE DATABASE OCCURS ONLY ONCE */

        if (('a' <= adress[0]) && (adress[0] <= 'z')) {
            target = (adress[0] - diffAscii);
        } else {
            target = adress[0];
        }

        if ((*ptrPositionEnable) == 0) {
            enable[*ptrPositionEnable] = target;
            (*ptrPositionEnable)++;

        } else {

            /* BY USING strchr() FUNCTION, WE ARE TRYING TO FIND THE (FIRST) OCCURENCE OF THAT CHARACTER IN THE enable ARRAY 
               IF WE DON'T FIND ANY OCCURENCE, WE CAN STORE THE CHARACTER INTO enable ARRAY */

            if (strchr(enable, target) == NULL) {
                enable[*ptrPositionEnable] = target;
                (*ptrPositionEnable)++;
            }

        }

    }

    sortAlphabetically(enable, strlen(enable));

    printf("Enable: %s\n", enable);  
}

/* FUNCTION FOR TURNING LOWERCASE INTO UPPERCASE */
void toUpperCase(char textProvided[], int textSize, int diffAscii) {

    for(int i = 0; i < textSize; i++) {
        if (('a' <= (textProvided[i]) && (textProvided[i]) <= 'z')) {
            textProvided[i] = textProvided[i] - diffAscii;
        }
    }
}

int main(int argc, char *argv[]) {

    /*
    ------------------------------------------
                Initialization
    ------------------------------------------

    DEFINING CONSTANTS OF THE PROGRAMME */

    #define MAX_LINE_LENGTH 120
    #define ASCII_SIZE 95
    #define STARTING_POINT 32

    /*________________________________________

    CREATING ARRAYS OF CHARACTERS FOR STORING:
    1. Read line from stdin = readLine[]
    2. Allowed keys after the programme runs = enable[]
    3. Found word when there is one enabled key = foundWord[] 
    4. Number of occurrences of characters */

    char readLine[MAX_LINE_LENGTH] = {0};
    char enable[ASCII_SIZE] = {0};
    char foundWord[MAX_LINE_LENGTH] = {0};
    int enableOccurrence[ASCII_SIZE] = {0};

    /*________________________________________

    INITIALIZED FOR MOVING INDEX OF enable[] ARRAY IN THE FUNCTION: fillEnableKeysArray(). */
    int position = 0;
    int *ptrPositionEnable = &position;

    /*________________________________________

    INITIALIZED FOR HAVING A VALUE REPRESENTING DIFFERENCE BETWEEN UPPERCASE AND LOWERCASE. USED IN THE FUNCTION: toUpperCase() */
    int diffAscii = 'a' - 'A';

    /* ________________________________________

    INITIALIZED FOR CHECKING THAT PROGRAMME'S BEEN IN FUNCTION wordCheck() */

    int hasWord = 1;
    int *ptrHasWord = &hasWord;

    /* ________________________________________

    INITIALIZED FOR CHECKING THAT PROGRAMME'S BEEN IN FUNCTION wordCheck() */

    int numCheck = 0;
    int *ptrNumCheck = &numCheck;

    /*-----------------------------------------
    ------------------------------------------*/

    /* CONDITION FOR CHECKING IF A VARIABLE 'argc' (SIZE OF THE ARGUMENTS IN THE COMMAND LINE WHEN 
        STARTED A PROGRAMME) IS MORE THAN 2 IF LESS PRINT EVERY LETTER THAT REPRESENTS SOME ADDRESS IN THE DATABASE*/
    if (argc < 2) {
        emptyInput(readLine, enable, ptrPositionEnable, MAX_LINE_LENGTH, diffAscii);
        return 0;
    }

    /* INITIALIZED readLineSize FOR STORING SIZE OF THE READ LINE FROM PROVIDED DATABASE AND ALSO STORING SIZE OF THE USER'S INPUT IN userInputSize */
    int readLineSize = 0;
    int userInputSize = strlen(argv[1]);

    /* CONVERTING EVERY CHARACTER INPUTTED BY USER TO UPPERCASE */
    

    for (int i = 0; i < userInputSize; i++) {
        if ((('a' <= argv[1][i]) && (argv[1][i] <= 'z')) || ((argv[1][i] <= 'A') && (argv[1][i] <= 'Z'))) {
            toUpperCase(argv[1], userInputSize, diffAscii);
        }
    }

    /* WHILE LOOP FOR ITERATING OVER DATABASE PROVIDED UNTIL FGETS RUNS INTO NULL VALUE */
    while(fgets(readLine, sizeof(readLine), stdin) != NULL) {

        readLineSize = strlen(readLine);

        if (readLineSize > MAX_LINE_LENGTH) {
            fprintf(stderr, "The size of the input is not in range 1 - 100\n");
            return 1;
        }

        /* CONVERTING READ LINE FROM DATABASE TO UPPERCASE */
        for (int i = 0; i < readLineSize; i++) {
            if ((('a' <= readLine[i]) && (readLine[i] <= 'z')) || ((readLine[i] <= 'A') && (readLine[i] <= 'Z'))) {
                toUpperCase(readLine, readLineSize, diffAscii);
            }
        }

        /* CALLING FUNCTION TO COMPARE ADDRESS FROM THE DATABASE AND USER'S INPUT */
        compareAddressAndInput(readLine, argv, ptrPositionEnable, userInputSize, enable, readLineSize, foundWord, enableOccurrence, ptrHasWord, STARTING_POINT);
    }

    fillingNumCheck(ASCII_SIZE, enableOccurrence, ptrNumCheck);

    /* PROGRAMME PRINTS Found: "word" WHEN THERE IS A WORD ASSOCIATED WITH PROVIDED KEY (PPROVIDED MEANS WHEN *ptrHasWord HAS BEEN DECREMENTED IN
    THE FUNCTION wordCheck) AND *ptrNumCheck VARIABLE HAS VALUE OF 1, WHICH HAPPENS WHEN IT IS INCREASED BY 1 WHEN THERE IS ONLY 1
    ENABLED KEY IN THE enableOccurrence FUNCTION */

    if (((*ptrNumCheck == 1) && (*ptrHasWord == 0)) || ((*ptrNumCheck == 0) && (*ptrHasWord == 0))) {
        printf("Found: %s\n", foundWord);

    /* PRINTING enableComplete FUNCTION WHEN *ptrNumCheck VARIABLE HAS BEEN ASSIGNED A VALUE THAT IS LARGER THAN 1, WHICH HAPPENS DURING ITERATION
       OVER enableOccurence WHEN enableOccurrence VALUES ARE SUMMED TOGETHER AND ASSIGNED TO THE *ptrNumCheck VARIABLE. (HAPPENS IN fillingNumCheck FUNCTION) */

    } else if (*ptrNumCheck >= 1) {
        
        char enableComplete[ASCII_SIZE] = {0};
        int enCompMover = 0;
        int enableSize = ASCII_SIZE;

        for (int i = 0; i < enableSize; i++) {
            if (enableOccurrence[i] != 0) {
                enableComplete[enCompMover] = i + STARTING_POINT;
                enCompMover++;
            }
        }

        printf("Enable: %s\n", enableComplete);

    } else {
        printf("Not found\n");
    }

    return 0;
}