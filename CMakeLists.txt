cmake_minimum_required(VERSION 3.28)
project(WordGame
        VERSION 0.0.2
        LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
add_executable(makeWordList makeWordList.c)
add_executable(WordGame wordGame.c)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wordDatabase.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})