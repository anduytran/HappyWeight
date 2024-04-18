cmake_minimum_required(VERSION 3.24)
project(HappyWeight)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(HappyWeight
        src/hashmap.h
        src/main.cpp src/trie.h)
