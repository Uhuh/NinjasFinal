# Author: Dylan Warren
# Date: MArch 16th 2019
# Purpose: To build a templated matrix class that uses vector and Gaussian
# Course: CS 5201 - Ninja's

CXX = /usr/bin/g++
CXXFLAGS = -g -Wpedantic -Wall -Wextra -Wfloat-conversion -Werror --std=c++17 -Ofast

OBJECTS = ./main.o
.SUFFIXES: .cpp

.cpp.o: $<
	${CXX} -c ${CXXFLAGS} $< -o $@

default: all
all: driver

driver: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f driver > /dev/null 2>&1
	-@rm -f ${OBJECTS} > /dev/null 2>&1
	-@rm -rf html/ latex/ > /dev/null 2>&1

main.o: ./vector.h ./vector.hpp ./matrix.h  \
				./solver.h ./solver.hpp ./main.cpp ./upper.hpp \
				./upper.h ./lower.h ./lower.hpp
