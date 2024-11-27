PHONY : all

all : MyMatrix.hpp
	g++ main.cpp square.c -o main
