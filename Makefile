PHONY : all

all : MyMatrix.cpp
	g++ MyMatrix.cpp square.c -o main
