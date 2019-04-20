cmake_minimum_required(VERSION 3.13)
project(tp3)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} src/inf3105.cpp src/DocumentXML.cpp src/Histoire.cpp src/Phrase.cpp src/graphe.h)