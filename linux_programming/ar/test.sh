#!/bin/bash

gcc -c test1.c
gcc -c test2.c
ar cr libtest.a test1.o test2.o
