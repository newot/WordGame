#ifndef treeWithUniqueChars_H_
#define treeWithUniqueChars_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

struct _binaryTreeNode
{
    char* data;
    struct _binaryTreeNode* left;
    struct _binaryTreeNode* right;
};

struct rootNode
{
    int treeSize;
    struct _binaryTreeNode* node;
};

struct rootNode* createRootNode(const char* data);
void freeBinaryTree(struct rootNode* root);
void getAllCharsFromBinaryTree(struct rootNode* root, char* allChars);
void searchAndInsertString(struct rootNode* root, const char* inputString, int numberOfCharacters);
void splitStringToChar(const char *inputString, char* outputString, int* stringLength, int*runningCount);  

#endif