
# Table of Contents

1.  [Overview](#orga998cf9)
2.  [Highlights](#org3ffe8ad)
    1.  [Extendable Equation Parser](#org0e7c1b1)
    2.  [Flexible Mesh Size](#org23d7d0b)
    3.  [N-Dimensional Integrals](#orgfcb742a)
3.  [Usage](#org30d97c6)
    1.  [Input](#org10010b3)
        1.  [Supported Operators](#orgbe9b289)
        2.  [Supported Functions](#orgc918a5a)
    2.  [Build](#org985ae5e)
    3.  [Command Line Arguments](#org934308b)
    4.  [Default Behavior](#org54e8239)
    5.  [run\_tests.sh](#org4aac20b)



<a id="orga998cf9"></a>

# Overview

A program for approximating definite integrals, written for MATH
613 - Applied Linear Algebra course at Indiana State University. The
program uses [Simpson's one-third](https://en.wikipedia.org/wiki/Simpson%27s_rule) rule for the approximation:

![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%20%5Cint%20_%7Ba%7D%5E%7Bb%7Df%28x%29%5C%2Cdx%5Capprox%20%7B%5Ctfrac%20%7B%5CDelta%20x%7D%7B3%7D%7D%5Cleft%28f%28x_%7B0%7D%29&plus;4f%28x_%7B1%7D%29&plus;2f%28x_%7B2%7D%29&plus;4f%28x_%7B3%7D%29&plus;2f%28x_%7B4%7D%29&plus;%5Ccdots%20&plus;4f%28x_%7Bn-1%7D%29&plus;f%28x_%7Bn%7D%29%5Cright%29)

This program uses the extended form of Simpson's rule for
approximating n-dimensional integrals.


<a id="org3ffe8ad"></a>

# Highlights

The following are some implementation details that are of note.


<a id="org0e7c1b1"></a>

## Extendable Equation Parser

The program contains a custom tokenizer (`scanner.c`) and parser
(`parser.c`) that converts an infix input equation to an abstract
syntax tree (`ast.c`). Representing the equation as an AST allows
for computing the equation on many values efficiently. It is also a
simple matter to extend the scanner and parser to handle new
operators and functions.


<a id="org23d7d0b"></a>

## Flexible Mesh Size

The program uses an adaptive approach for choosing the mesh
size. Starting at a low value, the mesh size is doubled until the
approximation converges to within four decimal places (`simpson.c`). The
mesh size is part of the output of the program.


<a id="orgfcb742a"></a>

## N-Dimensional Integrals

The program was built from the ground up to accomadate
n-dimensional integrals. The program accepts as input the integral
dimension and then a list of integral specifications that consist
of the start and end of the integral, as well as the variable the
integral should be performed on (`args.c`, `simpson.c`). See the
Usage section for more details.


<a id="org30d97c6"></a>

# Usage


<a id="org10010b3"></a>

## Input

The program accepts as input an infix equation that can contain
numbers, functions, one-character variables, and operators.


<a id="orgbe9b289"></a>

### Supported Operators

-   `+` (addition)
-   `-` (subtraction)
-   `*` (multiplication)
-   `/` (division)
-   `^` (exponentiation)
-   `(` (open parenthesis)
-   `)` (closing paranthesis)


<a id="orgc918a5a"></a>

### Supported Functions

-   `sin` (sine)
-   `cos` (cosine)
-   `tan` (tangent)
-   `ln` (natrual logarithm)
-   `sqrt` (square root)


<a id="org985ae5e"></a>

## Build

To build the project, run the following command in the root
directory of the project: 

`make integrate`

This command produces the target executable `integrate`.


<a id="org934308b"></a>

## Command Line Arguments

-   -n <dimension>: Specifies the integral dimension as <dimension>.
-   -p <params-list>: Specifies the list of integral
    specifications. A colon (`:`) separated list of comma (`,`)
    separated specifications e.g. `0,3,x:0,3,y` specifies a double
    integral in which the variable `x` (the outer integral) is
    integrates over the range [0, 3] and variable `y` (the inner
    integral) is integrated over the range [0, 3].
-   -e <equation>: Specifies the equation to integrate.


<a id="org54e8239"></a>

## Default Behavior

If no command line arguments are given, the program will expect the
user to first input the integral specification, then the
equation. One or the other may be passed as command line arguments,
while the other is read from `stdin`. For example,

    ./integrate 
    0 3.14 x
    sin(x)

is the `stdin` way of specifying \(\int_0^\pi \sin(x) dx\). The
command line way would be:

    ./integrate -n 1 -p `0,3.14,x' -e `sin(x)'


<a id="org4aac20b"></a>

## run\_tests.sh

Run the interactive program `run_tests.sh` to perform some test
examples using the program. The test examples are as follows:

-   ![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%7B%5Cint_0%5E%7B2%5Cpi%7D%20%5Csin%28x%29%20dx%7D)
-   ![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%7B%5Cint_0%5E%7B2%5Cpi%7D%20%5Ccos%28x%29%20dx%7D)
-   ![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%7B%5Cint_0%5E%7B10%7D%20%5Csin%28x%5E2%20&plus;%201%29%20dx%7D)
-   ![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%7B%5Cint_%7B10%7D%5E%7B20%7D%20%5Csin%28x%5E2%20&plus;%201%29%20dx%7D)
-   ![equation](https://latex.codecogs.com/svg.latex?%5Cdisplaystyle%7B%5Cint_%7B-1%7D%5E%7B1%7D%20%5Cint_1%5E2%20x%5E2y%20&plus;%20xy%5E2%20dx%20dy%7D)

