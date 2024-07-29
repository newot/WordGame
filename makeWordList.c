 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>
 #include <ctype.h>

 static int commentLength = 43;

//Replaces chars specified in specialChars with whatever is in replacementChars. Only works for 2-wide multi-characters and 2 characters
 void replaceAllSpecialChars(char* singleWord, int specialChars[], char *replacementChars[], int numberOfChars){
    char* result;
    for(int i=0;i<numberOfChars;i++){
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
void copyComments(FILE *output, FILE *wordDatabase, int commentLength){
    for(int i=0;i<commentLength;i++){
        char singleWord[128] = "";
        fgets(singleWord, 128, wordDatabase);
        fprintf(output, singleWord);
    }
}

int main(int argc, char *argv[]) {
    printf("Number of Characters:");
    int inputnumber = 0;
    scanf("%i", &inputnumber);
    printf("Result is in output.txt\n");

    FILE *wordDatabase;
    FILE *output;

    output = fopen("output.txt", "w");
    wordDatabase = fopen("wordDatabase.txt", "r");

    copyComments(output, wordDatabase, commentLength);

    char singleWord[128];
    while(fgets(singleWord, 128, wordDatabase)) {
        bool isInputNumberLong = true;
        int i = inputnumber;
        //We figure out if the word has the correct length by looking for word separetor (' ')
        if(singleWord[i]!=' '){
            isInputNumberLong = false;
        }
        i--;
        while(i>0 && isInputNumberLong){
            if(singleWord[i]==' '){
                isInputNumberLong = false;
            }
            i--;
        }
        if(isInputNumberLong){
            singleWord[0] = tolower(singleWord[0]);
            int numberOfChars = 7;
            //replacing the following chars. The 2 rows bellow are equivalent for UTF-8
            //int specialChars[] = {'ß', 'ö', 'ü', 'ä', 'Ö', 'Ü', 'Ä'};
            int specialChars[] = {-97, -74, -68, -92, -106, -100, -124};
            char *replacementChars[] = {"ss", "oe", "ue","ae", "oe", "ue","ae"};
            replaceAllSpecialChars(singleWord, specialChars, replacementChars, numberOfChars);
            
            //only copying the word to the new file, not extra information
            char firstNLettersFromString[inputnumber+1];
            for(int i=0; i<inputnumber; i++){
                firstNLettersFromString[i] = singleWord[i];
            }
            firstNLettersFromString[inputnumber] = '\n';
            fprintf(output, firstNLettersFromString);
            
        }
    }
    fclose(output);
    fclose(wordDatabase); 
}