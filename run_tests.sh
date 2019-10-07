#!/bin/bash

make integrate

echo
echo -n "Run test 1? "
read

echo "Running test 1:"
./integrate -n 1 -p '0,6.28,x' -e 'sin(x)'

echo
echo -n "Run test 2? "
read

echo "Running test 2:"
./integrate -n 1 -p '0,6.28,x' -e 'cos(x)'

echo
echo -n "Run test 3? "
read

echo "Running test 3:"
./integrate -n 1 -p '0,10,t' -e 'sin(t^2 + 1)'

echo
echo -n "Run test 4? "
read

echo "Running test 4:"
./integrate -n 1 -p '10,20,t' -e 'sin(t^2 + 1)'

echo
echo -n "Run test 5? "
read

echo "Running test 5:"
./integrate -n 2 -p '-1,1,y:1,2,x' -e 'x^2 * y + x * y^2'

echo

