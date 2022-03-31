# Pseudo random numbers generator (PRNG)
Lab work for my university.

## Task
Task was to create program that will use ten different pseudo random
number generation method's, generate a big number of them (like 10^6
or greater) and see rate of their appearing in different intervals 
with diagram.
For example, for linear coherent  method, picture will be something like this:
```
[0.0; 0.1]      0.10    ##########  
[0.1; 0.2]      0.10    ##########  
[0.2; 0.3]      0.10    ##########  
[0.3; 0.4]      0.10    ##########  
[0.4; 0.5]      0.10    ##########  
[0.5; 0.6]      0.09    #########  
[0.6; 0.7]      0.10    ##########  
[0.7; 0.8]      0.10    ##########  
[0.8; 0.9]      0.10    ##########  
[0.9; 1.0]      0.10    #########  
```

## Prerequisites

- g++ >= 10.3.0
- make >= 4.3

## Build and usage
Build:
```shell
$ make dirs && make build
```

Then in `lab/bin/` must appear a binary:
```shell
$ ./lab/bin/lab1
```
