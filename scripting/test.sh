#!/bin/sh
./Simple-Fuzzer/sfuzz -f -q -O -n Simple-Fuzzer/configs/literals -L test_input
mkdir shell
mkdir ft_shell

for x in test_input.*
do
    cat $x | sh > shell/$x
	eval $x | cat > ft_shell/$x
	if diff ft_shell/$x shell/$x
	then
		echo "same!"
	else
		echo "found error!"
		break
	fi 
done
