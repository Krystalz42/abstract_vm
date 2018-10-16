cmake_minimum_required(VERSION 3.12)
project(avm)

set(CMAKE_CXX_STANDARD 14)

include_directories(incs)

add_executable(avm srcs/main.cpp srcs/avm/AvmController.cpp incs/avm/AvmController.hpp incs/IOperand.hpp incs/avm.hpp incs/Operand.hpp srcs/avm/AvmModels.cpp incs/avm/AvmModels.hpp srcs/avm/AvmParser.cpp incs/avm/AvmParser.hpp incs/MutantStack.hpp)