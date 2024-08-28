#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "makeWordList.h"
#include "options.h"

// Linux exclusive!
#include <sys/stat.h>
#include <sys/types.h>

#define DirectoryName "res"
//%s = DirectoryName
//%i = character length
#define FileName "%s/wordDatabase_with_words_sizeof(%i)"

//Counting how many lines the document has
int getInfoAboutWordlist(int *wordCount, char *outputWordlist, char *allChars){
    FILE *wordList;
    wordList = fopen(outputWordlist, "r");
    if(wordList == NULL){
        printf("Error: Cannot find file: %s\n", *outputWordlist);
        exit(1);
    }
    char singleWord[WORD_MAX_CHAR_COUNT];
    singleWord[0] = '\0';
    while(singleWord[0] != '!') {
        fgets(singleWord, WORD_MAX_CHAR_COUNT, wordList);
        (*wordCount)++;
    }
    strcpy(allChars, singleWord);
    char* toBeSubstituted[] = {"! "};
    char* replacementChars[] = {" "};
    subsituteCharacters(allChars, toBeSubstituted, replacementChars, 1);
    if(fclose(wordList)){
        printf("could not close wordList");
    }
}

//Skiping potential comment above wordList for FILE stream
void skipComment(FILE *wordList, int commentLength){
    for(int i=0;i<commentLength+1;i++){
        char singleWord[WORD_MAX_CHAR_COUNT];
        fgets(singleWord, WORD_MAX_CHAR_COUNT, wordList);
    }
}

bool isComment(char *randomWord){
    if(randomWord[0] == '#'){
        return true;
    }
    return false;
}

//Get a random word
void findRandomWord(char randomWord[WORD_MAX_CHAR_COUNT], int wordCount, FILE *wordList){
    srand(time(NULL)); 
    int randomNumber = (rand() % wordCount);
    for(int i=0; i<randomNumber; i++){
        fgets(randomWord, WORD_MAX_CHAR_COUNT, wordList);
    }
    fgets(randomWord, WORD_MAX_CHAR_COUNT, wordList);
}

bool InputIsNotAllowed(char guessedWord[WORD_MAX_CHAR_COUNT], char* allChars, int numberOfCharacters){
    int runningCount = 0;
    while(guessedWord[runningCount] != '\0'){
        int newNumberOfCharacters = numberOfCharacters;
        char guessedWordChar[8];
        splitStringToChar(guessedWord, guessedWordChar, &newNumberOfCharacters, &runningCount);
        if(strstr(allChars, guessedWordChar) == NULL){
            return true;
        }
    }
    return false;
}

void checkInput(char randomWord[WORD_MAX_CHAR_COUNT], char guessedWord[WORD_MAX_CHAR_COUNT], int *amountCorrectPositionCharakters, int *amountCorrectCharakters, int charCharakterCount){
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
    printf("Number of Characters:");
    int charCharakterCount = 0;
    scanf("%i", &charCharakterCount);
    if(charCharakterCount > WORD_MAX_CHAR_COUNT || charCharakterCount < 1){
        printf("charCharakterCount out of bounds");
        exit(1);
    }
    char* outputWordlist = malloc(200);
    sprintf(outputWordlist, FileName, DirectoryName, charCharakterCount);

    struct stat sb;
    if(stat(DirectoryName, &sb) == -1){
        mkdir(DirectoryName, 0700);
    }else{
        if((sb.st_mode & S_IFMT) != S_IFDIR){
            //i could create a directory but currently i do not know if some files have edge cases where fstream does not work TODO (maybe. it is such a nieche case that i might not care enough)
            printf("Cannot create wordlist folder because a different file with the same name is in the working directory\n");
            exit(1);
        }
    }
    if(stat(outputWordlist, &sb) == -1){
        makeWordList(charCharakterCount, outputWordlist);
    }

    //Figure out wordCount
    int wordCount = 0;
    //I should fix this malloc Word_max_char_count is only used because it is required by substitudeCharacters 
    char* allChars = malloc(WORD_MAX_CHAR_COUNT);
    getInfoAboutWordlist(&wordCount, outputWordlist, allChars);
    if(wordCount<1){
        printf("Zu wenige Worte der Länge %i vorhanden", charCharakterCount);
        return 0;
    }

    //Prepare wordList
    char randomWord[WORD_MAX_CHAR_COUNT];
    do{
        FILE *wordList;
        wordList = fopen(outputWordlist, "r");
        if(wordList == NULL){
            printf("Error: Cannot find file: %s\n", wordList);
            exit(1);
        }
        findRandomWord(randomWord, wordCount, wordList);
        fclose(wordList);
    }while (isComment(randomWord));
    free(outputWordlist);

    printf("Every Character allowed:%s\n", allChars);
    //Main gameloop
    printf("Erate das Wort: \n");
    for(int i=0; i<10; i++){
        printf("%i/10\n", i+1);
        char guessedWord[WORD_MAX_CHAR_COUNT] = "";
        while (strlen(guessedWord) != charCharakterCount || InputIsNotAllowed(guessedWord, allChars, charCharakterCount))
        {
            scanf("%s", guessedWord);
        }

        int amountCorrectPositionCharakters = 0;
        int amountCorrectCharakters = 0;
        checkInput(randomWord, guessedWord, &amountCorrectPositionCharakters, &amountCorrectCharakters, charCharakterCount);
        
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
    free(allChars);
}