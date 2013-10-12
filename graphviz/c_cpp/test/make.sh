#!/bin/sh
g++ -fpic -shared -g -o libaa.so aa.cxx -I ./
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/hellogit/hello/graphviz/c_cpp/test
g++ -fpic -shared -g -o mylib.so mylib.cxx -laa -I ./ -L.
gcc -o main main.c ./mylib.so -ldl
./main

