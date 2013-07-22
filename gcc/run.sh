#!/bin/sh
gcc -c  message.c 
gcc -c main.c 
gcc -o goodbye main.o message.o
./goodbye
