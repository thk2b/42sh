#!/bin/sh
./Simple-Fuzzer/sfuzz -f -q -O -n ../config_sequences -L test_input
mkdir shell
mkdir ft_shell

for x in test_input.*
do
    cat $x | sh > shell/$x
	cat $x | ../42sh > ft_shell/$x
	if diff -y ft_shell/$x shell/$x
	then
		printf "\e[1;34mMATCHED.\n\e[0m"
	else
		printf "\e[31;1mError!\n\e[0m"
		break
	fi 
done
