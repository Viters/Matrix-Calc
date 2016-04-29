cmake_minimum_required(VERSION 3.3)
project(Matrix_Calc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    aghException.cpp
    aghException.h
    aghComplex.cpp
    aghComplex.h
    aghInclude.h
    aghMatrix.cpp
    aghMatrix.h
    ex2main.cpp)

add_executable(Matrix_Calc ${SOURCE_FILES})