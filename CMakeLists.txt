cmake_minimum_required(VERSION 3.12)
project(avm)

set(CMAKE_CXX_STANDARD 14)

include_directories(incs)
include_directories(incs/avm)

add_executable(avm
        incs/avm/AvmController.hpp
        incs/avm/AvmFactory.hpp
        incs/avm/AvmParser.hpp
        incs/avm/AvmView.hpp
        incs/avm.hpp
        incs/AvmException.hpp
        incs/IOperand.hpp
        incs/MutantStack.hpp
        incs/Operand.hpp
        srcs/avm/AvmController.cpp
        srcs/avm/AvmFactory.cpp
        srcs/avm/AvmParser.cpp
        srcs/avm/AvmView.cpp
        srcs/AvmException.cpp
        srcs/main.cpp)
