#ifndef treeWithUniqueChars_H_
#define treeWithUniqueChars_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rootNode
{
    int treeSize;
    struct _binaryTreeNode* node;
};

struct rootNode* createRootNode(char* data);
void freeBinaryTree(struct rootNode* root);
void getAllCharsFromBinaryTree(struct rootNode* root, char* allChars);
void searchAndInsertString(struct rootNode* root, char* inputString, int numberOfCharacters);

#endif