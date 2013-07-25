#!/bin/sh
gcc  -lDieWithMessage  -lTCPServerUtility -lAddressUtility  -L. GetAddrInfo.c -std=gnu99 -o GetAddrInfo
./GetAddrInfo
