#!/bin/sh
gcc -fPIC -c DieWithMessage.c
gcc -shared -o libDieWithMessage.so DieWithMessage.o

gcc -fPIC -I. -lDieWithMessage -L. -c AddressUtility.c -std=gnu99
gcc -shared -lDieWithMessage -L. -o libAddressUtility.so AddressUtility.o

gcc -fPIC -I. -lDieWithMessage -lAddressUtility -L. -c TCPServerUtility.c -std=gnu99
gcc -shared -lDieWithMessage -L. -o libTCPServerUtility.so TCPServerUtility.o
gcc  -lDieWithMessage  -lTCPServerUtility -lAddressUtility  -L. TCPEchoServer4.c -o TCPEchoServer4
./TCPEchoServer4 8&
echo TCPEchoServer4 pid `pidof TCPEchoServer4` is start
