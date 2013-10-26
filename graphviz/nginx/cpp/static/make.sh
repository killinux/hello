g++ -c hello.cpp
ar crv libmyhello.a hello.o
g++ main.c libmyhello.a -o main 
./main
