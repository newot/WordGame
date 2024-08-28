#include "makeWordList.h"




//copy specific chars from src to dest. Chars to be copied are specified from beginningSrc to endSrc. Chars will be copied to position starting from destIterator
void _copyOverFrom(char *dest, char *src, int *destIterator, int beginningSrc, int endSrc){
    for(int i = beginningSrc;i<endSrc;i++){
        dest[*destIterator] = src[i];
        (*destIterator)++;
    }
}

//Replaces chars specified in toBeSubstituted with whatever is in replacementChars.
//WARNING: Make sure singleWord has WORD_MAX_CHAR_COUNT memory allocated!!! TODO fixme
void subsituteCharacters(char *singleWord, char *toBeSubstituted[], char *replacementChars[], int numberOfCharsToBeSubstituted){
    char* result;
    for(int i=0;i<numberOfCharsToBeSubstituted;i++){
        do{
            //Checking if character needs to and can be substituted
            result = strstr(singleWord, toBeSubstituted[i]);
            if(result != NULL){
                if(strlen(singleWord) > (WORD_MAX_CHAR_COUNT + strlen(toBeSubstituted[i]) - strlen(replacementChars[i] - 1))){
                    printf("Warning: %s is to long for substitution and will be dropped\n", singleWord);
                    singleWord = "";
                    return;
                }
                //Make Character Substitution by copying till toBeSubstituted[], then copying the replacement, then copying starting after toBeSubstituted[]
                char singleWordUnedited[WORD_MAX_CHAR_COUNT];
                strcpy(singleWordUnedited, singleWord);
                int destIterator = 0;
                if(result - singleWord > 0){
                    _copyOverFrom(singleWord, singleWordUnedited, &destIterator, 0, result - singleWord);
                }
                int d = destIterator + strlen(toBeSubstituted[i]);
                _copyOverFrom(singleWord, replacementChars[i], &destIterator, 0, strlen(replacementChars[i]));
                if(destIterator > WORD_MAX_CHAR_COUNT && destIterator < 0){
                    printf("something went wrong while substituting");
                    exit(1);
                }
                _copyOverFrom(singleWord, singleWordUnedited, &destIterator, d, WORD_MAX_CHAR_COUNT-destIterator);               
            }
        }while(result != NULL);
    }
}

void _checkSubsituteCharactersInput(char *toBeSubstituted[], char *replacementChars[], int numberOfCharsToBeSubstituted){
    char* replacementCharsInSingleString = malloc(128);
    for(int i = 0; i < numberOfCharsToBeSubstituted; i++){
        strcat(replacementCharsInSingleString, replacementChars[i]);
    }
    for(int i = 0; i < numberOfCharsToBeSubstituted; i++){
        char* problemChar = strchr(replacementCharsInSingleString, *(toBeSubstituted[i]));
        if(problemChar != NULL){
            printf("replacement char and char to be Substituted are the same: INFINITE LOOP");
            exit(1);
        }
    }
    free(replacementCharsInSingleString);
}



// Copies comments over to new file. 
bool _checkIfAndCopyComment(FILE *output, char* singleWord){
    if(singleWord[0]=='#'){
        fprintf(output, singleWord);
        return true;
    }
    return false;
}

bool _excludeWord(char* singleWord, char *excludedChars[], int numberOfCharsToBeExcluded){
    for(int i=0; i<numberOfCharsToBeExcluded; i++){
        char* excludedCharFound = strstr(singleWord, excludedChars[i]);
        if(excludedCharFound != NULL){
            return true;
        }
    }
    return false;
}

void _tolowerString(char* singleWord, int wordLength){
    int i = 0;
    while(i < wordLength || singleWord[i] != '\0'){
        singleWord[i] = tolower(singleWord[i]);
        i++;
    }
}

int makeWordList(int numberOfCharacters, char *outputWordlist){
    if(numberOfCharacters > WORD_MAX_CHAR_COUNT - 2){
        printf("Error: Code does not support character counts above %i\n", WORD_MAX_CHAR_COUNT - 2);
        exit(1);
    }
    if(numberOfCharacters < 1){
        printf("Error: Code does not support character counts below 1\n");
        exit(1);
    }
    
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

    fprintf(output, "This is a modified version only including words that are %i characters long!\n", numberOfCharacters);

    char *line;
    size_t lineLength = WORD_MAX_CHAR_COUNT;
    size_t getlineReturnValue;

    line = (char *)malloc(lineLength * sizeof(char));
    if(line == NULL){
        printf("malloc could not alocate space");
        exit(1);
    }

    struct rootNode* root = createRootNode("o");
    
    while((getlineReturnValue = getline(&line, &lineLength, inputWordlist)) != -1) {

        if(_checkIfAndCopyComment(output, line)){
            continue;
        }
        
        char* singleWord = strtok(line, " ");
       
        if(singleWord == NULL) {
            continue;
        }

        int numberOfCharsToBeExcluded = 6;
        char *excludedChars[] = {",", "/", "-", "(", ")", "\n"};
        if(_excludeWord(singleWord, excludedChars, numberOfCharsToBeExcluded)){
            continue;
        }

        _tolowerString(singleWord, lineLength);

        int numberOfCharsToBeSubstituted = 13;
        //replacing the following chars. tolower does not lower "Ä", "Ö", "Ü"
        char *toBeSubstituted[] = {"ß", "ö", "ü", "ä", "Ö", "Ü", "Ä", "é", "è", "ê", "ç", "î", "ó"};
        char *replacementChars[] = {"ss", "oe", "ue","ae", "oe", "ue","ae", "e", "e", "e", "c", "i", "o"};
        //TODO insert error if toBeSubstituted/replacementChars unequal to numberOfCharsToBeSubstituted

        subsituteCharacters(singleWord, toBeSubstituted, replacementChars, numberOfCharsToBeSubstituted);

        searchAndInsertString(root, singleWord, WORD_MAX_CHAR_COUNT);

        if(strlen(singleWord) == numberOfCharacters){
            //writing word to file
            fprintf(output, singleWord);
            fprintf(output, "\n");
        }
    }

    if (line != NULL) {
        free(line);
    }

    char* allChars = malloc(2 * (*root).treeSize * sizeof(char));
    allChars[0] = '\0';
    getAllCharsFromBinaryTree(root, allChars);
    fprintf(output, "!%s",allChars);
    //printf("Every char included in Dataset: %s\n", allChars);

    free(allChars);
    freeBinaryTree(root);

    fclose(output);
    fclose(inputWordlist); 
    return 0;
}