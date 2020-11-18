cmake_minimum_required(VERSION 3.17)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project4
        .idea/workspace.xml
        .gitignore
        History.hpp
        History_Transaction_definitions.cpp
        main.cpp
        project4.cpp
        project4.hpp
        Transaction.hpp
        transaction_history.txt)
