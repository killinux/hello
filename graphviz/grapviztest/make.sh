#!/bin/sh
#yum install graphviz 
gcc -Wl,-Map=test.map -g -o test test.c  
./test 
#grep main test.map 
#addr2line 0x00000000004003c8 -e test -f  
gcc -g -finstrument-functions test.c instrument.c -o test 
./test 
./pvtrace test 
dot -Tjpg graph.dot -o graph.jpg  
