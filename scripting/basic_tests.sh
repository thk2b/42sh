#!/bin/sh
./Simple-Fuzzer/sfuzz -f -q -O -n Simple-Fuzzer/configs/simple -L utest_simple
mkdir shell
mkdir ft_shell

for x in utest*
do
    cat $x | sh > shell/$x
	cat $x | ../42sh > ft_shell/$x
	if diff -y ft_shell/$x shell/$x
	then
		echo "same!"
	else
		echo "found error!"
		break
	fi 
done
