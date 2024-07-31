 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdlib.h>

 static int COMMENT_LENGTH = 43;
 static size_t WORD_MAX_CHAR_COUNT = 128;
 static char *INPUT_WORDLIST = "wordDatabase.txt";

//copy specific chars from src to dest. Chars to be copied are specified from beginningSrc to endSrc. Chars will be copied to position starting from destIterator
 void _copyOverFrom(char *dest, char *src, int *destIterator, int beginningSrc, int endSrc){
    for(int i = beginningSrc;i<endSrc;i++){
        dest[*destIterator] = src[i];
        (*destIterator)++;
    }
}

//Replaces chars specified in toBeSubstituted with whatever is in replacementChars.
 void _subsituteCharacters(char *singleWord, char *toBeSubstituted[], char *replacementChars[], int numberOfCharsToBeSubstituted){
    char* result;
    for(int i=0;i<numberOfCharsToBeSubstituted;i++){
        do{
            //Checking if character needs to and can be substituted
            result = strstr(singleWord, toBeSubstituted[i]);
            if(result != NULL){
                if(strlen(singleWord)>WORD_MAX_CHAR_COUNT - strlen(replacementChars[i] - 1)){
                    printf("Warning: %s is to long for substitution and will be dropped\n", singleWord);
                    singleWord = "";
                    return;
                }
                //Make Character Substitution by copying till toBeSubstituted[], then copying the replacement, then copying starting after toBeSubstituted[]
                char singleWordUnedited[WORD_MAX_CHAR_COUNT];
                strcpy(singleWordUnedited, singleWord);
                int destIterator = 0;
                _copyOverFrom(singleWord, singleWordUnedited, &destIterator, 0, result - singleWord);
                int d = destIterator + strlen(toBeSubstituted[i]);
                _copyOverFrom(singleWord, replacementChars[i], &destIterator, 0, strlen(replacementChars[i]));
                _copyOverFrom(singleWord, singleWordUnedited, &destIterator, d, WORD_MAX_CHAR_COUNT-destIterator);
            }
        }while(result!=NULL);
    }
}

//Copies the first commentLength chars over to the new file. Intended for legal information etc.
void _copyComments(FILE *output, FILE *inputWordlist, int commentLength){
    for(int i=0;i<commentLength;i++){
        char singleWord[128] = "";
        fgets(singleWord, 128, inputWordlist);
        fprintf(output, singleWord);
    }
}

int makeWordList(int numberOfCharacters){
    if(numberOfCharacters > WORD_MAX_CHAR_COUNT - 2){
        printf("Error: Code does not support character counts above %i\n", WORD_MAX_CHAR_COUNT - 2);
        exit(1);
    }
    if(numberOfCharacters < 1){
        printf("Error: Code does not support character counts below 1\n");
        exit(1);
    }

    static char* outputWordlist = "output.txt";
    FILE *inputWordlist;
    FILE *output;

    output = fopen(outputWordlist, "w");
    if(output == NULL){
        printf("Error: Cannot create file: %s\n", outputWordlist);
        exit(1);
    }

    inputWordlist = fopen(INPUT_WORDLIST, "r");
    if(inputWordlist == NULL){
        printf("Error: Cannot find file: %s\n", INPUT_WORDLIST);
        exit(1);
    }

    _copyComments(output, inputWordlist, COMMENT_LENGTH);

    char *line;
    size_t lineLength = 32;
    size_t getlineReturnValue;

    line = (char *)malloc(lineLength * sizeof(char));
    if(line == NULL){
        printf("Error malloc");
        exit(1);
    }
    
    while ((getlineReturnValue = getline(&line, &lineLength, inputWordlist)) != -1) {
        
        char* singleWord = strtok(line, " ");
       

        if (singleWord == NULL) {
            continue;
        }

        singleWord[0] = tolower(singleWord[0]);

        int numberOfCharsToBeSubstituted = 8;
        //replacing the following chars. The 2 rows bellow are equivalent for UTF-8
        char *toBeSubstituted[] = {"ß", "ö", "ü", "ä", "Ö", "Ü", "Ä", "é"};
        char *replacementChars[] = {"ss", "oe", "ue","ae", "oe", "ue","ae", "e"};
        //TODO insert error if toBeSubstituted/replacementChars unequal to numberOfCharsToBeSubstituted
        //TODO add all characters that need to be substituted

        _subsituteCharacters(singleWord, toBeSubstituted, replacementChars, numberOfCharsToBeSubstituted);

        if(strlen(singleWord) == numberOfCharacters){
            //writing word to file
            fprintf(output, singleWord);
            fprintf(output, "\n");
        }

        //skipping all of the unneeded data after the word
        
    }

    if (line != NULL) {
        free(line);
    }

    fclose(output);
    fclose(inputWordlist); 
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Number of Characters:");
    int inputNumber = 0;
    scanf("%i", &inputNumber);
    
    makeWordList(inputNumber);
    printf("Result is in output.txt\n");

    return 0;
}