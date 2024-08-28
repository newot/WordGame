#include <gtest/gtest.h>

#include "allFunctions_treeWithUniqueChars.h"

//runningCount should be removed because it tests for specific implementation, maybe stringLength too
TEST(splitStringToChar, BasicFunctionalityTest){
    char* inputString = (char*)"aäq";
    char* outputString = (char*)malloc(8*sizeof(char));
    int stringLength = 3;
    int runningCount = 0;

    // First Character
    splitStringToChar(inputString, outputString, &stringLength, &runningCount);
    EXPECT_TRUE(strcmp(inputString, (char*)"aäq") == 0);
    EXPECT_TRUE(strcmp(outputString, (char*)"a") == 0);
    EXPECT_EQ(stringLength, 3);
    EXPECT_EQ(runningCount, 1);

    // Second Character
    splitStringToChar(inputString, outputString, &stringLength, &runningCount);
    EXPECT_TRUE(strcmp(inputString, (char*)"aäq") == 0);
    EXPECT_TRUE(strcmp(outputString, (char*)"ä") == 0);
    EXPECT_EQ(stringLength, 3);
    EXPECT_EQ(runningCount, 3);

    // Third Character
    splitStringToChar(inputString, outputString, &stringLength, &runningCount);
    EXPECT_TRUE(strcmp(inputString, (char*)"aäq") == 0);
    EXPECT_TRUE(strcmp(outputString, (char*)"q") == 0);
    EXPECT_EQ(stringLength, 3);
    EXPECT_EQ(runningCount, 4);
}

//Should be removed because it tests for a specific implementation, not functionality
TEST(binaryTree, CreateRootNode){
    struct  rootNode* root = createRootNode("a");

    EXPECT_EQ((*root).treeSize, 1);
    EXPECT_EQ((*(*root).node).left, nullptr);
    EXPECT_EQ((*(*root).node).right, nullptr);
    EXPECT_TRUE(strcmp((*(*root).node).data, (char*)"a") == 0);

    freeBinaryTree(root);
}


TEST(binaryTree, Input_Output_binaryTree){
    struct  rootNode* root = createRootNode((char*)"c");
    char *allChars = (char*)malloc(11*sizeof(char));

    // test insert and sorted output
    searchAndInsertString(root, (char*)"a", 2);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a c") == 0);

    // test adding more letters
    std::string str("b");
    searchAndInsertString(root, str.c_str(), 2);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a b c") == 0);

    // test adding words
    searchAndInsertString(root, (char*)"zum", 4);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a b c m u z") == 0);

    // test duplicate characters
    searchAndInsertString(root, (char*)"zu", 3);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a b c m u z") == 0);

    // test special characters
    searchAndInsertString(root, (char*)"nö", 1);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a b c m n u z ö") == 0);

    // test if multiwide characters with the same first 8 bits are seperated
    searchAndInsertString(root, (char*)"mäw", 1);
    getAllCharsFromBinaryTree(root, allChars);
    EXPECT_TRUE(strcmp(allChars, (char*)" a b c m n u w z ä ö") == 0);

    freeBinaryTree(root);
    free(allChars);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}