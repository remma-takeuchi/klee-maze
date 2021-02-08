#!/bin/sh

# Initialize test
make clean > /dev/null 2>&1 &&
make all > /dev/null 2>&1 
klee maze.bc > /dev/null 2>&1 

echo "[Coverage info BEFORE executing all test cases]"
llvm-cov gcov ./maze.gcno


echo "[Execute tests]"
for file in `ls ./klee-last/test*`; do
    echo "Executeing with $file"
    export KTEST_FILE=$file
    ./maze_gcov_harness > /dev/null
done
echo "Test Completed!\n"


echo "[Coverage info AFTER executing all test cases]"
llvm-cov gcov ./maze.gcno
