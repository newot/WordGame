 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <stdbool.h>

static int charCharakterCount = 5;
static int COMMENT_LENGTH = 43;

//Counting how many lines the document has
int countLines(int* wordCount){
    FILE *wordList;
    wordList = fopen("output.txt", "r");
    char singleWord[128];
    while(fgets(singleWord, 128, wordList)) {
        (*wordCount)++;
    }
    fclose(wordList);
}

//Skiping potential comment above wordList for FILE stream
void skipComment(FILE *wordList, int commentLength){
    for(int i=0;i<commentLength+1;i++){
        char singleWord[128];
        fgets(singleWord, 128, wordList);
    }
}

//Get a random word
void findRandomWord(char randomWord[128], int wordCount, FILE *wordList){
    srand(time(NULL)); 
    int randomNumber = (rand() % wordCount);
    for(int i=0; i<randomNumber; i++){
        fgets(randomWord, 128, wordList);
    }
    fgets(randomWord, 128, wordList);
}

void checkInput(char randomWord[128], char guessedWord[128], int *amountCorrectPositionCharakters, int *amountCorrectCharakters){
    //randomWordCopy is used to remove letters that are already accounted for
    //This is done to avoid counting multiple of the same letters twice
    char *randomWordCopy = strndup(randomWord, charCharakterCount);

    //How many letters are on the correct position
    for(int j=0; j<charCharakterCount; j++){
        if(guessedWord[j] == randomWord[j]){
            (*amountCorrectPositionCharakters)++;
            randomWordCopy[j] = '.';
        }
    }

    //How many letters are in the word, but not on the correct position
    for(int j=0; j<charCharakterCount; j++){
        char* search = strchr(randomWordCopy, guessedWord[j]);
        if(search != NULL){
            (*amountCorrectCharakters)++;
            *search = '.';
        }
    }
}

int main(int argc, char *argv[]) {
    if(charCharakterCount > 128 || charCharakterCount < 1){
        printf("charCharakterCount out of bounds");
    }

    //Figure out wordCount
    int wordCount = 0;
    countLines(&wordCount);
    wordCount = wordCount - COMMENT_LENGTH;
    if(wordCount<1){
        printf("Zu wenige Worte der Länge %i vorhanden", charCharakterCount);
        return 0;
    }

    //Prepare wordList
    FILE *wordList;
    wordList = fopen("output.txt", "r");
    if(wordList == NULL){
        printf("Error: Cannot find file: %s\n", wordList);
        exit(1);
    }
    char randomWord[128];
    skipComment(wordList, COMMENT_LENGTH);
    findRandomWord(randomWord, wordCount, wordList);
    fclose(wordList);

    //Main gameloop
    printf("Erate das Wort: \n");
    for(int i=0; i<10; i++){
        printf("%i/10\n", i+1);
        char guessedWord[128] = "";
        while (strlen(guessedWord) != charCharakterCount)
        {
            scanf("%s", guessedWord);
        }

        int amountCorrectPositionCharakters = 0;
        int amountCorrectCharakters = 0;
        checkInput(randomWord, guessedWord, &amountCorrectPositionCharakters, &amountCorrectCharakters);
        
        //Printing information and ending the game if guessed word is correct
        if(amountCorrectPositionCharakters == charCharakterCount){
            printf("Du hast das richtige Wort eraten!");
            i=10;
        }
        else{
            printf("%i Buchstaben sind richtig\n", amountCorrectPositionCharakters);
            printf("%i Buchstaben sind fast richtig\n", amountCorrectCharakters);
        }
    }
    printf("Das Wort war: %s", randomWord);
}