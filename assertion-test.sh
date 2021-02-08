#!/bin/sh

klee --emit-all-errors maze_assert.bc > /dev/null 2>&1

for file in `ls -1 klee-last/* | grep -A 2 .err | grep .ktest`; do
    ktest-tool $file
    echo "\n\n"
done

