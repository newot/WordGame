 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>
 #include <ctype.h>

 static int commentLength = 43;

//Replaces chars specified in specialChars with whatever is in replacementChars. Only works for 2-wide multi-characters and 2 characters
 void _replaceAllSpecialChars(char* singleWord, int specialChars[], char *replacementChars[], int numberOfReplacementChars){
    char* result;
    for(int i=0;i<numberOfReplacementChars;i++){
        do{
            result = strchr(singleWord, specialChars[i]);
            if(result != NULL){
                *result = replacementChars[i][1];
                *(result-1) = replacementChars[i][0];
            }
        }while(result!=NULL);
    }
}

//Copies the first commentLength chars over to the new file. Intended for legal information etc.
void _copyComments(FILE *output, FILE *wordDatabase, int commentLength){
    for(int i=0;i<commentLength;i++){
        char singleWord[128] = "";
        fgets(singleWord, 128, wordDatabase);
        fprintf(output, singleWord);
    }
}

void makeWordList(int numberOfCharacters){
    FILE *wordDatabase;
    FILE *output;

    output = fopen("output.txt", "w");
    wordDatabase = fopen("wordDatabase.txt", "r");

    _copyComments(output, wordDatabase, commentLength);

    char singleWord[128];
    while (fscanf(wordDatabase, "%s", singleWord)!=EOF) {
        if(strlen(singleWord) == numberOfCharacters){
            singleWord[0] = tolower(singleWord[0]);
            int numberOfReplacementChars = 7;
            //replacing the following chars. The 2 rows bellow are equivalent for UTF-8
            //int specialChars[] = {'ß', 'ö', 'ü', 'ä', 'Ö', 'Ü', 'Ä'};
            int specialChars[] = {-97, -74, -68, -92, -106, -100, -124};
            char *replacementChars[] = {"ss", "oe", "ue","ae", "oe", "ue","ae"};
            _replaceAllSpecialChars(singleWord, specialChars, replacementChars, numberOfReplacementChars);
            //writing word to file
            fprintf(output, singleWord);
            fprintf(output, "\n");
        }
        //skipping all of the unneeded data after the word
        char throwaway[128];
        fgets(throwaway, 128, wordDatabase);
    }

    fclose(output);
    fclose(wordDatabase); 
}

int main(int argc, char *argv[]) {
    printf("Number of Characters:");
    int inputNumber = 0;
    scanf("%i", &inputNumber);
    printf("Result is in output.txt\n");

    makeWordList(inputNumber);
}