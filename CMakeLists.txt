cmake_minimum_required(VERSION 3.27)
project(DA2324_PRJ1_G07_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA2324_PRJ1_G07_3 code/main.cpp
        data_structures/Graph.h
        code/DataReader.cpp
        code/DataReader.h
        code/WaterNetwork.cpp
)
