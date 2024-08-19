 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdlib.h>

struct binaryTreeNode
{
    char* data;
    struct binaryTreeNode* left;
    struct binaryTreeNode* right;
};

struct binaryTreeNode* createBinaryTreeNode(char* data, int* treeSize){
    struct binaryTreeNode* newNode = malloc(sizeof(struct binaryTreeNode));
    (*newNode).data = (char *) malloc(100);
    strcpy((*newNode).data, data);
    (*newNode).left = NULL;
    (*newNode).right = NULL;
    (*treeSize)++;
    return newNode;
}

void freeBinaryTree(struct binaryTreeNode* root){
    if((*root).left != NULL){
        freeBinaryTree((*root).left);
        free((*root).left);
    }
    if((*root).right != NULL){
        freeBinaryTree((*root).right);
        free((*root).right);
    }
    free((*root).data);
}

void searchAndInsertChar(struct binaryTreeNode* root, char* data, int* treeSize){
    if(strcmp((*root).data, data) > 0){
        if((*root).left == NULL){
            (*root).left = createBinaryTreeNode(data, treeSize);
        }
        else{
            searchAndInsertChar((*root).left, data, treeSize);
        }
    }
    else if(strcmp((*root).data, data) < 0){
        if((*root).right == NULL){
            (*root).right = createBinaryTreeNode(data, treeSize);
        }
        else{
            searchAndInsertChar((*root).right, data, treeSize);
        }
    }
}

void getAllCharsFromBinaryTree(struct binaryTreeNode* root, char* allChars){
    if((*root).left != NULL){
        getAllCharsFromBinaryTree((*root).left, allChars);        
    }
    strcat(allChars, ((*root).data));
    if((*root).right != NULL){
        getAllCharsFromBinaryTree((*root).right, allChars);    
    }
}

void _splitStringToChar(char *inputString, char* outputString, int* stringLength, int*runningCount){    
    int k = 0;
    while(((inputString[*runningCount] | 0b00111111) & 0b11111111) == 0b11111111){
        outputString[k] = inputString[*runningCount];
        *stringLength--;
        (*runningCount)++;
        k++;
    }
    outputString[k] = inputString[*runningCount];
    outputString[k+1] = '\0';
    (*runningCount)++;
}

void testSplitStringToChar(){
    char* inputString = "äa";
    char* outputString = malloc(sizeof(char));
    int stringLength = 3;
    int runningCount = 0;
    printf("splitString");
    char* temp = "äa";
    int f = temp[0];
    _splitStringToChar(inputString, outputString, &stringLength, &runningCount);
    printf("ä:%s\n", outputString);
    _splitStringToChar(inputString, outputString, &stringLength, &runningCount);
    printf("a:%s\n", outputString);
    free(outputString);
}

void searchAndInsertString(struct binaryTreeNode* root, char* inputString, int numberOfCharacters, int* treeSize){
    int newNumberOfCharacters = numberOfCharacters;
    int runningCount = 0;
    while(inputString[runningCount] != '\0'){
        char singleWordChars[numberOfCharacters];
        _splitStringToChar(inputString, singleWordChars, &newNumberOfCharacters, &runningCount);
        searchAndInsertChar(root, singleWordChars, treeSize);
    }
}           

//#####################################################################################

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
                if(strlen(singleWord) > (WORD_MAX_CHAR_COUNT + strlen(toBeSubstituted[i]) - strlen(replacementChars[i] - 1))){
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

int makeWordList(int numberOfCharacters){
    if(numberOfCharacters > WORD_MAX_CHAR_COUNT - 2){
        printf("Error: Code does not support character counts above %i\n", WORD_MAX_CHAR_COUNT - 2);
        exit(1);
    }
    if(numberOfCharacters < 1){
        printf("Error: Code does not support character counts below 1\n");
        exit(1);
    }

    static char* outputWordlist = "output.bin";
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

    //_copyComments(output, inputWordlist, COMMENT_LENGTH);

    char *line;
    size_t lineLength = WORD_MAX_CHAR_COUNT;
    size_t getlineReturnValue;

    line = (char *)malloc(lineLength * sizeof(char));
    if(line == NULL){
        printf("Error malloc");
        exit(1);
    }

    int treeSize = 0;
    struct binaryTreeNode* root = createBinaryTreeNode("o", &treeSize);
    
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

        _subsituteCharacters(singleWord, toBeSubstituted, replacementChars, numberOfCharsToBeSubstituted);

        searchAndInsertString(root, singleWord, WORD_MAX_CHAR_COUNT, &treeSize);

        if(strlen(singleWord) == numberOfCharacters){
            //writing word to file
            fprintf(output, singleWord);
            fprintf(output, "\n");
        }
    }

    if (line != NULL) {
        free(line);
    }

    char* allChars = malloc(treeSize * sizeof(char));
    allChars[0] = '\0';
    getAllCharsFromBinaryTree(root, allChars);
    printf("Every char included in Dataset: %s\n", allChars);
    free(allChars);
    freeBinaryTree(root);

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

    //testSplitStringToChar();

    return 0;
}