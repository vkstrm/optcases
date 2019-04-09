#!/usr/bin/env bash

g++-8 -g -c -O3 -o $1.o $1.cpp -Wall
objdump -drwC -Mintel -S $1.o > Asm/$1.s
rm $1.o