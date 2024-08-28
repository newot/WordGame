#include "treeWithUniqueChars.h"

//creates a generic tree node
struct _binaryTreeNode* _createBinaryTreeNode(const char* data, int* treeSize){
    struct _binaryTreeNode* newNode = malloc(sizeof(struct _binaryTreeNode));
    if(newNode == NULL){
        printf("malloc could not alocate space");
        exit(1);
    }
    (*newNode).data = (char *) malloc(sizeof(char) * WORD_MAX_CHAR_COUNT);
    if((*newNode).data == NULL){
        printf("malloc could not alocate space");
        exit(1);
    }
    strcpy((*newNode).data, data);
    (*newNode).left = NULL;
    (*newNode).right = NULL;
    (*treeSize)++;
    return newNode;
}

//creates a root node
struct rootNode* createRootNode(const char* data){
    struct rootNode* newNode = malloc(sizeof(struct rootNode));
    if(newNode == NULL){
        printf("malloc could not alocate space");
        exit(1);
    }
    (*newNode).treeSize = 0;
    (*newNode).node = _createBinaryTreeNode(data, &(*newNode).treeSize);
    return newNode;
}

//frees memory alocated by tree
void _freeBinaryTreeRekursivee(struct _binaryTreeNode* node){
    if((*node).left != NULL){
        _freeBinaryTreeRekursivee((*node).left);
        free((*node).left);
    }
    if((*node).right != NULL){
        _freeBinaryTreeRekursivee((*node).right);
        free((*node).right);
    }
    free((*node).data);
}

void freeBinaryTree(struct rootNode* root){
    _freeBinaryTreeRekursivee((*root).node);
    free(root);
}

//returns every char stored in binaryTree
void _getAllCharsFromBinaryTreeNode(struct _binaryTreeNode* node, char* allChars){
    if((*node).left != NULL){
        _getAllCharsFromBinaryTreeNode((*node).left, allChars);        
    }
    char* charPlusSpace = malloc(sizeof((*node).data + 1));
    if(charPlusSpace == NULL){
        printf("malloc could not allocate space");
    }
    sprintf(charPlusSpace, " %s",((*node).data));
    strcat(allChars, charPlusSpace);
    free(charPlusSpace);
    if((*node).right != NULL){
        _getAllCharsFromBinaryTreeNode((*node).right, allChars);    
    }
}

void getAllCharsFromBinaryTree(struct rootNode* root, char* allChars){
    allChars[0] = '\0';
    _getAllCharsFromBinaryTreeNode((*root).node, allChars);
}

//Inserts char into tree if char is not already in tree
void _searchAndInsertChar(struct _binaryTreeNode* root, char* data, int* treeSize){
    if(strcmp((*root).data, data) > 0){
        if((*root).left == NULL){
            (*root).left = _createBinaryTreeNode(data, treeSize);
        }
        else{
            _searchAndInsertChar((*root).left, data, treeSize);
        }
    }
    else if(strcmp((*root).data, data) < 0){
        if((*root).right == NULL){
            (*root).right = _createBinaryTreeNode(data, treeSize);
        }
        else{
            _searchAndInsertChar((*root).right, data, treeSize);
        }
    }
}

//ONLY USE THIS FUNCTION STARTING FROM runningCount = 0.  Iterates runningCount itself. Returns char on position runningCount. Supports multibyte chars
void splitStringToChar(const char *inputString, char* outputString, int* stringLength, int*runningCount){    
    int k = 0;
    while(((inputString[*runningCount] | 0b00111111) & 0b11111111) == 0b11111111){
        outputString[k] = inputString[*runningCount];
        *stringLength--;
        (*runningCount)++;
        k++;
        if(k > (WORD_MAX_CHAR_COUNT - 2)){
            printf("inputString is to long");
        }
    }
    outputString[k] = inputString[*runningCount];
    outputString[k+1] = '\0';
    (*runningCount)++;
    if((*runningCount) > (WORD_MAX_CHAR_COUNT)){
        printf("inputString is to long");
    }
}

//Split of chars from an inputString and stores unique chars in a binary tree
void searchAndInsertString(struct rootNode* root, const char* inputString, int numberOfCharacters){
    int newNumberOfCharacters = numberOfCharacters;
    int runningCount = 0;
    while(inputString[runningCount] != '\0'){
        char singleWordChars[numberOfCharacters];
        splitStringToChar(inputString, singleWordChars, &newNumberOfCharacters, &runningCount);
        _searchAndInsertChar((*root).node, singleWordChars, &((*root).treeSize));
    }
}    