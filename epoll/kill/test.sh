#!/bin/sh
gcc  sigtest.c
./a.out&
kill -USR1 `pidof a.out`
kill -USR2 `pidof a.out`
kill 9 `pidof a.out`
rm a.out
