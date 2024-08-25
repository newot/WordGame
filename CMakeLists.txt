cmake_minimum_required(VERSION 3.20)
project(WordGame
        VERSION 0.0.2
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

# GoogleTest import copied from: https://google.github.io/googletest/quickstart-cmake.html
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(makeWordList ./src/makeWordList.c)
target_sources(makeWordList PRIVATE ./src/treeWithUniqueChars.c)

add_executable(WordGame ./src/wordGame.c)

# Testing
enable_testing()

add_executable(test_treeWithUniqueChars ./unittest/test_treeWithUniqueChars.cpp)
target_sources(test_treeWithUniqueChars PRIVATE ./src/treeWithUniqueChars.c)
target_link_libraries(test_treeWithUniqueChars GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_treeWithUniqueChars)



#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wordDatabase.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})