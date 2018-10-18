cmake_minimum_required(VERSION 3.12)
project(avm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses -I/usr/local/Cellar/ncurses")
include_directories(incs)
link_directories(/usr/local/Cellar/ncurses)
add_executable(avm
        incs/avm/AvmController.hpp
        incs/avm/AvmModels.hpp
        incs/avm/AvmParser.hpp
        incs/avm/AvmView.hpp
        incs/avm.hpp
        incs/AvmException.hpp
        incs/IOperand.hpp
        incs/MutantStack.hpp
        incs/Operand.hpp
        srcs/avm/AvmController.cpp
        srcs/avm/AvmModels.cpp
        srcs/avm/AvmParser.cpp
        srcs/avm/AvmView.cpp
        srcs/AvmException.cpp
        srcs/main.cpp)
