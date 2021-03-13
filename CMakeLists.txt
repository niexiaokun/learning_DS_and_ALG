cmake_minimum_required(VERSION 3.15)
project(learning_DS_and_ALG)

set(CMAKE_CXX_STANDARD 11)

add_executable(advancedSort advancedSort.cpp)
add_executable(SegmentTree SegmentTree.cpp)
add_executable(gradient_descent gradient_descent.cpp)
add_executable(trie trie.cpp)

add_executable(knn knn.cpp)