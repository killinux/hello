#!/bin/sh
#g++ -I. cppmain.c cpppart.cpp 
g++ -I. -c cpppart.cpp 
#g++ -I. cppmain.c cpppart.o 
gcc -I. cmain.c cpppart.o 
./a.out
