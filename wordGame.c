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

int main(int argc, char *argv[]) {
    //Figure out wordCount
    int wordCount = 0;
    countLines(&wordCount);
    wordCount = wordCount - COMMENT_LENGTH;
    if(wordCount<1){
        printf("Zu wenige Worte der Länge vorhanden");
        return 0;
    }

    //Prepare wordList
    FILE *wordList;
    wordList = fopen("output.txt", "r");
    char randomWord[128];
    skipComment(wordList, COMMENT_LENGTH);

    //Get a random word
    srand(time(NULL)); 
    int randomNumber = (rand() % wordCount);
    for(int i=0; i<randomNumber; i++){
        fgets(randomWord, 128, wordList);
    }
    fgets(randomWord, 128, wordList);
    fclose(wordList);

    //Main gameloop
    printf("Erate das Wort: \n");
    for(int i=0; i<10; i++){
        printf("%i/10\n", i+1);
        char guessedWord[128];
        scanf("%s", guessedWord);
        //randomWordCopy is used to remove letters that are already accounted for
        //This is done to avoid counting multiple of the same letters twice
        char *randomWordCopy = strndup(randomWord, charCharakterCount); 
        //How many letters are on the correct position
        int amountCorrectPositionCharakters = 0;
        for(int j=0; j<charCharakterCount; j++){
            if(guessedWord[j] == randomWord[j]){
                amountCorrectPositionCharakters++;
                randomWordCopy[j] = '.';
            }
        }
        //How many letters are in the word, but not on the correct position
        int amountCorrectCharakters = 0;
        for(int j=0; j<charCharakterCount; j++){
            char* search = strchr(randomWordCopy, guessedWord[j]);
            if(search != NULL){
                amountCorrectCharakters++;
                *search = '.';
            }
        }
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