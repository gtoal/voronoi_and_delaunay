#!/bin/sh
cc -g -Wall -Wno-unused-function table_delaunay.c -lm
../clarkson/rsites 10 2 > test_nodes.txt
echo test|./a.out 2> /dev/null
rm -f ./a.out test_nodes.txt 
