#!/bin/sh
./Simple-Fuzzer/sfuzz -f -q -O -n Simple-Fuzzer/configs/literals file -L testfile

for x in testfile.*
do
    cat $x | sh > sh_output.$x
done
