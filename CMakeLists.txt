cmake_minimum_required(VERSION 3.20)
project(WordGame
        VERSION 0.0.2
        LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(makeWordList makeWordList.c)
target_sources(makeWordList PRIVATE treeWithUniqueChars.c)

add_executable(WordGame wordGame.c)



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wordDatabase.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})