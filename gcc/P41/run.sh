#!/bin/sh
gcc -c test.c
gcc -S test.c
objdump -d test.o
