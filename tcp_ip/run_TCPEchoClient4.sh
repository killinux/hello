#!/bin/sh
gcc -fPIC -c DieWithMessage.c
gcc -shared -o libDieWithMessage.so DieWithMessage.o
gcc -lDieWithMessage -L. TCPEchoClient4.c -o TCPEchoClient4
./TCPEchoClient4 183.60.244.51 hello 8
