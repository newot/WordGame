#ifndef treeWithUniqueChars_H_
#define treeWithUniqueChars_H_

extern "C"{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//Non accesible Functions
struct _binaryTreeNode* _createBinaryTreeNode(const char* data, int* treeSize);
void _freeBinaryTreeRekursivee(struct _binaryTreeNode* node);
void _getAllCharsFromBinaryTreeNode(struct _binaryTreeNode* node, char* allChars);
void _searchAndInsertChar(struct _binaryTreeNode* root, char* data, int* treeSize);
void _splitStringToChar(const char *inputString, char *outputString, int *stringLength, int *runningCount);
}

#endif