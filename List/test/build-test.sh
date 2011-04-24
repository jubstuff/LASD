#!/usr/bin/env bash

cd ..
make
cd test
#costruisce il file con tutti i test
./make-tests.sh > AllTests.c

gcc -Wall -o test-suite AllTests.c CuTest.c ../lista.o ListTests.c
./test-suite
