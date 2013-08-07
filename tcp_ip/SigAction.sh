#!/bin/sh
#gcc SigAction.c  -o SigAction -L. -lDieWithMessage
# kill -2 pid

gcc testSigAction.c  -o SigAction
./SigAction &

kill -2 `pidof SigAction`
