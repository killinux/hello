#!/bin/sh
gcc -o demo demo.c -pg
./demo
gprof demo>gprof.txt
