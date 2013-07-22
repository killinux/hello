#!/bin/sh
gcc -fPIC -c message.c
gcc -shared -o libmessage.so message.o 
gcc -o goodbye -lmessage -L. main.c
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./goodbye
